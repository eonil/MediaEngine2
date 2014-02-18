//
//  EEGraphicsDrawableView.h
//  Graphics
//
//  Created by Hoon H. on 2/16/14.
//
//

#include <Eonil/Improvisations/MediaEngine/Foundation/Foundation.h>

#if	EONIL_MEDIA_ENGINE_TARGET_OSX









#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

/*!
 Provides a convenient view for OpenGL drawing.
 
 @brief
 OpenGL is multi-platform API, but obtaining process is all different by
 platforms. This provides a ready-made drawable framebuffer/renderbuffer
 for Cocoa touch in OS X.
 
 @classdesign
 Framebuffer and related renderbuffers will be created, and prepared.
 They're immediately ready-to-use, and will be cleaned up when this object
 dies.
 
 @note
 OS X version is a hurried implementation. It uses draw block instead of 
 presentation of renderbuffer, and this is because I had no time to dig up
 low level logic on OS X. This will be changed in future version.
 
 Currently OS X version is mainly exists to preview purpose for iOS version.
 */
@interface	EEGraphicsDrawableView : NSOpenGLView
- (id)		initWithFrame:(CGRect)frame;
- (void)	prepareGraphicsContext;
- (void)	cleanupGraphicsContext;
//- (void)	presentRenderbuffer;								//	Not supported yet.
@property	(readwrite,nonatomic,copy)	void(^_draw)(void);		//	Hurried implementation. Will be replaced with `presentRenderbuffer` method.
@end















#endif // EONIL_MEDIA_ENGINE_TARGET_OSX
