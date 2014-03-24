//
//  GPUTransformRegularPolygonDrawer.cpp
//  Graphics
//
//  Created by Hoon H. on 3/20/14.
//
//

#include "GPUTransformRegularPolygonDrawer.h"

#include "../../Server/Symbols.h"
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
				
				
				
				
				
				static inline auto
				M() -> Machine&
				{
					return	Machine::machine();
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
				make_vertexes(Size const& segmentation, Size const& capacity) -> vec<GPUVertex>
				{
					EONIL_DEBUG_ASSERT(segmentation >= 3);
					EONIL_DEBUG_ASSERT(capacity > 0);
					
					vec<GPUVertex>	vs{};
					vs.reserve((segmentation * 2 + 2) * capacity);
					Scalar const	segf	=	Scalar(segmentation);
					
					auto	add_vert	=	[segf, &vs](size_t instance_num, size_t segment_num, Scalar sign)
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
//				static inline auto
//				make_indexes(Size const& segmentation, Size const& capacity) -> Server::ElementArrayBuffer
//				{
//					Scalar const	segf	=	Scalar(segmentation);
//					
//					vec<int16_t>	idxs{};
//					idxs.reserve(capacity * 4);
//					for (Size j=0; j<capacity; j++)
//					{
//						for (Size i=0; i<segmentation; i++)
//						{
//							idxs.push_back(i);
//						}
//					}
//
//					GenericMemoryRange<void const>	mem	{idxs.data(), idxs.data() + idxs.size()};
//					Server::ElementArrayBuffer		eb	{mem};
//					
//					return	ab;
//				}
				
				
				
				
				
				static const constexpr Size	INSTANCE_FLOAT_COUNT	=	sizeof(GPUTransformRegularPolygonDrawer::VaryingInstance)/sizeof(Scalar);
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			struct
			GPUTransformRegularPolygonDrawer::Core
			{
				Size			segmentation				{};
				Size			capacity					{};
				Program			program						{ShaderPatchUtility::programWithPatch(VERTEX_SHADER_CODE, FRAGMENT_SHADER_CODE)};
				
				local<UniformValueSlot>	transformUniformSlot	{program.uniformValueSlotForName("transformP")};
				local<UniformValueSlot>	instancesUniformSlot	{program.uniformValueSlotForName("instancesP[0]")};

				VertexLayoutDescriptor				layout		{make_vertex_format()};
				ProgramVertexChannelingDescriptor	channeling	{ProgramVertexChannelingDescriptor::analyze(layout, program)};
				
//				Server::ArrayBuffer					vertexes;
//				Server::ElementArrayBuffer			indexes;
				
				Core(Size const& segmentation, Size const& capacity)
				:	segmentation(segmentation)
				,	capacity(capacity)
//				,	vertexes(make_vertexes(segmentation, capacity))
				{
					static_assert(sizeof(VaryingInstance) == 8 * sizeof(Scalar), "");
					
					EONIL_MEDIA_ENGINE_DEBUG_LOG("GPUTransformRegularPolygonDrawer, capacity = " + std::to_string(capacity));
				}
			};
			
			
			
			
			
			
			
			
			
			
			
			
			GPUTransformRegularPolygonDrawer::GPUTransformRegularPolygonDrawer(Size const& segmentation, Size const& capacity)
			{
				EONIL_DEBUG_ASSERT(capacity <= _maximumCapacityOfCurrentPlatformForVaryingInstances());
				
				_core_ptr		=	uptr<Core>{new Core{segmentation, capacity}};
			}
			GPUTransformRegularPolygonDrawer::~GPUTransformRegularPolygonDrawer()
			{
			}
			
			auto GPUTransformRegularPolygonDrawer::
			draw(const vec<Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::GPUTransformRegularPolygonDrawer::VaryingInstance> &instances, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Matrix4 &worldToScreenTransform, const Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::DisplayScreenFrame &frame) const -> void
			{
				static_assert(sizeof(VaryingInstance) == sizeof(Scalar) * 8, "");
				EONIL_DEBUG_ASSERT_WITH_MESSAGE(instances.size() > 0, "You must pass at least one or more instances. No instance cannot be rendered.");
				
				auto&	transform_uniform_slot	=	*_core_ptr->transformUniformSlot;
				auto&	instances_uniform_slot	=	*_core_ptr->instancesUniformSlot;
				
				Machine::machine().useProgram(_core_ptr->program);
				{
					Size	page_size	=	_core_ptr->capacity;
					Size	page_count	=	instances.size() / page_size;
					
					for (Size page_index=0; page_index<=page_count; page_index++)
					{
						Size	num_inst	=	page_index == page_count ? instances.size() % page_size : page_size;
						
						transform_uniform_slot.setValue(worldToScreenTransform);
						instances_uniform_slot.setValueArray((Scalar const*)(instances.data() + (page_index * page_size)), (INSTANCE_FLOAT_COUNT * num_inst));
						
						vec<GPUVertex>	vs	=	make_vertexes(_core_ptr->segmentation, _core_ptr->capacity);
						Size			vc	=	calc_vertex_count(_core_ptr->segmentation, num_inst);
						
						Server::Utility::draw(vs.data(), _core_ptr->layout, _core_ptr->channeling, DrawingMode::TRIANGLE_STRIP, Range::fromAdvancement(0, vc));
						
						instances_uniform_slot.unset();
						transform_uniform_slot.unset();

					}
				}
				Machine::machine().unuseProgram();
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			auto GPUTransformRegularPolygonDrawer::
			_maximumCapacityOfCurrentPlatformForVaryingInstances() -> Size
			{
				static_assert(std::is_same<Scalar, float>::value, "Floating-point type must be equal.");
				
				Size	uniform_vec_count	=	Machine::machine().maximumVertexUniformVectorCount();
				Size	all_bytes			=	uniform_vec_count * sizeof(Vector4);
				Size	req_bytes			=	sizeof(Matrix4);
				Size	avail_bytes			=	req_bytes > all_bytes ? 0 : all_bytes - req_bytes;
				Size	inst_count			=	avail_bytes / (sizeof(VaryingInstance));
				return	inst_count;
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}