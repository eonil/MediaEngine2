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

typedef	void(^PROC)(void);
typedef	void(^STEP)(CGRect bounds);

@implementation ____EonilImprovisationsMediaEngineApplicationController
{
	PROC	_prepare;
	STEP	_step;
	PROC	_cleanup;
	
	____EonilImprovisationsMediaEngineMainWindowController*	_main_wincon;
}
+ (int)runWithArgc:(int)argc argv:(const char *[])argv prepare:(void (^)(void))prepare cleanup:(void (^)(void))cleanup step:(void (^)(CGRect))step
{
	int	result	=	0;
	
	@autoreleasepool
	{
		____EonilImprovisationsMediaEngineApplicationController*	appcon	=	[[self alloc] init];
		[[NSApplication sharedApplication] setDelegate:appcon];
		
		appcon->_prepare	=	[prepare copy];
		appcon->_step		=	[step copy];
		appcon->_cleanup	=	[cleanup copy];
		
		result				=	NSApplicationMain(argc, argv);
		
		appcon->_prepare	=	nil;
		appcon->_step		=	nil;
		appcon->_cleanup	=	nil;

		NSAssert([[NSApplication sharedApplication] delegate] == appcon, @"The delegate shouldn't be changed.");
		[[NSApplication sharedApplication] setDelegate:nil];
	}
	
	return	result;
}
- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
	_main_wincon	=	[[____EonilImprovisationsMediaEngineMainWindowController alloc] initWithStep:_step];
	_prepare();
	[_main_wincon startDisplayTicking];
}
- (void)applicationWillTerminate:(NSNotification *)notification
{
	[_main_wincon stopDisplayTicking];
	_cleanup();
	_main_wincon	=	nil;
}
@end













#endif // EONIL_MEDIA_ENGINE_TARGET_OSX

