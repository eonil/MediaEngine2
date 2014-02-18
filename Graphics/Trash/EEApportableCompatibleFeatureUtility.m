////
////  EEApportableCompatibleFeatureUtility.m
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 6/23/13.
////
////
//
//
//#import "EEApportableCompatibleFeatureUtility.h"
//
//
//@implementation EEApportableCompatibleFeatureUtility
//@end
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
//
//
//#pragma mark	-	iOS Specifics
//
//#if	EONIL_MEDIA_ENGINE_TARGET_IOS
//
//
///*!
// @param		constraintSize
// 
// 			If you don't want to put a constraint, use `INFINITE`.
// 			Any other than positive real number will be rejected by assertion.
// 
// 
// @note		Copied from Cocos2D-X source code and modified by Hoon H.
// */
//static CGSize const
//MeasureString(NSString* const str, UIFont* const font, CGSize const constraintSize)
//{
//	NSCAssert([str isKindOfClass:[NSString class]], @"");
//	NSCAssert([font isKindOfClass:[UIFont class]], @"");
////	NSCAssert(isnormal(constraintSize.width) && constraintSize.width >= 0.0f, @"");
////	NSCAssert(isnormal(constraintSize.height) && constraintSize.height >= 0.0f, @"");
//	
//    NSArray*	lines	=	[str componentsSeparatedByString: @"\n"];
//    CGSize		dim		=	CGSizeZero;
//    
//    for (NSString *s in lines)
//    {
//        CGSize tmp	=	[s sizeWithFont:font constrainedToSize:constraintSize];
//        if (tmp.width	>	dim.width)
//        {
//			dim.width	=	tmp.width;
//        }
//        dim.height	+=	tmp.height;
//    }
//    
//    return	dim;
//}
//
//
///*
// Copied from Cocos2D-X source code and modified by Hoon H.
// */
//static void
//DrawStringInContext(CGContextRef const context, CGSize const dimension, NSString* const string, UIFont* const font, NSTextAlignment const alignment)
//{
//	NSCAssert(context != NULL, @"`context` must be an instance of `CGContextRef`.");
//
//	CGContextSetRGBFillColor(context, 1,1,1,1);
//	
//	// move Y rendering to the top of the image
//	CGContextTranslateCTM(context, 0.0f, dimension.height);
//	CGContextScaleCTM(context, 1.0f, -1.0f); //NOTE: NSString draws in UIKit referential i.e. renders upside-down compared to CGBitmapContext referential
//	
//	// store the current context
//	UIGraphicsPushContext(context);
//	{
//		CGRect	rect	=	CGRectMake(0, 0, dimension.width, dimension.height);
//		
//		[string drawInRect:rect withFont:font lineBreakMode:NSLineBreakByWordWrapping alignment:alignment];
//	}
//	UIGraphicsPopContext();
//}
//static UIImage* const
//UIImageFromString(NSString* const str, UIFont* const font, CGSize const imageSize, NSTextAlignment const alignment)
//{
//	NSCAssert([str isKindOfClass:[NSString class]], @"");
//	NSCAssert([font isKindOfClass:[UIFont class]], @"");
//
//	CGColorSpaceRef	color_space	=	CGColorSpaceCreateDeviceRGB();
//	CGBitmapInfo	bitmap_info	=	kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big;
//	CGContextRef	drawing_ctx	=	CGBitmapContextCreate(NULL, imageSize.width, imageSize.height, 8, imageSize.width * 4, color_space, bitmap_info);
//
//	DrawStringInContext(drawing_ctx, imageSize, str, font, alignment);
//		
//	CGImageRef		cgimg		=	CGBitmapContextCreateImage(drawing_ctx);
//	UIImage*		image		=	[[UIImage alloc] initWithCGImage:cgimg];
//	
//	CGContextRelease(drawing_ctx);
//	CGColorSpaceRelease(color_space);	
//	CGImageRelease(cgimg);
//	
//	return			image;
//}
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
//
//
//
//
//@implementation EEApportableCompatibleFeatureUtility (EEApportableCompatibleUIKitExtra)
///*!
// @example
// 
//	 //	Unicode characters must be formed in C-string due to Apportable bug. (1.0 beta)
//	 NSString*	str		=	[NSString stringWithUTF8String:"English한글漢字English@＃＆＊＠§※☆★○●◎◇◆□■△▲▽▼→←↑↓↔〓◁◀▷▶♤♠♡♥♧♣⊙◈▣◐◑▒▤▥▨▧▦▩♨☏☎☜☞¶†‡↕↗↙↖↘♭♩♪♬㉿㈜№㏇™㏂㏘℡®ªº"];
//	 UIFont*	font	=	[UIFont systemFontOfSize:24];
//	 UIImage*	img		=	[EEApportableCompatibleFeatureUtility imageBydrawingString:str forSize:CGSizeMake(200, 200) withFont:font alignment:(NSTextAlignmentLeft)];
//
// */
//+ (UIImage *)imageBydrawingString:(NSString *)string forSize:(CGSize)size withFont:(UIFont *)font alignment:(NSTextAlignment)alignment
//{
//	return	UIImageFromString(string, font, size, alignment);
//}
//@end
//
//
//#endif
//
//
//
