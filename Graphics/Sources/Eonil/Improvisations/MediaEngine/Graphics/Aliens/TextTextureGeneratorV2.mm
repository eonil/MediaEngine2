//
//  TextTextureGeneratorV2.cpp
//  Graphics
//
//  Created by Hoon H. on 2/17/14.
//
//

#include "TextTextureGeneratorV2.h"

#include "FontProxy.h"




#include "../Debugging/Doctor.h"

#include "../Aliens/PlanarRGBAImageProxy.h"



#if	EONIL_MEDIA_ENGINE_TARGET_OSX
#include <CoreFoundation/CoreFoundation.h>
#include <QuartzCore/QuartzCore.h>
#include <GLKit/GLKit.h>
#include <AppKit/AppKit.h>
#include "../Aliens/Apple/CoreGraphics/_PlanarRGBAImageProxy_Core_using_Apple_CoreGraphics.h"
#endif

#if	EONIL_MEDIA_ENGINE_TARGET_IOS
#include <CoreFoundation/CoreFoundation.h>
#include <QuartzCore/QuartzCore.h>
#include <GLKit/GLKit.h>
#include <UIKit/UIKit.h>
#include "../Aliens/Apple/CoreGraphics/_PlanarRGBAImageProxy_Core_using_Apple_CoreGraphics.h"
#endif




























#if	EONIL_MEDIA_ENGINE_TARGET_IOS

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Aliens
	{
		namespace
		{
			
			
			
			/*!
			 Copied from Cocos2D-X source code and modified by Hoon H.
			 
			 @result	Bounds in pixels of the actual text drawing range.
			 */
			static Bounds2 const
			DrawStringInContext(CGContextRef const context, CGSize const dimension, NSString* const string, UIFont* const font, UIColor* const color, NSTextAlignment const alignment)
			{
				NSCAssert(context != NULL, @"`context` must be an instance of `CGContextRef`.");
				
				Bounds2	draw_b;
				
				// move Y rendering to the top of the image
				CGContextTranslateCTM(context, 0.0f, dimension.height);
				CGContextScaleCTM(context, 1.0f, -1.0f); //NOTE: NSString draws in UIKit referential i.e. renders upside-down compared to CGBitmapContext referential
				
				// store the current context
				UIGraphicsPushContext(context);
				
				{
					FontProxy	f2	=	FontProxy::systemDefaultFont(font.pointSize, true);
					Vector2		fsz	=	f2.measure(str{string.UTF8String}, Vector2{dimension.width, dimension.height});
					CGSize		sz	=	CGSizeMake(fsz.x, fsz.y);

//						CGPoint	pt		=	CGPointMake((dimension.width - sz.width) * 0.5, (dimension.height - sz.height) * 0.5);
					CGPoint	pt		=	CGPointMake(0, (dimension.height - sz.height) * 0.5);
					
					/*!
					 Currently always draw at left-top corner.
					 */
					CGRect	rect	=	CGRectMake(0, 0, sz.width, sz.height);
					
					[color setFill];
					[string drawInRect:rect
							  withFont:font
						 lineBreakMode:NSLineBreakByWordWrapping
							 alignment:alignment
					 ];

					/*
					 This doesn't show multi-line text.
					 */
//						[string drawAtPoint:pt forWidth:sz.width withFont:font fontSize:font.pointSize lineBreakMode:(NSLineBreakByWordWrapping) baselineAdjustment:(UIBaselineAdjustmentAlignBaselines)];

					////
					
					draw_b	=	Bounds2(0, 0, sz.width, MIN(sz.height, dimension.height));
				}
				UIGraphicsPopContext();
				
				////
				
				return	draw_b;
			}
			
			
//			static TextTextureGeneratorV2::ImageRangeV1 const
//			ImageRangeV1FromString(NSString* const str, UIFont* const font, UIColor* const color, CGSize const imageSize, NSTextAlignment const alignment)
//			{
//				NSCAssert([str isKindOfClass:[NSString class]], @"");
//				NSCAssert([font isKindOfClass:[UIFont class]], @"");
//				
//				CGBitmapInfo	bitmap_info	=	kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Big;
//				CGColorSpaceRef	color_space	=	CGColorSpaceCreateDeviceRGB();
//				CGContextRef	drawing_ctx	=	CGBitmapContextCreate(NULL, imageSize.width, imageSize.height, 8, imageSize.width * 4, color_space, bitmap_info);
//				
//				Bounds2			drawing_b	=	DrawStringInContext(drawing_ctx, imageSize, str, font, color, alignment);
//				
//				CGImageRef		cgimg		=	CGBitmapContextCreateImage(drawing_ctx);
//				NativeImage		pimg		=	NativeImage(cgimg);
//				
//				CGContextRelease(drawing_ctx);
//				CGColorSpaceRelease(color_space);
//				CGImageRelease(cgimg);
//				
//				EEGL_ASSERT(cgimg != NULL);
//				
//				TextTextureGeneratorV2::ImageRangeV1	imgr {pimg, drawing_b};
//				return	imgr;
//			}
			
			
			
			static auto
			ImageRangeV2FromString(NSString* const str, UIFont* const font, UIColor* const color, CGSize const imageSize, NSTextAlignment const alignment) -> TextTextureGeneratorV2::ImageRangeV2
			{
				NSCAssert([str isKindOfClass:[NSString class]], @"");
				NSCAssert([font isKindOfClass:[UIFont class]], @"");
				
				CGBitmapInfo	bitmap_info	=	kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Big;
				CGColorSpaceRef	color_space	=	CGColorSpaceCreateDeviceRGB();
				CGContextRef	drawing_ctx	=	CGBitmapContextCreate(NULL, imageSize.width, imageSize.height, 8, imageSize.width * 4, color_space, bitmap_info);
				
				Bounds2			drawing_b	=	DrawStringInContext(drawing_ctx, imageSize, str, font, color, alignment);
				
				CGImageRef		cgimg		=	CGBitmapContextCreateImage(drawing_ctx);
				
				
				TextTextureGeneratorV2::ImageRangeV2	imgr{};
				imgr.image	=	PlanarRGBAImageProxy::proxyByOwningRawPointer(PlanarRGBAImageProxy::RawPointer{cgimg});
				imgr.bounds	=	drawing_b;
				
				CGContextRelease(drawing_ctx);
				CGColorSpaceRelease(color_space);
				
				/*
				 DO NOT release because the image proxy took the exclusive ownership.
				 */
//				CGImageRelease(cgimg);
				
				EEGL_ASSERT(cgimg != NULL);
				
				return	imgr;
			}
			
			
			
			
			
			
			
//				/*!
//				 Creates alpha-only
//				 */
//				static Memory const
//				ImageMemoryFromString(NSString* const str, UIFont* const font, CGSize const imageSize, NSTextAlignment const alignment)
//				{
//					NSCAssert([str isKindOfClass:[NSString class]], @"");
//					NSCAssert([font isKindOfClass:[UIFont class]], @"");
//					
//					CGColorSpaceRef	color_space	=	CGColorSpaceCreateDeviceRGB();
//					CGBitmapInfo	bitmap_info	=	kCGImageAlphaPremultipliedFirst | kCGBitmapByteOrder32Big;
//					CGContextRef	drawing_ctx	=	CGBitmapContextCreate(NULL, imageSize.width, imageSize.height, 8, imageSize.width * 4, color_space, bitmap_info);
//					
////					CGContextSetFillColor(drawing_ctx, (CGFloat[]){.5,1,0.5,.5});
////					CGContextFillRect(drawing_ctx, CGRectMake(0, 0, 100, 100));
//					
//					DrawStringInContext(drawing_ctx, imageSize, str, font, [UIColor whiteColor], alignment);
//					
//					CGImageRef		cgimg		=	CGBitmapContextCreateImage(drawing_ctx);
//					NativeImage	pimg		=	NativeImage(cgimg);
//					
//					CGContextRelease(drawing_ctx);
//					CGColorSpaceRelease(color_space);
//					CGImageRelease(cgimg);
//					
////					[UIImagePNGRepresentation([[UIImage alloc] initWithCGImage:cgimg]) writeToFile:@"/Users/Eonil/Temp/BBB.png" atomically:YES];
//					
//					EEGL_ASSERT(cgimg != NULL);
//					return	pimg;
//				}
		}
		
		
		
		
		
		
		
		
		
		Vector2 const
		TextTextureGeneratorV2::minimumDrawingSizeOfText(Text const t)
		{
//			NSString*		string	=	[[NSString alloc] initWithUTF8String:t.contentString.c_str()];
//			UIFont*			font	=	[UIFont boldSystemFontOfSize:t.fontSizeInPixels];					//!	@todo	I am not sure the *font size* is in pixels. Fix if it's wrong.
//			CGSize			size	=	CGSizeMake(t.maximumSize.x, t.maximumSize.y);
//			CGSize			sz		=	MeasureString(string, font, size);
//			Vector2			sz1		=	Vector2(sz.width, sz.height);
			
			FontProxy		f1		=	FontProxy::systemDefaultFont(t.fontSizeInPixels, true);
			Vector2			sz2		=	f1.measure(t.contentString, t.maximumSize);
			return			sz2;
		}
		
		
		auto
		TextTextureGeneratorV2::imageRangeV2WithText(const Text t, const Vector4 c) -> ImageRangeV2
		{
			NSString*		string	=	[[NSString alloc] initWithUTF8String:t.contentString.c_str()];
			UIFont*			font	=	[UIFont boldSystemFontOfSize:t.fontSizeInPixels];					//!	@todo	I am not sure the *font size* is in pixels. Fix if it's wrong.
			CGSize			size	=	CGSizeMake(t.maximumSize.x, t.maximumSize.y);
			
			UIColor*		color	=	[UIColor colorWithRed:c.x green:c.y blue:c.z alpha:c.w];
			
			return			ImageRangeV2FromString(string, font, color, size, NSTextAlignmentCenter);
		}
		
		
		
		
		
		
		
		
		
		
		
	}
	
}}}}

#endif // EONIL_MEDIA_ENGINE_TARGET_IOS



