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
#include "../../Server/Machine.h"
#include "../../Server/Machinery/VertexAttributeChannel.h"
#include "../../Server/Utility/VertexLayoutDescriptor.h"
#include "../../Server/Utility/ProgramVertexChannelingDescriptor.h"
#include "../../Server/Utility/Functions.h"


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
#include "CPUTransformLineDrawer.vertex.shader"
				;
				
				static constexpr char const
				FRAGMENT_SHADER_CODE[]	=
#if EONIL_MEDIA_ENGINE_TARGET_IOS
#include "CPUTransformLineDrawer.es.fragment.shader"
#endif
#if EONIL_MEDIA_ENGINE_TARGET_OSX
#include "CPUTransformLineDrawer.dt.fragment.shader"
#endif
				;
				
				
				
				static inline auto
				M() -> Machine&
				{
					return	Machine::machine();
				}
				
				static inline auto
				make_program() -> Program
				{
					VertexShader::NameChannelMap	ncmap{};
					
					VertexShader	vs	{VERTEX_SHADER_CODE};
					FragmentShader	fs	{FRAGMENT_SHADER_CODE};

					return	{vs, fs};
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
				Program			program							{{VERTEX_SHADER_CODE}, {FRAGMENT_SHADER_CODE}};
				Size			transformUniformIndex			{program.indexOfUniformValueSlotForName("localToWorldTransformP")};
				
				VertexLayoutDescriptor				layout		{make_vertex_format()};
				ProgramVertexChannelingDescriptor	channeling	{ProgramVertexChannelingDescriptor::analyze(layout, program)};
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
				for (auto const& i: instances)
				{
					EONIL_DEBUG_ASSERT(i.origination.location.w == 1);
					EONIL_DEBUG_ASSERT(i.destination.location.w == 1);
				}
				
				Machine::machine().useProgram(_core_ptr->program);
				{
					_core_ptr->program.uniformValueSlotAtIndex(_core_ptr->transformUniformIndex).setValue(worldToScreenTransform);
					draw(instances.data(), _core_ptr->layout, _core_ptr->channeling, DrawingMode::LINES, Range::fromAdvancement(0, instances.size() * 2));
				}
				Machine::machine().unuseProgram();
			}
			
			
			

			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}
