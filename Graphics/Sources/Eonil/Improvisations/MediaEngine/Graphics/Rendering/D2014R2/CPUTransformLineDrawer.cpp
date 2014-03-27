//
//  CPUTransformLineDrawer.cpp
//  Graphics
//
//  Created by Hoon H. on 2/22/14.
//
//

#include "CPUTransformLineDrawer.h"


#include "../../Server/Symbols.h"
#include "../../Server/Texture.h"
#include "../../Server/Shader.h"
#include "../../Server/Program.h"
#include "../../Server/ProgramParameterLocation.h"
#include "../../Server/Machine.h"
#include "../../Server/Machinery/VertexAttributeChannel.h"
#include "../../Server/Utility/VertexLayoutDescriptor.h"
#include "../../Server/Utility/VertexComponentChannelingDescriptor.h"
#include "../../Server/Utility/GeometryRendering.h"

/*!
 
 OpenGL 2.0 does not support geometry instancing.
 
 */







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
#include		"CPUTransformLineDrawer.vertex.shader.glsl-dt-1_10"
#elif			EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
#include		"CPUTransformLineDrawer.vertex.shader.glsl-es-1_00"
#else
#error			EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
#endif
				
				;
				
				static constexpr char const
				FRAGMENT_SHADER_CODE[]	=
#if				EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
#include		"CPUTransformLineDrawer.fragment.shader.glsl-dt-1_10"
#elif			EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
#include		"CPUTransformLineDrawer.fragment.shader.glsl-es-1_00"
#else			
#error			EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
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
			CPUTransformLineDrawer::Core
			{
				Program								program						{{VERTEX_SHADER_CODE}, {FRAGMENT_SHADER_CODE}};
				local<ProgramUniformValueSlotProxy>	transformUniformIndex		{program.uniformValueSlotForName("localToWorldTransformP")};
				
				VertexComponentChannelingDescriptor	channeling					{VertexComponentChannelingDescriptor::analyze(make_vertex_format(), program)};
			};
			
			
			
			
			
			
			
			
			
			
			
			
			CPUTransformLineDrawer::CPUTransformLineDrawer()
			{
				_core_ptr		=	uptr<Core>{new Core{}};
			}
			CPUTransformLineDrawer::~CPUTransformLineDrawer()
			{
			}
			
			auto CPUTransformLineDrawer::
			drawInstances(const vec<Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::CPUTransformLineDrawer::Instance> &instances, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Matrix4 &worldToScreenTransform, DisplayScreenFrame const& frame) const -> void
			{
				EONIL_DEBUG_ASSERT_WITH_MESSAGE(instances.size() >0, "You must pass at least one or more instances. No instance cannot be rendered.");
				for (auto const& i: instances)
				{
					EONIL_DEBUG_ASSERT(i.origination.location.w == 1);
					EONIL_DEBUG_ASSERT(i.destination.location.w == 1);
				}
				
				////
				
				M().useProgram(_core_ptr->program);
				{
					auto&	transform_uniform_slot	=	*_core_ptr->transformUniformIndex;
					
					transform_uniform_slot.setValue(worldToScreenTransform);
					{
						GenericMemoryRange<void const>		range1	{instances.data(), instances.data() + instances.size()};
						ClientMemoryVertexProvisioning		verts1	{range1, _core_ptr->channeling};
						GeometryProvisioning				geomp1	{&verts1};
						
						draw(geomp1, DrawingMode::LINES, {0, instances.size() * 2});
					}
					transform_uniform_slot.unset();
				}
				M().unuseProgram();
			}
			
			
			

			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}
