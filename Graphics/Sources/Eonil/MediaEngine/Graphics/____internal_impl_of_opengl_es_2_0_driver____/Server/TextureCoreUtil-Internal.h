////
////  TextureCoreUtil-Internal.h
////  EonilGraphics
////
////  Created by Eonil on 7/21/13.
////
////
//
//#ifndef __EonilGraphics__TextureCoreUtil_Internal__
//#define __EonilGraphics__TextureCoreUtil_Internal__
//
//#include <cstdlib>
//#import <QuartzCore/QuartzCore.h>
//
//#include "../Common.h"
//#include "../Stub/GL.h"
//
//INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN
//
//	namespace
//	Server
//	{
//		namespace
//		{
//			using namespace	Eonil::MediaEngine::Graphics::Stub;
//			
//			
//			
//			
//			
//			
//							
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			bool const
//			isPOT(Size const s)
//			{
//				Size	smin	=	16;
//				Size	s1		=	smin;
//				
//				while (s1 <= s)
//				{
//					if (s1 == s)
//					{
//						return	true;
//					}
//					s1	=	s1 * 2;
//				}
//				return	false;
//			}
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			struct
//			OpacityComponentOptimization
//			{
//				enum
//				CODE
//				{
//					NONE,
//					PREMULTIPLICATION,
//				};
//			};
//			struct
//			AlphaComponentPlacement
//			{
//				enum
//				CODE
//				{
//					FIRST,		//!	Lowest address.
//					LAST,		//!	Highest address.
//				};
//			};
//			
//			class
//			TextureCoreUtil
//			{
//			public:
//				
//			};
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//		
//			
//		}
//		
//		
//	
//		Scalar const
//		RatioInByte(uint8_t const b)
//		{
//			return	(Scalar)b/(Scalar)std::numeric_limits<uint8_t>::max();
//		}
//		Legacy2013SharedMemory const
//		ProcessIntoPremultipliedARGB8888Pixels(Legacy2013SharedMemory const pixels, bool const firstToLast, bool const multiplyAlpha)
//		{
////					if (not lastToFirstAlpha and not multiplyAlpha)
////					{
////						return	pixels;
////					}
//			
//			////
//			
//			struct
//			Pixel
//			{
//				uint8_t	cs[4];
//			};
//			
//			Pixel const*	pmem0	=	(Pixel const*)pixels.address();
//			Pixel*			pmem1	=	(Pixel*)malloc(pixels.length());
//			size_t			pc		=	pixels.length() / 4;
//			
//			for (size_t i=0; i<pc; i++)
//			{
//				Pixel const	p0	=	pmem0[i];
//				Pixel		p1	=	p0;
//				
//				if (firstToLast)	//	ARGB -> RGBA
//				{
//					p1.cs[0]	=	p0.cs[1];
//					p1.cs[1]	=	p0.cs[2];
//					p1.cs[2]	=	p0.cs[3];
//					p1.cs[3]	=	p0.cs[0];
//				}
//				if (multiplyAlpha)	//	Alpha is last component.
//				{
//					p1.cs[0]	*=	RatioInByte(p1.cs[3]);
//					p1.cs[1]	*=	RatioInByte(p1.cs[3]);
//					p1.cs[2]	*=	RatioInByte(p1.cs[3]);
//				}
//				
//				pmem1[i]		=	p1;
//			}
//			
//			return	Legacy2013SharedMemory::Factory::memoryByOwningRange(pmem1, pixels.length());
//		}
//		
//		bool const
//		NeedsAlphaPremultiplication(CGImageRef const image)
//		{
//			CGImageAlphaInfo	alpha	=	CGImageGetAlphaInfo(image);
//
//			return	alpha	=	kCGImageAlphaLast;
//		}
//		
//		
//		
//		/*!
//		 This produces RGBA (premultiplied) texture image and returns a GL texture name to it.
//		 You are responsible to delete the GL texture name.
//		 
//		 @discussion			RGBA(8888) format is primrily considered because it's GL standard.
//								By default, all rendering pipeline in this engine all uses premultiplied 
//								image unless there's special concern. So this will also apply 
//								premultiplication.
//		 
//		 @note					iPhone GPU is not optimal with RGBA texture, and actually it
//								likes ARGB(?, not sure) image.
//								The optimal format is not supported currently, but will be added later.
//		 */
//		GLuint const
//		NameByCreatingTextureFromCGImage(CGImageRef const image, bool const flipInY)
//		{
//			EEGL_ASSERT(image != NULL);
//			EEGL_ASSERT_WITH_REASON(CGImageGetColorSpace(image) != NULL, "Only colored images are supported.");
//
//			
//////			EONIL_DEBUG_ASSERT_WITH_MESSAGE(CGImageGetAlphaInfo(image) == kCGImageAlphaPremultipliedFirst, "Currently only image with premultiplied alpha supported.");
////		
////			//	OpenGL compatible RGBA 8888 image.
////			//	Use as is.
////			
////			CGImageAlphaInfo	alpha	=	CGImageGetAlphaInfo(image);
////			
////			bool				swiz	=	alpha == kCGImageAlphaFirst or alpha == kCGImageAlphaPremultipliedFirst;
////			bool				mult	=	alpha == kCGImageAlphaLast or alpha == kCGImageAlphaFirst;
////			
////			size_t				w	=	CGImageGetWidth(image);
////			size_t				h	=	CGImageGetHeight(image);
////			
////			CGDataProviderRef	d0	=	CGImageGetDataProvider(image);
////			CFDataRef			d1	=	CGDataProviderCopyData(d0);
////			uint8_t const*		b0	=	CFDataGetBytePtr(d1);
////			Legacy2013SharedMemory				b1	=	Legacy2013SharedMemory::Factory::memoryByProxyingRange(b0, w*h*4);
////			Legacy2013SharedMemory				b2	=	ProcessIntoPremultipliedARGB8888Pixels(b1, swiz, mult);
////			
////			GLuint	name	=	eeglGenTexture();
////			eeglBindTexture(GL_TEXTURE_2D, name);
////			eeglTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, b2.address());
////			eeglUnbindTexture(GL_TEXTURE_2D);
////			CFRelease(d1);
////			
////			return	name;
//
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
////				CGImageAlphaInfo	alpha	=	CGImageGetAlphaInfo(image);
//			
////					if (alpha == kCGImageAlphaPremultipliedFirst)
////					{
////						//	OpenGL compatible ARGB 8888 image.
////						//	Use as is.
////						
////						CGDataProviderRef	d0	=	CGImageGetDataProvider(image);
////						CFDataRef			d1	=	CGDataProviderCopyData(d0);
////						uint8_t const*		b0	=	CFDataGetBytePtr(d1);
////						
////						size_t				w	=	CGImageGetWidth(image);
////						size_t				h	=	CGImageGetHeight(image);
////						
////						GLuint	name	=	eeglGenTexture();
////						eeglBindTexture(GL_TEXTURE_2D, name);
////						eeglTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, b0);
////						eeglUnbindTexture(GL_TEXTURE_2D);
////						CFRelease(d1);
////						
////						return	name;
////					}
////					else
//			
//			
//			
//			
//			
//			
//			{
//				//	Convert into ARGB 8888 image.
//				
//				size_t				textureWidth	=	CGImageGetWidth(image);
//				size_t				textureHeight	=	CGImageGetHeight(image);
//				CGSize				imageSize		=	CGSizeMake(textureWidth, textureHeight);
//				EEGL_ASSERT(imageSize.width > 0 && imageSize.height > 0);
//				
//				{
//					void*				data			=	malloc(textureHeight * textureWidth * 4);
//					CGColorSpaceRef		colorSpace		=	CGColorSpaceCreateDeviceRGB();
//					CGContextRef		context			=	CGBitmapContextCreate(data, textureWidth, textureHeight, 8, 4 * textureWidth, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
//					{
//						CGContextClearRect(context, CGRectMake(0, 0, textureWidth, textureHeight));
////						CGContextTranslateCTM(context, 0, textureHeight - imageSize.height);			//	I don't know why this line exist, but it seems required for non-square texture...
//						
//						if (flipInY)
//						{
//							CGContextScaleCTM(context, +1, -1);
//							CGContextTranslateCTM(context, 0, -(CGFloat)textureHeight);
//						}
//						
//						CGContextDrawImage(context, CGRectMake(0, 0, CGImageGetWidth(image), CGImageGetHeight(image)), image);
//						CGContextFlush(context);
//					}
//					CGContextRelease(context);
//					CGColorSpaceRelease(colorSpace);
//					
//					GLuint	name	=	eeglGenTexture();
//					eeglBindTexture(GL_TEXTURE_2D, name);
//					eeglTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//					eeglUnbindTexture(GL_TEXTURE_2D);
//					free(data);
//					
////					UIImage*	img1	=	[UIImage imageWithCGImage:image];
////					[UIImagePNGRepresentation(img1) writeToFile:@"/Users/Eonil/Temp/aaaa.png" atomically:YES];
//					
//					return	name;
//				}
//			}
//
//			
//			
//			
//			
//				
//				
//		
//		
//
//		}
//	}
//	
//	
//	
//	
//	
//	
//	
//}}}}
//
//#endif /* defined(__EonilGraphics__TextureCoreUtil_Internal__) */
