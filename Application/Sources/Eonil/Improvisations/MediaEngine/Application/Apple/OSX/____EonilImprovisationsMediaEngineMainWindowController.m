//
//  ____EonilImprovisationsMediaEngineMainWindowController.m
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#import "____EonilImprovisationsMediaEngineMainWindowController.h"

#if	EONIL_MEDIA_ENGINE_TARGET_OSX















#import <Eonil/Improvisations/MediaEngine/Graphics/Platform/OSX/EEGraphicsDrawableView.h>

@implementation ____EonilImprovisationsMediaEngineMainWindowController
{
	EEGraphicsDrawableView*		_gl_view;
	
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
- (id)init
{
	[self doesNotRecognizeSelector:_cmd];
	return	nil;
}
- (id)initWithStep:(void (^)(CGRect bounds))step
{
	self	=	[super initWithWindow:nil];
	if (self)
	{
		/*
		 Initialization/setup/layout order of NSView hierachy is very important.
		 Do not swizzle the order.
		 */
		
		EEGraphicsDrawableView*	glv	=	[[EEGraphicsDrawableView alloc] init];
		__unsafe_unretained id	glv_ref	=	glv;
		
		_gl_view	=	glv;
		_gl_view._draw	=	^()
		{
			NSCAssert([glv_ref isKindOfClass:[EEGraphicsDrawableView class]], @"The GL view shouldn't be nil.");
			CGRect bounds	=	[glv_ref bounds];
			step(bounds);
		};
		
		NSWindow*	mainwin	=	[[NSWindow alloc] init];		//	Use parameterless initializer to place the window at default position.
		[self setWindow:mainwin];
		
		////
		
		NSUInteger	style	=	NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask | NSResizableWindowMask;
		CGRect		frame1	=	[[NSScreen mainScreen] frame];
		CGRect		frame2	=	CGRectInset(frame1, frame1.size.width/2, frame1.size.height/2);
		CGRect		frame3	=	CGRectInset(frame2, -320/2, -480/2);
		[mainwin setStyleMask:style];
		[mainwin setBackgroundColor:[NSColor grayColor]];
		[mainwin setDelegate:self];
		[mainwin setFrame:frame3 display:YES];
		[mainwin makeKeyAndOrderFront:self];
		
		////
		
		NSView*	cv					=	[mainwin contentView];
		[cv addSubview:_gl_view];
		
		cv.wantsLayer				=	YES;
		cv.layer					=	[[CALayer alloc] init];
		cv.layer.backgroundColor	=	[NSColor redColor].CGColor;
		
		[_gl_view setTranslatesAutoresizingMaskIntoConstraints:NO];
		[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeCenterX) relatedBy:(NSLayoutRelationEqual) toItem:_gl_view attribute:(NSLayoutAttributeCenterX) multiplier:1 constant:0]];
		[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeCenterY) relatedBy:(NSLayoutRelationEqual) toItem:_gl_view attribute:(NSLayoutAttributeCenterY) multiplier:1 constant:0]];
		[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeWidth) relatedBy:(NSLayoutRelationEqual) toItem:_gl_view attribute:(NSLayoutAttributeWidth) multiplier:1 constant:0]];
		[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeHeight) relatedBy:(NSLayoutRelationEqual) toItem:_gl_view attribute:(NSLayoutAttributeHeight) multiplier:1 constant:0]];
	}
	return	self;
}
- (void)startDisplayTicking
{
	[_gl_view prepareGraphicsContext];
	
	_disp_timer	=	[NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)1.0/60.0 target:self selector:@selector(displayTimeTick:) userInfo:nil repeats:YES];
}
- (void)stopDisplayTicking
{
	[_disp_timer invalidate];
	
	_disp_timer	=	nil;
	
	[_gl_view cleanupGraphicsContext];
}
- (void)displayTimeTick:(id)sender
{
	[_gl_view setNeedsDisplay:YES];
	
//	CGRect	b	=	_gl_view.frame;
//	NSLog(@"%@", NSStringFromRect(b));
}
@end












#endif // EONIL_MEDIA_ENGINE_TARGET_OSX