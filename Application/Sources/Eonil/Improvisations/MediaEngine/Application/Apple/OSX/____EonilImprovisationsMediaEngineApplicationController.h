//
//  ____EonilImprovisationsMediaEngineApplicationController.h
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

@interface ____EonilImprovisationsMediaEngineApplicationController : NSObject <NSApplicationDelegate>
+ (int)	runWithArgc:(int)argc argv:(char const*[])argv prepare:(void(^)(void))prepare cleanup:(void(^)(void))cleanup step:(void(^)(CGRect bounds))step;
@end















#endif // EONIL_MEDIA_ENGINE_TARGET_OSX
