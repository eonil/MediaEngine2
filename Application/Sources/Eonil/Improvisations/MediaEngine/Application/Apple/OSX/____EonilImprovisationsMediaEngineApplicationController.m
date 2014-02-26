//
//  ____EonilImprovisationsMediaEngineApplicationController.m
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#import "____EonilImprovisationsMediaEngineApplicationController.h"

#if	EONIL_MEDIA_ENGINE_TARGET_OSX












#import "____EonilImprovisationsMediaEngineMainWindowController.h"

typedef	void(^STEP)(CGRect bounds);

static STEP		GlobalStepper	=	nil;

@implementation ____EonilImprovisationsMediaEngineApplicationController
{
	____EonilImprovisationsMediaEngineMainWindowController*	_main_wincon;
}
+ (int)runWithArgc:(int)argc argv:(char const*[])argv step:(void (^)(CGRect bounds))step
{
	int	result	=	0;
	
	@autoreleasepool
	{
		____EonilImprovisationsMediaEngineApplicationController*	appcon	=	[[self alloc] init];
		[[NSApplication sharedApplication] setDelegate:appcon];
		
		GlobalStepper	=	[step copy];
		result			=	NSApplicationMain(argc, argv);
		GlobalStepper	=	nil;

		NSAssert([[NSApplication sharedApplication] delegate] == appcon, @"The delegate shouldn't be changed.");
		[[NSApplication sharedApplication] setDelegate:nil];
	}
	
	return	result;
}
- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
	_main_wincon	=	[[____EonilImprovisationsMediaEngineMainWindowController alloc] initWithStep:GlobalStepper];
	[_main_wincon startDisplayTicking];
}
- (void)applicationWillTerminate:(NSNotification *)notification
{
	[_main_wincon stopDisplayTicking];
	_main_wincon	=	nil;
}
@end













#endif // EONIL_MEDIA_ENGINE_TARGET_OSX

