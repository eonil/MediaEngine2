//
//  ____EonilImprovisationsMediaEngineMainWindowController.h
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#include <Eonil/MediaEngine/Foundation.h>

#if	EONIL_MEDIA_ENGINE_TARGET_OSX









#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <AppKit/AppKit.h>





@protocol	____EonilImprovisationsMediaEngineMainWindowController_Delegate
- (void)	mainWindowControllerPrepare;
- (void)	mainWindowControllerCleanup;
- (void)	mainWindowControllerStep:(CGRect)bounds;
@end

@interface ____EonilImprovisationsMediaEngineMainWindowController : NSWindowController <NSWindowDelegate>
@property	(readwrite,nonatomic,strong)	NSView*																	overlayView;
@property	(readwrite,nonatomic,assign)	id<____EonilImprovisationsMediaEngineMainWindowController_Delegate>		delegate;
- (id)init;									//	Designated initializer.
- (void)startDisplayTicking;
- (void)stopDisplayTicking;
- (void)displayTimeTick:(id)sender;
//- (void)routeToDelegate;					//	Bad design... but this is the only option until refactoring design of `EEGraphicsDrawableView`.
@end
















#endif // EONIL_MEDIA_ENGINE_TARGET_OSX
