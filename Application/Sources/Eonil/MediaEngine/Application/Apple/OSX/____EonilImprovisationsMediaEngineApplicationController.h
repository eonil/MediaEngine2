//
//  ____EonilImprovisationsMediaEngineApplicationController.h
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

//using	PROC	=	std::function<void(void)>;
//using	STEP	=	std::function<void(CGRect bounds)>;

@class		____EonilImprovisationsMediaEngineMainWindowController;

@interface	____EonilImprovisationsMediaEngineApplicationController : NSObject <NSApplicationDelegate>
+ (int)	runWithArgc:(int)argc argv:(char const*[])argv prepare:(void(^)(____EonilImprovisationsMediaEngineMainWindowController* mwc))prepare cleanup:(void(^)(void))cleanup step:(void(^)(CGRect bounds))step;
//+ (int)	runWithArgc:(int)argc argv:(char const*[])argv prepare:(PROC const&)prepare cleanup:(PROC const&)cleanup step:(STEP const&)step;
@end















#endif // EONIL_MEDIA_ENGINE_TARGET_OSX
