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
#include "../../Server/Utility/VertexDescriptor.h"
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
				
				enum
				VERTEX_CHANNEL_INDEXES : Size
				{
					LOCATION_COORDINATE		=	0,
					COMPOSITION_COLOR		=	1,
				};
				
				static inline auto
				make_vertex_format() -> VertexDescriptor
				{
					VertexDescriptor	f{};
					f.appendScalarVectorChannel(4);				//	LOCATION_COORDINATE
					f.appendScalarVectorChannel(4);				//	COMPOSITION_COLOR
					
					return	f;
				}
			}
			
			
			
			CPUTransformLineDrawer::CPUTransformLineDrawer()
			{
				VertexShader::NameChannelMap	ncmap{};
				ncmap.insert({"locationCoordinateV", &M().vertexAttributeChannelAtIndex(LOCATION_COORDINATE)});
				ncmap.insert({"compositionColorV", &M().vertexAttributeChannelAtIndex(COMPOSITION_COLOR)});
				
				VertexShader	vs	{VERTEX_SHADER_CODE, VertexShader::NameChannelMap{}};
				FragmentShader	fs	{FRAGMENT_SHADER_CODE};
				
				_program_ptr	=	uptr<Program>{new Program{vs, fs}};
				_transform_idx	=	_program_ptr->indexOfUniformValueSlotForName("localToWorldTransformP");
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
				
				Machine::machine().useProgram(*_program_ptr);
				{
					_program_ptr->uniformValueSlotAtIndex(_transform_idx).setValue(worldToScreenTransform);
					draw(make_vertex_format(), instances.data(), DrawingMode::LINES, Range::fromAdvancement(0, instances.size() * 2));
				}
				Machine::machine().unuseProgram();
			}
			
			
			

			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}
