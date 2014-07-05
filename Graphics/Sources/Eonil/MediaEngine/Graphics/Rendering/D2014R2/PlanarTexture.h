//
//  PlanarTexture.h
//  Graphics
//
//  Created by Hoon H. on 14/7/6.
//
//

#pragma once
#include "RenderingD2014R2Common.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN

class
CrossPlatformAbstractTexture2DBox : no_copy
{
public:
	struct
	Utility
	{
		/*!
		 Creates a texture from RGBA8888 pixels. (LDR, 8-bits integer per channel x 4 channels, 32-bits per pixels)
		 
		 @param		flipInY
		 Flips the image along the Y axis. Use this if you need to flip the image.
		 In most cases (especially if you loaded an image using only this library)
		 you don't need to set the value.
		 
		 **CAUTION**
		 This option is supported only with premultiplied-alpha images.
		 If your image is straight-alpha, you must set this to `false`.
		 
		 @note
		 This function will use alpha channel as is. If you want premultiplied alpha, then you should premultiply
		 them yourself.
		 */
		static auto	textureWithPixels(GenericMemoryRange<void const> memory, sz const& width, sz const& height, bool const& flipInY = false) -> CrossPlatformAbstractTexture2DBox;
	};
	
	
	
public:
	CrossPlatformAbstractTexture2DBox(CrossPlatformAbstractTexture2DBox const&) = delete;
	CrossPlatformAbstractTexture2DBox(CrossPlatformAbstractTexture2DBox&&);
	~CrossPlatformAbstractTexture2DBox();
	
	
private:
	struct	Core;
	uptr<Core>	_core;
	
private:
	CrossPlatformAbstractTexture2DBox(Core&& core);
	
public:
	auto	core() const -> Core const&;
};


using	PlanarTexture	=	CrossPlatformAbstractTexture2DBox;


EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END