//
//  CPUTransformUniformPolylineImmediateDrawer.cpp
//  Graphics
//
//  Created by Hoon H. on 3/20/14.
//
//

#include "CPUTransformUniformPolylineImmediateDrawer.h"

#include "../../Server/Symbols.h"
#include "../../Server/Texture.h"
#include "../../Server/Shader.h"
#include "../../Server/Program.h"
#include "../../Server/Machine.h"
#include "../../Server/Machinery/VertexAttributeChannel.h"
#include "../../Server/Utility/VertexLayoutDescriptor.h"
#include "../../Server/Utility/ProgramVertexChannelingDescriptor.h"
#include "../../Server/Utility/Functions.h"
#include "../../Server/ProgramParameterLocation.h"





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
#include "CPUTransformUniformPolylineImmediateDrawer.vertex.shader.rstr"
				;
				
				static constexpr char const
				FRAGMENT_SHADER_CODE[]	=
#if EONIL_MEDIA_ENGINE_TARGET_IOS
				R"(
				)"
#include "CPUTransformUniformPolylineImmediateDrawer.es.fragment.shader.rstr"
#endif
#if EONIL_MEDIA_ENGINE_TARGET_OSX
#include "CPUTransformUniformPolylineImmediateDrawer.dt.fragment.shader.rstr"
#endif
				;
				
				
				
				
				
				static inline auto
				M() -> Machine&
				{
					return	Machine::current();
				}
				
				
				enum
				VERTEX_CHANNEL_INDEXES : Size
				{
					LOCATION_COORDINATE		=	0,
					COMPOSITION_COLOR		=	1,
				};
				
				static inline auto
				make_vertex_format() -> VertexLayoutDescriptor
				{
					VertexLayoutDescriptor	f{};
					f.appendScalarVectorChannel("locationCoordinateV", 4);				//	LOCATION_COORDINATE
					f.appendScalarVectorChannel("compositionColorV", 4);				//	COMPOSITION_COLOR
					
					return	f;
				}
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			struct
			CPUTransformUniformPolylineImmediateDrawer::Core
			{
				Program			program							{{VERTEX_SHADER_CODE}, {FRAGMENT_SHADER_CODE}};
				local<UniformValueSlot>	transformUniformSlot	{program.uniformValueSlotForName("localToWorldTransformP")};
//				Size			transformUniformIndex			{program.indexOfUniformValueSlotV1ForName("localToWorldTransformP")};
				
				VertexLayoutDescriptor				layout		{make_vertex_format()};
				ProgramVertexChannelingDescriptor	channeling	{ProgramVertexChannelingDescriptor::analyze(layout, program)};
			};
			
			
			
			
			
			
			
			
			
			
			
			
			CPUTransformUniformPolylineImmediateDrawer::CPUTransformUniformPolylineImmediateDrawer()
			{
				_core_ptr		=	uptr<Core>{new Core{}};
			}
			CPUTransformUniformPolylineImmediateDrawer::~CPUTransformUniformPolylineImmediateDrawer()
			{
			}
			
			auto CPUTransformUniformPolylineImmediateDrawer::
			draw(const Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::CPUTransformUniformPolylineImmediateDrawer::Drawing &data, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Matrix4 &worldToScreenTransform, const Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::DisplayScreenFrame &frame) const -> void
			{
				/*
				 
				 Coordinates illustration.
				 
					 
					 
						  CT 
					 (center top)
					 
					 LT			RT						1
						+--+--+
						|  |  |							^
						|     |							|
						|  |  |							|
						|     |							|
						|  |  |							|
						|     |							|
						|  |  |							|
						+-----+
					 LB			RB						0
					 
						  CB
					 (center bottom)				progressing
													direction
													(segment normal)
					 
						radius = dist(LT, CT) = dist(RT, CT) = dist(LB, CB) = dist(RB, CB)
					 
					 
				 
				 
				 Joint resolution.
				 
				                           /                 /
				                          /                 /
				                         /                 /
										/                 /
				                       /                 /
				                      /                 /
				                     /                 /
				                    /                 /
				                   /                 /
							  B   /            E    /
								 /..          ..   /
								/   ''..  ..''  \ /
						   C   *--------*--------*    F
								\   ..''          \
								 \''     CT0       \
							  A   \                 \
								   \                 \
									\                 \
									 \        N0       \
									  \	                \
									   \        ^        \
										\        \        \
										 \        \        \
										  \        \        \
										   \        \        \
											\                 \
				 
				 
				 
				 Point A and B must be moved to point C. Also E to F.
				 
					N1		=	segment normal of the top segment.
					N0		=	segment normal of the bottom segment.
					CB1		=	center bottom of the top segment.
					CT0		=	center top of the bottom segment.
				 
					R		=	line radius.
				 
					a1		=	angle between segments. (angle between points A, C, B)
					a2		=	half of angle between segments
							=	angle between points CT0, C, A
							=	angle between points CT0, C, B
							=	a1 / 2
					
					v1		=	vector from CT0 to C. (unknown)
					v2		=	vector from CT0 to A. (known)
							=	R
					v3		=	vector from A to C. (unknown)
				 
					lv1		=	len(v1)
							=	R / sin(a2)
				 
					lv2		=	len(v2)
							=	sin(a2) * lv1
							=	R
				 
					lv3		=	cos(a2) * lv1
							=	cos(a2) * (R / sin(a2))
							=	cos(a2) / sin(a2) * R
							=	cot(a2) * R
				 
					A		=	CT0 + mul(rot(N0, 90 degrees), R)
					B		=	CB0 + mul(rot(N1, 90 degrees), R)
					C		=	A + v3
							=	A + (N0 * lv3)
				 
				 I'm suck at math, and this may be wrong.
				 
				 */
				
//				struct
//				GPUDataVertex
//				{
//					Vector4		position	{};
//				};
//				
//				EONIL_DEBUG_ASSERT_WITH_MESSAGE(data.strokes.size() >0, "You must pass at least one or more instances. No instance cannot be rendered.");
//				for (auto const& s: data.strokes)
//				{
//					
//				}
//				
//				M().useProgram(_core_ptr->program);
//				{
//					auto&	transform_uniform_slot	=	_core_ptr->program.uniformValueSlotAtIndex(_core_ptr->transformUniformIndex);
//					
//					transform_uniform_slot.setValue(worldToScreenTransform);
//					draw(instances.data(), _core_ptr->layout, _core_ptr->channeling, DrawingMode::LINES, Range::fromAdvancement(0, instances.size() * 2));
//					transform_uniform_slot.unset();
//				}
//				M().unuseProgram();
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}

}}}}