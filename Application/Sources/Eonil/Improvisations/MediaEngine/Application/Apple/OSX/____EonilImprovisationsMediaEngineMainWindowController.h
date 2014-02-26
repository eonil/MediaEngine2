//
//  ____EonilImprovisationsMediaEngineMainWindowController.h
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#include <Eonil/Improvisations/MediaEngine/Foundation/Foundation.h>

#if	EONIL_MEDIA_ENGINE_TARGET_OSX









#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <AppKit/AppKit.h>

@interface ____EonilImprovisationsMediaEngineMainWindowController : NSWindowController <NSWindowDelegate>
- (id)initWithStep:(void(^)(CGRect bounds))step;
- (void)startDisplayTicking;
- (void)stopDisplayTicking;
- (void)displayTimeTick:(id)sender;
@end
















#endif // EONIL_MEDIA_ENGINE_TARGET_OSX
