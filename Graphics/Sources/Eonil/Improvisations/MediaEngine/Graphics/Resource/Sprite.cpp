//
//  Sprite.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/13/13.
//
//

#include "Sprite.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Resource
	{
		namespace
		{
		}

		
		Sprite::State::State(_Legacy2013_SharingBox<PlanarTexture> texture, std::vector<Vertex> const vertexes) : texture(texture), vertexes(vertexes)
		{
		}
		
		
		
		Sprite::Sprite(_Legacy2013_SharingBox<PlanarTexture> texture, std::vector<Vertex> const vertexes) : _state(new State (texture, vertexes))
		{
		}
		Sprite::Sprite(Sprite const& sprite) : _state(sprite._state)
		{
		}

		

		_Legacy2013_SharingBox<PlanarTexture> const&
		Sprite::texture() const
		{
			return	_state->texture;
		}
		
		auto
		Sprite::vertexes() const -> std::vector<Vertex> const&
		{
			return	_state->vertexes;
		}
	}
	
	
	
	
	
	
	
	
}}}}


















