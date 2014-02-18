//
//  TextTextureGeneratorV2.h
//  Graphics
//
//  Created by Hoon H. on 2/17/14.
//
//

#ifndef __Graphics__TextTextureGeneratorV2__
#define __Graphics__TextTextureGeneratorV2__

#include "../Server/Texture.h"
#include "../Platform/NativeImage.h"
#include "../Aliens/PlanarRGBAImageProxy.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Aliens
	{
		
		using namespace Eonil::Improvisations::MediaEngine::Graphics::Value;
		using namespace Eonil::Improvisations::MediaEngine::Graphics::Platform::D2014R1;
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		/*!
		 Creates an image of rendered text by using underlying platform's text rendering facility.
		 */
		struct
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
			static auto		imageRangeV2WithText(Text const t, Vector4 const colorInRGBA = Vector4(1,1,1,1)) -> ImageRangeV2;			//!	Uses CGImage(premultiplied ARGB)/GLKTextureLoader. No support for straight alpha.
			
			//				static NativeImage const		textureWithText2(Text const t);			//!	Uses CGImage(Alpha only)/manual loading. For support of straight alpha.
		};
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
	
}}}}

#endif /* defined(__Graphics__TextTextureGeneratorV2__) */
