//
//  ____EonilImprovisationsMediaEngineApplicationController.m
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#import "____EonilImprovisationsMediaEngineApplicationController.h"

#if	EONIL_MEDIA_ENGINE_TARGET_IOS













#import <Eonil/Improvisations/MediaEngine/Graphics/Platform/iOS/EEGraphicsDrawableView.h>

typedef	void(^STEP)(CGRect bounds);

static STEP		GlobalStepper	=	nil;



@implementation ____EonilImprovisationsMediaEngineApplicationController
{
	UIWindow*					_main_win;
	UINavigationController*		_nav_con;
	UIViewController*			_gl_view_con;
	EEGraphicsDrawableView*		_gl_view;
	
	CADisplayLink*				_disp_link;
}
+ (int)runWithArgc:(int)argc argv:(char*[])argv step:(void (^)(CGRect bounds))step
{
	@autoreleasepool
	{
		GlobalStepper	=	[step copy];
		int	result		=	UIApplicationMain(argc, argv, nil, NSStringFromClass([self class]));
		GlobalStepper	=	nil;
		
		return	result;
	}
}
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	CGRect	bounds	=	[[UIScreen mainScreen] bounds];
	_main_win		=	[[UIWindow alloc] initWithFrame:bounds];
	_nav_con		=	[[UINavigationController alloc] init];
	_gl_view_con	=	[[UIViewController alloc] init];
	_gl_view		=	[[EEGraphicsDrawableView alloc] init];
	
	[_gl_view_con setView:_gl_view];
	[_nav_con setNavigationBarHidden:YES animated:NO];
	[_nav_con pushViewController:_gl_view_con animated:NO];
	[_main_win setRootViewController:_nav_con];
	[_main_win setBackgroundColor:[UIColor grayColor]];
	[_main_win makeKeyAndVisible];
	
	////
	
	[_gl_view prepareGraphicsContext];
	[self startDisplayTicking];
	
	////
	
	return	YES;
}
- (void)applicationDidEnterBackground:(UIApplication *)application
{
	[self stopDisplayTicking];
}
- (void)applicationWillEnterForeground:(UIApplication *)application
{
	[self startDisplayTicking];
}
- (void)applicationWillTerminate:(UIApplication *)application
{
	[self stopDisplayTicking];
	[_gl_view cleanupGraphicsContext];
}
- (void)startDisplayTicking
{
	_disp_link	=	[CADisplayLink displayLinkWithTarget:self selector:@selector(displayLinkTick:)];
	
	[_disp_link addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSRunLoopCommonModes];
}
- (void)stopDisplayTicking
{
	[_disp_link removeFromRunLoop:[NSRunLoop mainRunLoop] forMode:NSRunLoopCommonModes];
	[_disp_link invalidate];
	
	_disp_link	=	nil;
}
- (void)displayLinkTick:(id)sender
{
	CGRect	bounds	=	[_gl_view bounds];
	GlobalStepper(bounds);
	[_gl_view presentRenderbuffer];
}
@end











#endif // EONIL_MEDIA_ENGINE_TARGET_IOS

