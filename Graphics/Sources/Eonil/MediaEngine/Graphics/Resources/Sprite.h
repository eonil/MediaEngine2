//
//  Sprite.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/13/13.
//
//

#pragma once
#include "../Common.h"
#include "../Server/Texture.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RESOURCES_NAMESPACE_BEGIN







using namespace Geometry;
using namespace Server;

/*!
 Immutable 2D shape.
 
 Sprite will be drawn using triangle strip.
 Vertexes should be sequenced for it.
 */
class
Sprite
{
public:
	struct
	Vertex
	{
		union
		{
			struct
			{
				Vector2			spaceCoordinate;
				Vector2			mappingCoordinate;
			};
		};
	};
	static_assert(sizeof(Vertex) == sizeof(Scalar) * 4, "");
	
public:
	Sprite(_Legacy2013_SharingBox<PlanarTexture> texture, std::vector<Vertex> const vertexes);
	Sprite(Sprite const& other);
	
	_Legacy2013_SharingBox<PlanarTexture> const&			texture() const;
	std::vector<Vertex> const&		vertexes() const;
	
private:
	struct
	State
	{
		_Legacy2013_SharingBox<PlanarTexture> 	texture;
		std::vector<Vertex>						vertexes;
		
		/*!
		 @note
		 This is required due to bug on Clang 3.3 included in Xcode 4.x.
		 Compiler crashes if a POD struct is initialized with field initializer 
		 and there's no corresponding constructor. So erasing of this constructor
		 will cause a compiler crash.
		 
		 I need explicit constructor to initialize a struct.
		 */
		State(_Legacy2013_SharingBox<PlanarTexture> texture, std::vector<Vertex> const vertexes);
	};
	
	std::shared_ptr<State> const	_state;
};











EONIL_MEDIA_ENGINE_GRAPHICS_RESOURCES_NAMESPACE_END