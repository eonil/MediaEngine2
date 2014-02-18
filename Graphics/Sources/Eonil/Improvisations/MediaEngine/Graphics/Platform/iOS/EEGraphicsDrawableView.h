//
//  EEGraphicsDrawableView.h
//  Graphics
//
//  Created by Hoon H. on 2/10/14.
//
//

#include <Eonil/Improvisations/MediaEngine/Foundation/Foundation.h>

#if	EONIL_MEDIA_ENGINE_TARGET_IOS









#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/*!
 Provides a convenient view for OpenGL drawing.
 
 @brief
 OpenGL is multi-platform API, but obtaining process is all different by
 platforms. This provides a ready-made drawable framebuffer/renderbuffer
 for Cocoa touch in iOS.
 
 @classdesign
 Framebuffer and related renderbuffers will be created, and prepared.
 They're immediately ready-to-use, and will be cleaned up when this object
 dies.
 
 @discussion
 
 */
@interface	EEGraphicsDrawableView : UIView
- (id)		initWithFrame:(CGRect)frame;
- (void)	prepareGraphicsContext;
- (void)	cleanupGraphicsContext;
- (void)	presentRenderbuffer;
@end















#endif // EONIL_MEDIA_ENGINE_TARGET_IOS
