//
//  ____EonilImprovisationsMediaEngineMainWindowController.m
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#import "____EonilImprovisationsMediaEngineMainWindowController.h"

#if	EONIL_MEDIA_ENGINE_TARGET_OSX














#import <Eonil/MediaEngine/Graphics/Platform/OSX/EEGraphicsDrawableView.h>

#import <OpenGL/OpenGL.h>
#import <OpenGL/gl3.h>

@implementation ____EonilImprovisationsMediaEngineMainWindowController
{
	EEGraphicsDrawableView2*	_gl_view;
	
	BOOL						_is_first;
	NSTimer*					_disp_timer;
}
- (id)initWithWindow:(NSWindow *)window
{
	[self doesNotRecognizeSelector:_cmd];
	return	nil;
}
- (id)initWithWindowNibName:(NSString *)windowNibName
{
	[self doesNotRecognizeSelector:_cmd];
	return	nil;
}
- (id)initWithWindowNibName:(NSString *)windowNibName owner:(id)owner
{
	[self doesNotRecognizeSelector:_cmd];
	return	nil;
}
- (id)initWithWindowNibPath:(NSString *)windowNibPath owner:(id)owner
{
	[self doesNotRecognizeSelector:_cmd];
	return	nil;
}
//- (id)init
//{
//	[self doesNotRecognizeSelector:_cmd];
//	return	nil;
//}
- (id)init
{
	self	=	[super initWithWindow:nil];
	if (self)
	{
		_is_first	=	YES;
		
		/*
		 Initialization/setup/layout order of NSView hierachy is very important.
		 Do not swizzle the order.
		 */
		
		_gl_view	=	[[EEGraphicsDrawableView2 alloc] init];

		
		NSWindow*	mainwin	=	[[NSWindow alloc] init];		//	Use parameterless initializer to place the window at default position.
		[mainwin setDelegate:self];
		[self setWindow:mainwin];
		
		////

		CGSize const	IPHONE4_SCREEN_RESOLUTION	=	CGSizeMake(640, 960);
		
		NSUInteger	style	=	NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask;
		[mainwin setStyleMask:style];
		[mainwin setBackgroundColor:[NSColor grayColor]];
		[mainwin setDelegate:self];
		[mainwin setContentSize:IPHONE4_SCREEN_RESOLUTION];
		[mainwin orderFront:nil];
		[mainwin makeKeyWindow];
		////
		
		NSView*	cv					=	[mainwin contentView];
		[_gl_view setFrame:[mainwin.contentView bounds]];
		[cv addSubview:_gl_view];
		
//		cv.wantsLayer				=	YES;
//		cv.layer					=	[[CALayer alloc] init];
//		cv.layer.backgroundColor	=	[NSColor redColor].CGColor;
		
		[_gl_view setTranslatesAutoresizingMaskIntoConstraints:NO];
		[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeCenterX) relatedBy:(NSLayoutRelationEqual) toItem:_gl_view attribute:(NSLayoutAttributeCenterX) multiplier:1 constant:0]];
		[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeCenterY) relatedBy:(NSLayoutRelationEqual) toItem:_gl_view attribute:(NSLayoutAttributeCenterY) multiplier:1 constant:0]];
		[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeWidth) relatedBy:(NSLayoutRelationEqual) toItem:_gl_view attribute:(NSLayoutAttributeWidth) multiplier:1 constant:0]];
		[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeHeight) relatedBy:(NSLayoutRelationEqual) toItem:_gl_view attribute:(NSLayoutAttributeHeight) multiplier:1 constant:0]];
		
		////
		
	}
	return	self;
}
- (void)startDisplayTicking
{
	NSAssert(self.delegate != nil, @"Delegate must be set.");
	
	[_gl_view prepareGraphicsContext];
	[self.delegate mainWindowControllerPrepare];
	
	_disp_timer	=	[NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)1.0/60.0 target:self selector:@selector(displayTimeTick:) userInfo:nil repeats:YES];
}
- (void)stopDisplayTicking
{
	NSAssert(self.delegate != nil, @"Delegate must be set.");
	
	[_disp_timer invalidate];
	_disp_timer	=	nil;
	
	[self.delegate mainWindowControllerCleanup];
	[_gl_view cleanupGraphicsContext];
}
- (void)displayTimeTick:(id)sender
{
	NSAssert([[NSThread mainThread] isEqual:[NSThread currentThread]], @"This method must be called from the main thread.");
	NSAssert(self.delegate != nil, @"Delegate must be set.");
	NSCAssert([_gl_view isKindOfClass:[EEGraphicsDrawableView2 class]], @"The GL view must be a valid instance.");
	NSAssert([_disp_timer isKindOfClass:[NSTimer class]], @"Timer must be available.");
	
	CGRect bounds	=	[_gl_view bounds];
	[self.delegate mainWindowControllerStep:bounds];
	[_gl_view presentRenderbuffer];
}




- (void)setOverlayView:(NSView *)overlayView
{
	if (_overlayView != NULL)
	{
		[_overlayView removeFromSuperview];
	}
	
	_overlayView	=	overlayView;
	
	if (_overlayView != NULL)
	{
		_overlayView.frame	=	_gl_view.bounds;
		[_gl_view addSubview:_overlayView];
	}
}









- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize
{
	NSLog(@"%@", NSStringFromSelector(_cmd));
	
	if (_gl_view.window != nil)
	{
		[_gl_view cleanupGraphicsContext];
	}
	return	frameSize;
}
//- (void)windowWillMove:(NSNotification *)notification
//{
//	NSLog(@"%@", NSStringFromSelector(_cmd));
//}
//
//
//- (void)windowDidChangeScreen:(NSNotification *)notification
//{
//	NSLog(@"%@", NSStringFromSelector(_cmd));
//}
//- (void)windowDidLoad
//{
//	NSLog(@"%@", NSStringFromSelector(_cmd));
//}
//- (void)windowDidMove:(NSNotification *)notification
//{
//	NSLog(@"%@", NSStringFromSelector(_cmd));
//}
- (void)windowDidResize:(NSNotification *)notification
{
	NSLog(@"%@", NSStringFromSelector(_cmd));
	
	if (_gl_view.window != nil)
	{
		[_gl_view prepareGraphicsContext];
	}
	
	////
	
	_overlayView.frame	=	_gl_view.bounds;
}
//- (void)windowDidUpdate:(NSNotification *)notification
//{
//	NSLog(@"%@", NSStringFromSelector(_cmd));
//}
//- (void)windowDidExpose:(NSNotification *)notification
//{
//	NSLog(@"%@", NSStringFromSelector(_cmd));
//}
//- (void)windowWillClose:(NSNotification *)notification
//{
//	NSLog(@"%@", NSStringFromSelector(_cmd));
//}
@end





























#endif // EONIL_MEDIA_ENGINE_TARGET_OSX
