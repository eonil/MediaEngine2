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
#include "../../Server/Machine.h"
#include "../../Server/Machinery/VertexAttributeChannel.h"
#include "../../Server/Utility/VertexLayoutDescriptor.h"
#include "../../Server/Utility/ProgramVertexChannelingDescriptor.h"
#include "../../Server/Utility/Functions.h"






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
#if				EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
#include		"GPUTransformRegularPolygonDrawer.vertex.shader.glsl-dt-1_10"
#elif			EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
#include		"GPUTransformRegularPolygonDrawer.vertex.shader.glsl-es-1_00"
#else
#error			EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
#endif
				;
				
				static constexpr char const
				FRAGMENT_SHADER_CODE[]	=
#if				EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
#include		"GPUTransformRegularPolygonDrawer.fragment.shader.glsl-dt-1_10"
#elif			EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
#include		"GPUTransformRegularPolygonDrawer.fragment.shader.glsl-es-1_00"
#else
#error			EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
#endif
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
					vec<GPUVertex>	vs{};
					vs.reserve(segmentation * 2 * capacity);
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
					
					for (Size j=0; j<capacity; j++)
					{
						add_vert(j, 0, +1);
						for (Size i=0; i<=segmentation; i++)
						{
							add_vert(j, i, +1);
							add_vert(j, i, -1);
						}
						add_vert(j, segmentation, -1);
					}
				
					return	vs;
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
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			struct
			GPUTransformRegularPolygonDrawer::Core
			{
				Size			segmentation				{};
				Size			capacity					{};
				Program			program						{{VERTEX_SHADER_CODE}, {FRAGMENT_SHADER_CODE}};
				Size			transformUniformIndex		{program.indexOfUniformValueSlotV1ForName("transformP")};
				Size			instancesUniformIndex		{program.indexOfUniformValueSlotV1ForName("instancesP[0]")};

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
				}
			};
			
			
			
			
			
			
			
			
			
			
			
			
			GPUTransformRegularPolygonDrawer::GPUTransformRegularPolygonDrawer(Size const& segmentation, Size const& capacity)
			{
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

				auto&	transform_uniform_slot	=	_core_ptr->program.uniformValueSlotAtIndex(_core_ptr->transformUniformIndex);
				auto&	instances_uniform_slot	=	_core_ptr->program.uniformValueSlotAtIndex(_core_ptr->instancesUniformIndex);
				Machine::machine().useProgram(_core_ptr->program);
				{
					transform_uniform_slot.setValue(worldToScreenTransform);
//					instances_uniform_slot.setValueArray((float const*)instances.data(), sizeof(VaryingInstance)/sizeof(Scalar) * );
					instances_uniform_slot.setValueArray((float const*)instances.data(), 8 * _core_ptr->capacity);
					{
						vec<GPUVertex>	vs	=	make_vertexes(_core_ptr->segmentation, _core_ptr->capacity);
						Server::Utility::draw(vs.data(), _core_ptr->layout, _core_ptr->channeling, DrawingMode::TRIANGLE_STRIP, Range::fromAdvancement(0, vs.size()));
					}
					instances_uniform_slot.unset();
					transform_uniform_slot.unset();
				}
				Machine::machine().unuseProgram();
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			auto GPUTransformRegularPolygonDrawer::
			_maximumCapacityOfCurrentPlatformForVaryingInstances() -> Size
			{				
				Size	vec_count	=	Machine::machine().maximumVertexUniformVectorCount();
				Size	bytes		=	vec_count * 4 * 4;
				Size	req_bytes	=	sizeof(Matrix4) + sizeof(Vector4) * 4;
				Size	avail_bytes	=	req_bytes > bytes ? 0 : bytes - req_bytes;
				Size	shape_c		=	avail_bytes / (sizeof(VaryingInstance) * 4);
				return	shape_c;
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}