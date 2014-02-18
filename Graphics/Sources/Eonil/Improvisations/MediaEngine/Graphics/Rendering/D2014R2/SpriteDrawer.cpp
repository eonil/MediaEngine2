//
//  SpriteDrawer.cpp
//  Graphics
//
//  Created by Hoon H. on 2/18/14.
//
//

#include "SpriteDrawer.h"

#include "../../Server/Texture.h"
#include "../../Server/Machine.h"

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
			static inline auto
			M() -> Server::Machine&
			{
				return	Server::Machine::machine();
			}
			
			SpriteDrawer::SpriteDrawer(Server::PlanarTexture const& texture)
			{
//				""
			}
			SpriteDrawer::~SpriteDrawer()
			{
				
			}
			
			auto SpriteDrawer::
			drawInstances(const vec<Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::SpriteDrawer::Instance> &instances) const -> void
			{
				M().useProgram(*_program);
				{
//					_program->
				}
				M().unuseProgram();
			}
			
			
			
			
			
		}
	}
	
}}}}
