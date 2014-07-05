//
//  TextTextureGeneratorV2.h
//  Graphics
//
//  Created by Hoon H. on 2/17/14.
//
//

#pragma once
#include "../____internal_impl_of_opengl_es_2_0_driver____/driver_all.h"
#include "../Platform/NativeImage.h"
#include "../Aliens/PlanarRGBAImageProxy.h"
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

namespace
Aliens
{
	
	using namespace Eonil::MediaEngine::Graphics::Geometry;
	using namespace Eonil::MediaEngine::Graphics::Platform::D2014R1;
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*!
	 Creates an image of rendered text by using underlying platform's text rendering facility.
	 */
	struct
	EONIL_MEDIA_ENGINE_DEPRECATE()
	TextTextureGeneratorV2
	{
		struct
		Text
		{
			std::string		contentString;
			Scalar			fontSizeInPixels;
			Vector2			maximumSize;
		};
		
		struct
		ImageRangeV1
		{
			NativeImage	image;		//!	Pixels in image coordinate. (origin at left-top corner).
			Bounds2			bounds;		//!	Bounds of actual texture drawing in pixels in the image. Follows imaeg local coordinate. (0~width, 0~height)
		};
		
		struct
//			EONIL_MEDIA_ENGINE_DEPRECATE() 
		ImageRangeV2
		{
			PlanarRGBAImageProxy	image	{};		//!	Pixels in image coordinate. (origin at left-top corner).
			Bounds2					bounds	{};		//!	Bounds of actual texture drawing in pixels in the image. Follows imaeg local coordinate. (0~width, 0~height)
			
			ImageRangeV2() = default;
//				ImageRangeV2(ImageRangeV2&& o) //: image(steal(o.image)), bounds(steal(o.bounds))
//				{
//					std::swap(image, o.image);
//					std::swap(bounds, o.bounds);
//				}
			ImageRangeV2(ImageRangeV2&& o) : image(std::move(o.image)), bounds(std::move(o.bounds))
			{
			}
		};
		
		static Vector2 const				minimumDrawingSizeOfText(Text const t);													//!	Minimum size in pixels which required to draw the text.
		
		/*!
		 Uses CGImage(premultiplied ARGB)/GLKTextureLoader. No support for straight alpha.
		 
		 @todo
		 Rendering pipeline is going to implement straight alpha mode. Text-rendering feature needs to 
		 become single-channel alpha-only texture. Implement it later.
		 */
		static auto		imageRangeV2WithText(Text const t, Vector4 const colorInRGBA = Vector4(1,1,1,1)) -> ImageRangeV2;
		
		//				static NativeImage const		textureWithText2(Text const t);			//!	Uses CGImage(Alpha only)/manual loading. For support of straight alpha.
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END
