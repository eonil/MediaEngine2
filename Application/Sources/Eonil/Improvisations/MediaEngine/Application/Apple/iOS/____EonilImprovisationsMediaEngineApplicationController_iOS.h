//
//  ____EonilImprovisationsMediaEngineApplicationController_iOS.h
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#include <Eonil/Improvisations/MediaEngine/Foundation/Foundation.h>

#if	EONIL_MEDIA_ENGINE_TARGET_IOS










#import <Foundation/Foundation.h>
#import	<UIKit/UIKit.h>

/*!
 This class must be used only from main thread.
 Thread-unsafe, non-reentrant.
 */
@interface	____EonilImprovisationsMediaEngineApplicationController_iOS : NSObject <UIApplicationDelegate>
+ (int)	runWithArgc:(int)argc argv:(char*[])argv prepare:(void(^)(UIViewController* mainViewController))prepare cleanup:(void(^)(void))cleanup step:(void(^)(CGRect boundsInPixels))step;
- (void)startDisplayTicking;
- (void)stopDisplayTicking;
- (void)displayLinkTick:(id)sender;
@end














#endif // EONIL_MEDIA_ENGINE_TARGET_IOS
