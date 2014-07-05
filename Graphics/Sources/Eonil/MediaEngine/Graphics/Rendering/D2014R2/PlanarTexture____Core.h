//
//  PlanarTexture____Core.h
//  Graphics
//
//  Created by Hoon H. on 14/7/6.
//
//

#pragma once
/*
 Internal-only header.
 */
#include "RenderingD2014R2Common.h"
#include "RenderingD2014R2____internal____.h"
#include "PlanarTexture.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN






struct
CrossPlatformAbstractTexture2DBox::Core
{
	Server::Texture2D	_gles2_tex_2d;
	
	Core(Server::Texture2D&& raw)
	{
		_gles2_tex_2d	=	std::move(raw);
	}
};











EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END