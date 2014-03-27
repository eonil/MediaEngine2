////
////  CPUTransformRegularPolygonDrawer.cpp
////  Graphics
////
////  Created by Hoon H. on 3/20/14.
////
////
//
//#include "CPUTransformRegularPolygonDrawer.h"
//
//#include "../../Server/Symbols.h"
//#include "../../Server/Buffer.h"
//#include "../../Server/Query.h"
//#include "../../Server/Texture.h"
//#include "../../Server/Shader.h"
//#include "../../Server/Program.h"
//#include "../../Server/Machine.h"
//#include "../../Server/Machinery/VertexAttributeChannel.h"
//#include "../../Server/Utility/VertexLayoutDescriptor.h"
//#include "../../Server/Utility/ProgramVertexChannelingDescriptor.h"
//#include "../../Server/Utility/Functions.h"
//#include "../../Server/ProgramParameterLocation.h"
//
//
//
//
//
//namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
//	
//	namespace
//	Rendering
//	{
//		namespace
//		D2014R2
//		{
//			using namespace	Server::Utility;
//			
//			namespace
//			{
//				
//				static constexpr char const
//				VERTEX_SHADER_CODE[]	=
//#include "CPUTransformRegularPolygonDrawer.vertex.shader.rstr"
//				;
//				
//				static constexpr char const
//				FRAGMENT_SHADER_CODE[]	=
//#if EONIL_MEDIA_ENGINE_TARGET_IOS
//#include "CPUTransformRegularPolygonDrawer.es.fragment.shader.rstr"
//#endif
//#if EONIL_MEDIA_ENGINE_TARGET_OSX
//#include "CPUTransformRegularPolygonDrawer.dt.fragment.shader.rstr"
//#endif
//				;
//				
//				
//				
//				
//				
//				static inline auto
//				M() -> Machine&
//				{
//					return	Machine::current();
//				}
//				
//				
//				enum
//				VERTEX_CHANNEL_INDEXES : Size
//				{
//					ANGLE		=	0,
//					SIGN		=	1,
//				};
//				
//				static inline auto
//				make_vertex_format() -> VertexLayoutDescriptor
//				{
//					VertexLayoutDescriptor	f{};
//					f.appendScalarVectorChannel("positionV", 4);
//					f.appendScalarVectorChannel("colorV", 4);
//					
//					return	f;
//				}
//				
//				////
//				
//				struct
//				GPUVertex
//				{
//					Scalar		angle	{};			//!	In radians. 0~2*PI CCW. -a if this is inner boundary vertex, +a if this is outer boundary vertex.
//				};
//				
//				static inline auto
//				make_vertexes(Size const& segmentation, Size const& capacity) -> vec<GPUVertex>
//				{
//					Scalar const	segf	=	Scalar(segmentation);
//					
//					vec<GPUVertex>	vs{};
//					vs.reserve(segmentation * 2 * capacity);
//					for (Size j=0; j<capacity; j++)
//					{
//						for (Size i=0; i<=segmentation; i++)
//						{
//							{
//								Scalar	t	=	Scalar(i)/segf;
////								Scalar	a	=	t * 2 * M_PI;			//	Keep this for documentation purpose.
//								Scalar	a	=	t * 2 * M_PI + 1;		//	Shift up by one because GLSL does not support signness on zero.
//								
//								GPUVertex	v1	{};
//								v1.angle	=	+a;		//	Outer first.
//								
//								GPUVertex	v2	{};
//								v2.angle	=	-a;		//	Inner last.
//								
//								vs.push_back(v1);
//								vs.push_back(v2);
//							}
//						}
//					}
//				
//					return	vs;
//				}
////				static inline auto
////				make_indexes(Size const& segmentation, Size const& capacity) -> Server::ElementArrayBuffer
////				{
////					Scalar const	segf	=	Scalar(segmentation);
////					
////					vec<int16_t>	idxs{};
////					idxs.reserve(capacity * 4);
////					for (Size j=0; j<capacity; j++)
////					{
////						for (Size i=0; i<segmentation; i++)
////						{
////							idxs.push_back(i);
////						}
////					}
////					
////					GenericMemoryRange<void const>	mem	{idxs.data(), idxs.data() + idxs.size()};
////					Server::ElementArrayBuffer		eb	{mem};
////					
////					return	ab;
////				}
//			}
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			struct
//			CPUTransformRegularPolygonDrawer::Core
//			{
//				Size			segmentation					{};
//				Program			program							{{VERTEX_SHADER_CODE}, {FRAGMENT_SHADER_CODE}};
//				
//				local<ProgramUniformValueSlotProxy>	transformUniformSlot	{program.uniformValueSlotForName("transformP")};
////				Size			transformUniformIndex			{program.indexOfProgramUniformValueSlotProxyV1ForName("transformP")};
//				
//				VertexLayoutDescriptor				layout		{make_vertex_format()};
//				ProgramVertexChannelingDescriptor	channeling	{ProgramVertexChannelingDescriptor::analyze(layout, program)};
//				
////				Server::ArrayBuffer					vertexes;
////				Server::ElementArrayBuffer			indexes;
//				
//				Core(Size const& segmentation)
//				:	segmentation(segmentation)
////				,	vertexes(make_vertexes(segmentation, capacity))
//				{
//					static_assert(sizeof(VaryingInstance) == 8 * sizeof(Scalar), "");
//				}
//			};
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			CPUTransformRegularPolygonDrawer::CPUTransformRegularPolygonDrawer(Size const& segmentation)
//			{
//				_core_ptr		=	uptr<Core>{new Core{segmentation}};
//			}
//			CPUTransformRegularPolygonDrawer::~CPUTransformRegularPolygonDrawer()
//			{
//			}
//			
//			auto CPUTransformRegularPolygonDrawer::
//			draw(const vec<Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::CPUTransformRegularPolygonDrawer::VaryingInstance> &instances, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Matrix4 &worldToScreenTransform, const Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::DisplayScreenFrame &frame) const -> void
//			{
//				EONIL_DEBUG_ASSERT_WITH_MESSAGE(instances.size() > 0, "You must pass at least one or more instances. No instance cannot be rendered.");
//				
////				auto&	transform_uniform_slot	=	_core_ptr->program.uniformValueSlotAtIndex(_core_ptr->transformUniformIndex);
//				auto&	transform_uniform_slot	=	*_core_ptr->transformUniformSlot;
//				M().useProgram(_core_ptr->program);
//				{
//					transform_uniform_slot.setValue(worldToScreenTransform);
//					{
//						vec<GPUVertex>	vs	=	make_vertexes(_core_ptr->segmentation, instances.size());
//
//						struct
//						GPUVertex2
//						{
//							Vector4	position	{};
//							Vector4	color		{};
//						};
//					
//						vec<GPUVertex2>	vs3{};
//						vs3.reserve(vs.size());
//						
//						Scalar	r1	=	0.2;
//						Scalar	r2	=	0.3;
//						
//						for (Size i=0; i<vs.size(); i++)
//						{
//							Scalar	a1	=	vs.at(i).angle;
////							Scalar	a2	=	fabs(a1);				//	Keep this for documentation purpose.
//							Scalar	a2	=	fabs(a1) - 1;			//	Shift down by one because GLSL does not support signness of zero.
//							bool	s1	=	std::signbit(a1);
//							Scalar	r	=	s1 ? r1 : r2;
//							
//							Scalar	t1	=	a2;
//							Scalar	x1	=	cosf(t1) * r;
//							Scalar	y1	=	sinf(t1) * r;
//							
//							{
//								GPUVertex2	v2;
//								v2.position	=	{x1, y1, 0, 1};
//								vs3.push_back(v2);
//							}
//						}
//						
//						Server::Utility::draw(vs3.data(), _core_ptr->layout, _core_ptr->channeling, DrawingMode::TRIANGLE_STRIP, Range::fromAdvancement(0, vs3.size()));
//					}
//					transform_uniform_slot.unset();
//				}
//				M().unuseProgram();
//			}
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//		}
//	}
//	
//}}}}
