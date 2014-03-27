//
//  GPUTransformRegularPolygonDrawer.cpp
//  Graphics
//
//  Created by Hoon H. on 3/20/14.
//
//

#include "GPUTransformRegularPolygonDrawer.h"

#include "../../Server/Symbols.h"
#include "../../Server/Query.h"
#include "../../Server/Buffer.h"
#include "../../Server/Texture.h"
#include "../../Server/Shader.h"
#include "../../Server/Program.h"
#include "../../Server/ProgramParameterLocation.h"
#include "../../Server/Machine.h"
#include "../../Server/Machinery/VertexAttributeChannel.h"
#include "../../Server/Utility/VertexLayoutDescriptor.h"
#include "../../Server/Utility/ProgramVertexChannelingDescriptor.h"
#include "../../Server/Utility/Functions.h"

#include "../../Server/Utility/VertexComponentChannelingDescriptor.h"
#include "../../Server/Utility/GeometryRendering.h"

#include "ShaderPatchUtility.h"




namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{
			using namespace	Server::Utility;
			
			namespace
			{
				
				static constexpr char const
				VERTEX_SHADER_CODE[]	=
#include		"GPUTransformRegularPolygonDrawer.vertex.shader.glsl-common"
				;
				
				static constexpr char const
				FRAGMENT_SHADER_CODE[]	=
#include		"GPUTransformRegularPolygonDrawer.fragment.shader.glsl-common"
				;
				
				
				
				
				
				static const constexpr Size		INSTANCE_FLOAT_COUNT				=	sizeof(GPUTransformRegularPolygonDrawer::VaryingInstance)/sizeof(Scalar);
				static const constexpr Size		INSTANCE_VECTOR_COUNT				=	sizeof(GPUTransformRegularPolygonDrawer::VaryingInstance)/sizeof(Vector4);
				static const constexpr Size		VERTEX_BUFFER_SIZE_HARD_LIMIT_BYTES	=	256 * 1024;
				
				
				
				static inline auto
				M() -> Machine&
				{
					return	Machine::current();
				}
				
				
				enum
				VERTEX_CHANNEL_INDEXES : Size
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
				calc_vertex_count(Size const& segmentation, Size const& instance_count) -> Size
				{
					EONIL_DEBUG_ASSERT(segmentation >= 3);
					
					Size	extra_segmentation_for_compleness	=	1;
					Size	vertex_per_segment					=	2;
					Size	extra_vertex_count_for_jumping		=	2;
					
					Size	visible_shape_vertex_count			=	(segmentation + extra_segmentation_for_compleness) * vertex_per_segment;
					Size	total_vertex_per_instance			=	visible_shape_vertex_count + extra_vertex_count_for_jumping;
					Size	total_vertex_of_all_instances		=	total_vertex_per_instance * instance_count;
					
					return	total_vertex_of_all_instances;
				}
				static inline auto
				make_vertexes(Size const& segmentation, Size const& capacity) -> vec<GPUVertex>
				{
					EONIL_DEBUG_ASSERT(segmentation >= 3);
					EONIL_DEBUG_ASSERT(capacity > 0);
					
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
					
					for (Size j=0; j<capacity; j++)
					{
						add_vert(j, 0, +1);						//	For connection between circles when drawing in TRIANGLE_STRIP mode.
						for (Size i=0; i<=segmentation; i++)
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
				calc_maximum_instance_count_for_current_hardware() -> Size
				{
					Size	vs_max_uni_vec_c	=	M().query().maximumVertexUniformVectorCount();
					Size	uni_v4_for_others	=	4;
					Size	bytes_avail_uni		=	(vs_max_uni_vec_c - uni_v4_for_others) * sizeof(Scalar) * 4;
					Size	bytes_req_per_inst	=	INSTANCE_FLOAT_COUNT * sizeof(Scalar);
					Size	max_inst_count		=	bytes_avail_uni / bytes_req_per_inst;
					return	max_inst_count;
				}
				static inline auto
				calc_largest_capacity_for_current_hardware(Size segmentation) -> Size
				{
					Size	vert_count_per_inst	=	calc_vertex_count(segmentation, 1);
					Size	bytes_req_per_inst	=	sizeof(GPUVertex) * vert_count_per_inst;
					Size	buffer_max_count	=	VERTEX_BUFFER_SIZE_HARD_LIMIT_BYTES / bytes_req_per_inst;
					Size	final_max_count		=	std::min(calc_maximum_instance_count_for_current_hardware(), buffer_max_count);
					return	final_max_count;
				}
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			struct
			GPUTransformRegularPolygonDrawer::Core
			{
				Size			segmentation				{};
				Size			capacity					{};
				Program			program						{ShaderPatchUtility::programWithPatch(VERTEX_SHADER_CODE, FRAGMENT_SHADER_CODE)};
				
				local<ProgramUniformValueSlotProxy>	transformUniformSlot	{program.uniformValueSlotForName("transformP")};
				local<ProgramUniformValueSlotProxy>	instancesUniformSlot	{program.uniformValueSlotForName("instancesP[0]")};

				VertexLayoutDescriptor				layout		{make_vertex_format()};
				
				Server::ArrayBuffer					vertexes;
				VertexComponentChannelingDescriptorForStreamInServerBuffer	staticDataChanneling	{VertexComponentChannelingDescriptorForStreamInServerBuffer::analyze(&vertexes, make_vertex_format(), program)};
				
//				ProgramVertexChannelingDescriptor2	channeling	{ProgramVertexChannelingDescriptor2::analyze(layout, program)};
				
				
				Core(Size const& segmentation, Size const& capacity)
				:	segmentation(segmentation)
				,	capacity(capacity)
				,	vertexes(make_vertex_buffer(make_vertexes(segmentation, capacity)))
				{
					EONIL_MEDIA_ENGINE_DEBUG_LOG("GPUTransformRegularPolygonDrawer, capacity = " + std::to_string(capacity));
				}
			};
			
			
			
			
			
			
			
			
			
			
			
			
			GPUTransformRegularPolygonDrawer::GPUTransformRegularPolygonDrawer(Size const& segmentation)
			:	GPUTransformRegularPolygonDrawer(segmentation, calc_largest_capacity_for_current_hardware(segmentation))
			{
			}
			GPUTransformRegularPolygonDrawer::GPUTransformRegularPolygonDrawer(Size const& segmentation, Size const& capacity)
			{
				EONIL_DEBUG_ASSERT(capacity <= _maximumCapacityOfCurrentPlatformForVaryingInstances());
				EONIL_DEBUG_ASSERT(calc_vertex_count(segmentation, capacity) * sizeof(GPUVertex) <= VERTEX_BUFFER_SIZE_HARD_LIMIT_BYTES);
				_core_ptr		=	uptr<Core>{new Core{segmentation, capacity}};
			}
			GPUTransformRegularPolygonDrawer::~GPUTransformRegularPolygonDrawer()
			{
			}
			
			auto GPUTransformRegularPolygonDrawer::
			draw(const vec<Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::GPUTransformRegularPolygonDrawer::VaryingInstance> &instances, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Matrix4 &worldToScreenTransform, const Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::DisplayScreenFrame &frame) const -> void
			{
				EONIL_DEBUG_ASSERT_WITH_MESSAGE(instances.size() > 0, "You must pass at least one or more instances. No instance cannot be rendered.");
				
				auto&	transform_uniform_slot	=	*_core_ptr->transformUniformSlot;
				auto&	instances_uniform_slot	=	*_core_ptr->instancesUniformSlot;
				
				M().useProgram(_core_ptr->program);
				{
					Size	inst_count	=	instances.size();
					Size	page_size	=	_core_ptr->capacity;
					Size	page_extra	=	inst_count % page_size;
					Size	page_count	=	inst_count / page_size + 0;
					
					for (Size page_index=0; page_index<=page_count; page_index++)
					{
						Size	num_inst	=	page_index == page_count ? page_extra : page_size;
						
						transform_uniform_slot.setValue(worldToScreenTransform);
						instances_uniform_slot.setValueArray((Vector4 const*)(instances.data() + (page_index * page_size)), (INSTANCE_VECTOR_COUNT * num_inst));
						
						Size	vc			=	calc_vertex_count(_core_ptr->segmentation, num_inst);
						
//						Server::Utility::draw(_core_ptr->vertexes, _core_ptr->layout, _core_ptr->channeling, DrawingMode::TRIANGLE_STRIP, Range::fromAdvancement(0, vc));
						
						GeometryChanneling vchs {&_core_ptr->staticDataChanneling};
						Server::Utility::draw(vchs, {}, DrawingMode::TRIANGLE_STRIP, {0, vc});
						
						instances_uniform_slot.unset();
						transform_uniform_slot.unset();

					}
				}
				M().unuseProgram();
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			auto GPUTransformRegularPolygonDrawer::
			_maximumCapacityOfCurrentPlatformForVaryingInstances() -> Size
			{
				static_assert(std::is_same<Scalar, float>::value, "Floating-point type must be equal.");
				
				Size	uniform_vec_count	=	M().query().maximumVertexUniformVectorCount();
				Size	all_bytes			=	uniform_vec_count * sizeof(Vector4);
				Size	req_bytes			=	sizeof(Matrix4);
				Size	avail_bytes			=	req_bytes > all_bytes ? 0 : all_bytes - req_bytes;
				Size	inst_count			=	avail_bytes / (sizeof(VaryingInstance));
				return	inst_count;
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}