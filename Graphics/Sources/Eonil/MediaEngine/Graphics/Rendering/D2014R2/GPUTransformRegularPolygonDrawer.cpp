//
//  GPUTransformRegularPolygonDrawer.cpp
//  Graphics
//
//  Created by Hoon H. on 3/20/14.
//
//

#include "GPUTransformRegularPolygonDrawer.h"
#include "RenderingD2014R2____internal____.h"
#include "____shader_patch_utility.h"

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

namespace
Rendering
{
	namespace
	D2014R2
	{
		using namespace	Server;
		using namespace	Server::Utility;
		
		namespace
		{
			
			static constexpr char const
			VERTEX_SHADER_CODE[]	=
#include		"GPUTransformRegularPolygonDrawer.vertex.shader.glsl-common.inc"
			;
			
			static constexpr char const
			FRAGMENT_SHADER_CODE[]	=
#include		"GPUTransformRegularPolygonDrawer.fragment.shader.glsl-common.inc"
			;
			
			
			
			
			
			static const constexpr sz		INSTANCE_FLOAT_COUNT				=	sizeof(GPUTransformRegularPolygonDrawer::VaryingInstance)/sizeof(Scalar);
			static const constexpr sz		INSTANCE_VECTOR_COUNT				=	sizeof(GPUTransformRegularPolygonDrawer::VaryingInstance)/sizeof(Vector4);
			static const constexpr sz		VERTEX_BUFFER_SIZE_HARD_LIMIT_BYTES	=	256 * 1024;
			
			
			
			static inline auto
			M() -> Machine&
			{
				return	Machine::current();
			}
			
			
			enum
			VERTEX_CHANNEL_INDEXES : sz
			{
				ANGLE		=	0,
				SIGN		=	1,
			};
			
			static inline auto
			make_vertex_format() -> VertexLayoutDescriptor
			{
				VertexLayoutDescriptor	f{};
				f.appendScalarVectorChannel("angleV", 1);
				f.appendScalarVectorChannel("indexV", 1);
				
				return	f;
			}
			
			////
			
			struct
			GPUVertex
			{
				Scalar		angle	{};			//!	In radians. 0~2*PI CCW. -a if this is inner boundary vertex, +a if this is outer boundary vertex.
				Scalar		index	{};			//!	0~(N-1) for instance index.
			};
			
			static inline auto
			calc_vertex_count(sz const& segmentation, sz const& instance_count) -> sz
			{
				if (USE_DEBUGGING_ASSERTIONS)
				{
					err9_converted_legacy_assertion(segmentation >= 3);
				}
				
				////
				
				sz	extra_segmentation_for_compleness	=	1;
				sz	vertex_per_segment					=	2;
				sz	extra_vertex_count_for_jumping		=	2;
				
				sz	visible_shape_vertex_count			=	(segmentation + extra_segmentation_for_compleness) * vertex_per_segment;
				sz	total_vertex_per_instance			=	visible_shape_vertex_count + extra_vertex_count_for_jumping;
				sz	total_vertex_of_all_instances		=	total_vertex_per_instance * instance_count;
				
				return	total_vertex_of_all_instances;
			}
			static inline auto
			make_vertexes(sz const& segmentation, sz const& capacity) -> vec<GPUVertex>
			{
				if (USE_DEBUGGING_ASSERTIONS)
				{
					err9_converted_legacy_assertion(segmentation >= 3);
					err9_converted_legacy_assertion(capacity > 0);
				}
				
				////

				vec<GPUVertex>	vs{};
				vs.reserve(calc_vertex_count(segmentation, capacity));
				Scalar const	segf	=	Scalar(segmentation);
				
				auto
				add_vert	=	[segf, &vs](size_t instance_num, size_t segment_num, Scalar sign)
				{
					Scalar	t	=	Scalar(segment_num)/segf;
//						Scalar	a	=	t * 2 * M_PI;			//	Keep this for documentation purpose.
					Scalar	a	=	t * 2 * M_PI + 1;		//	Shift up by one because GLSL does not support signness on zero.
					
					GPUVertex	v1	{};
					v1.angle	=	a * sign;
					v1.index	=	instance_num;
					
					vs.push_back(v1);
				};
				
				////
				
				for (sz j=0; j<capacity; j++)
				{
					add_vert(j, 0, +1);						//	For connection between circles when drawing in TRIANGLE_STRIP mode.
					for (sz i=0; i<=segmentation; i++)
					{
						add_vert(j, i, +1);
						add_vert(j, i, -1);
					}
					add_vert(j, segmentation, -1);			//	For connection between circles when drawing in TRIANGLE_STRIP mode.
				}
			
				return	vs;
			}
			static inline auto
			make_vertex_buffer(vec<GPUVertex> const& vs) -> ArrayBuffer
			{
				GenericMemoryRange<GPUVertex const>		r1	=	{vs.data(), vs.size()};
				GenericMemoryRange<void const>			r2	=	{r1};
				return	ArrayBuffer{r2};
			}
			
			static inline auto
			calc_maximum_instance_count_for_current_hardware() -> sz
			{
				sz	vs_max_uni_vec_c	=	M().query().maximumVertexUniformVectorCount();
				sz	uni_v4_for_others	=	4;
				sz	bytes_avail_uni		=	(vs_max_uni_vec_c - uni_v4_for_others) * sizeof(Scalar) * 4;
				sz	bytes_req_per_inst	=	INSTANCE_FLOAT_COUNT * sizeof(Scalar);
				sz	max_inst_count		=	bytes_avail_uni / bytes_req_per_inst;
				return	max_inst_count;
			}
			static inline auto
			calc_largest_capacity_for_current_hardware(sz segmentation) -> sz
			{
				sz	vert_count_per_inst	=	calc_vertex_count(segmentation, 1);
				sz	bytes_req_per_inst	=	sizeof(GPUVertex) * vert_count_per_inst;
				sz	buffer_max_count	=	VERTEX_BUFFER_SIZE_HARD_LIMIT_BYTES / bytes_req_per_inst;
				sz	final_max_count		=	std::min(calc_maximum_instance_count_for_current_hardware(), buffer_max_count);
				return	final_max_count;
			}
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		struct
		GPUTransformRegularPolygonDrawer::Core
		{
			sz								segmentation			{};
			sz								capacity				{};
			Program								program					{____shader_patch_utility::programWithPatch(VERTEX_SHADER_CODE, FRAGMENT_SHADER_CODE)};
			
			local<ProgramUniformValueSlotProxy>	transformUniformSlot	{program.uniformValueSlotForName("transformP")};
			local<ProgramUniformValueSlotProxy>	instancesUniformSlot	{program.uniformValueSlotForName("instancesP[0]")};
			
			Server::ArrayBuffer					vertexes;
			VertexComponentChannelingDescriptor	staticDataChanneling;
			
			Core(sz const& segmentation, sz const& capacity)
			:	segmentation(segmentation)
			,	capacity(capacity)
			,	vertexes(make_vertex_buffer(make_vertexes(segmentation, capacity)))
			,	staticDataChanneling(VertexComponentChannelingDescriptor::analyze(make_vertex_format(), program))
			{
				if (USE_DEBUGGING_ASSERTIONS)
				{
					log9_just_print_line("GPUTransformRegularPolygonDrawer, capacity = " + std::to_string(capacity));
				}
			}
		};
		
		
		
		
		
		
		
		
		
		
		
		
		GPUTransformRegularPolygonDrawer::GPUTransformRegularPolygonDrawer(sz const& segmentation)
		:	GPUTransformRegularPolygonDrawer(segmentation, calc_largest_capacity_for_current_hardware(segmentation))
		{
		}
		GPUTransformRegularPolygonDrawer::GPUTransformRegularPolygonDrawer(sz const& segmentation, sz const& capacity)
		{
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion(capacity <= _maximumCapacityOfCurrentPlatformForVaryingInstances());
				err9_converted_legacy_assertion(calc_vertex_count(segmentation, capacity) * sizeof(GPUVertex) <= VERTEX_BUFFER_SIZE_HARD_LIMIT_BYTES);
			}
			
			////
			
			_core_ptr		=	uptr<Core>{new Core{segmentation, capacity}};
		}
		GPUTransformRegularPolygonDrawer::~GPUTransformRegularPolygonDrawer()
		{
		}
		
		auto GPUTransformRegularPolygonDrawer::
		draw(const vec<VaryingInstance> &instances, const Matrix4 &worldToScreenTransform, const DisplayScreenFrame &frame) const -> void
		{
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion(instances.size() > 0, "You must pass at least one or more instances. No instance cannot be rendered.");
			}
			
			////
			
			auto&	transform_uniform_slot	=	*_core_ptr->transformUniformSlot;
			auto&	instances_uniform_slot	=	*_core_ptr->instancesUniformSlot;
			
			M().useProgram(_core_ptr->program);
			{
				sz	inst_count	=	instances.size();
				sz	page_size	=	_core_ptr->capacity;
				sz	page_extra	=	inst_count % page_size;
				sz	page_count	=	inst_count / page_size + 0;
				
				for (sz page_index=0; page_index<=page_count; page_index++)
				{
					sz	num_inst	=	page_index == page_count ? page_extra : page_size;
					
					transform_uniform_slot.setValue(worldToScreenTransform);
					instances_uniform_slot.setValueArray((Vector4 const*)(instances.data() + (page_index * page_size)), (INSTANCE_VECTOR_COUNT * num_inst));
					
					sz	vc			=	calc_vertex_count(_core_ptr->segmentation, num_inst);
					
					ServerBufferVertexProvisioning	vertexes1	{&_core_ptr->vertexes, _core_ptr->staticDataChanneling};
					{
						Server::Utility::draw(&vertexes1, DrawingMode::TRIANGLE_STRIP, {0, vc});
					}
					
					instances_uniform_slot.unset();
					transform_uniform_slot.unset();

				}
			}
			M().unuseProgram();
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		auto GPUTransformRegularPolygonDrawer::
		_maximumCapacityOfCurrentPlatformForVaryingInstances() -> sz
		{
			static_assert(std::is_same<Scalar, float>::value, "Floating-point type must be equal.");
			
			sz	uniform_vec_count	=	M().query().maximumVertexUniformVectorCount();
			sz	all_bytes			=	uniform_vec_count * sizeof(Vector4);
			sz	req_bytes			=	sizeof(Matrix4);
			sz	avail_bytes			=	req_bytes > all_bytes ? 0 : all_bytes - req_bytes;
			sz	inst_count			=	avail_bytes / (sizeof(VaryingInstance));
			return	inst_count;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END

