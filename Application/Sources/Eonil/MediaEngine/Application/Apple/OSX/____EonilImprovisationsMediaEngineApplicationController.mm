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

typedef void(^INIT)(____EonilImprovisationsMediaEngineMainWindowController*);
typedef	void(^TERM)(void);
typedef	void(^STEP)(CGRect bounds);

@interface		____EonilImprovisationsMediaEngineApplicationController () <____EonilImprovisationsMediaEngineMainWindowController_Delegate>
@end

@implementation ____EonilImprovisationsMediaEngineApplicationController
{
	INIT	_prepare;
	STEP	_step;
	TERM	_cleanup;
	
	____EonilImprovisationsMediaEngineMainWindowController*	_main_wincon;
}
//+ (int)runWithArgc:(int)argc argv:(const char *[])argv prepare:(const PROC &)prepare cleanup:(const PROC &)cleanup step:(const STEP &)step
//{
//	
//}
+ (int)runWithArgc:(int)argc argv:(const char *[])argv prepare:(void (^)(____EonilImprovisationsMediaEngineMainWindowController* mwc))prepare cleanup:(void (^)(void))cleanup step:(void (^)(CGRect))step
{
	int	result	=	0;
	
	@autoreleasepool
	{
		____EonilImprovisationsMediaEngineApplicationController*	appcon	=	[[self alloc] init];
		[[NSApplication sharedApplication] setDelegate:appcon];
		
		appcon->_prepare	=	[prepare copy];
		appcon->_step		=	[step copy];
		appcon->_cleanup	=	[cleanup copy];
//		appcon->_prepare	=	prepare;
//		appcon->_step		=	step;
//		appcon->_cleanup	=	cleanup;
				
		result				=	NSApplicationMain(argc, argv);
		
		appcon->_prepare	=	nil;
		appcon->_step		=	nil;
		appcon->_cleanup	=	nil;
//		appcon->_prepare	=	nullptr;
//		appcon->_step		=	nullptr;
//		appcon->_cleanup	=	nullptr;

		NSAssert([[NSApplication sharedApplication] delegate] == appcon, @"The delegate shouldn't be changed.");
		[[NSApplication sharedApplication] setDelegate:nil];
	}
	
	return	result;
}
- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
	_main_wincon			=	[[____EonilImprovisationsMediaEngineMainWindowController alloc] init];
	_main_wincon.delegate	=	self;
	
	[_main_wincon startDisplayTicking];
}
- (void)applicationWillTerminate:(NSNotification *)notification
{
	[_main_wincon stopDisplayTicking];
	
	_main_wincon	=	nil;
}

- (void)mainWindowControllerPrepare
{
	_prepare(_main_wincon);
}
- (void)mainWindowControllerCleanup
{
	_cleanup();
}
- (void)mainWindowControllerStep:(CGRect)bounds
{
	_step(bounds);
}
@end













#endif // EONIL_MEDIA_ENGINE_TARGET_OSX

