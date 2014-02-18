//
//  AAAppDelegate.m
//  OSXTester
//
//  Created by Hoon ; on 6/19/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//


#include "AATestStatus.h"
#include "AATestRendering0.h"
#include "AATestRendering1.h"
#include "AATestRendering2.h"

#import "AAAppDelegate.h"



using namespace	Eonil::Improvisations::MediaEngine::Graphics;
using namespace	Eonil::Improvisations::MediaEngine::Graphics::Stub;
using namespace	Eonil::Improvisations::MediaEngine::Graphics::Value;
using namespace	Eonil::Improvisations::MediaEngine::Graphics::Server;

@implementation AAAppDelegate
{
	NSWindow*		_win;
	NSOpenGLView*	_glV;
	NSTimer*		_tmr;
}
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	_win	=	[[NSWindow alloc] init];
	
	[_win setFrame:NSRectFromCGRect(CGRectMake(200, 200, 400, 400)) display:YES];
	[_win makeKeyAndOrderFront:self];
	
	_glV	=	[[AATestGLView alloc] init];
	[_win.contentView addSubview:_glV];
	
	NSView*	cv	=	_win.contentView;
	cv.wantsLayer	=	YES;
	cv.layer		=	[[CALayer alloc] init];
	cv.layer.backgroundColor	=	[NSColor redColor].CGColor;
	
	_glV.translatesAutoresizingMaskIntoConstraints	=	NO;
	[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeCenterX) relatedBy:(NSLayoutRelationEqual) toItem:_glV attribute:(NSLayoutAttributeCenterX) multiplier:1 constant:0]];
	[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeCenterY) relatedBy:(NSLayoutRelationEqual) toItem:_glV attribute:(NSLayoutAttributeCenterY) multiplier:1 constant:0]];
	[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeWidth) relatedBy:(NSLayoutRelationEqual) toItem:_glV attribute:(NSLayoutAttributeWidth) multiplier:1 constant:0]];
	[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeHeight) relatedBy:(NSLayoutRelationEqual) toItem:_glV attribute:(NSLayoutAttributeHeight) multiplier:1 constant:0]];
	
	[NSTimer scheduledTimerWithTimeInterval:1.0/60.0 target:self selector:@selector(tick:) userInfo:nil repeats:YES];
}
- (void)tick:(id)sender
{
	[_glV setNeedsDisplay:YES];
}
@end













@implementation AATestGLView
- (void)drawRect:(NSRect)dirtyRect
{
	
	////
	
	{
		Renderbuffer	rb1		{Renderbuffer::FORMAT::DEPTH16, self.frame.size.width, self.frame.size.height};
		eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb1.name());
		
		//		GLuint	db_name;
		//		eeglGenRenderbuffers(1, &db_name);
		//		eeglBindRenderbuffer(GL_RENDERBUFFER, db_name);
		//		eeglRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, self.frame.size.width, self.frame.size.height);
		//		eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, db_name);
		
		{
			TestStatus();
			
			TestClearScreen();
			TestRenderingWithOnlyVertexesInClientMemory();
			TestRenderingWithOnlyVertexesInServerMemory();
			TestRenderingWithVertexesAndIndexesInClientMemory();
			TestRenderingWithVertexesAndIndexesInServerMemory();
			TestRendering1RenderingWithTransform();
			
			NSString*		fp0		=	[[NSBundle mainBundle] pathForResource:@"02" ofType:@"png"];
			PlanarTexture	tex		=	Server::PlanarTexture::Utility::textureWithContentOfFileAtPath(fp0.UTF8String);
			TestRendering2RenderingWithTexture(tex);
			
			[self.openGLContext flushBuffer];
		}
		eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
		
		//		eeglDeleteRenderbuffer(db_name);
	}
	
	////
	
	{
		size_t	numobj	=	Eonil::Improvisations::Debug::ObjectInstanceAddressTracker<ArrayBuffer>::allObjectAddresses().size();
		EONIL_TEST_ASSERT(numobj == 0);
	}
	{
		size_t	numobj	=	Eonil::Improvisations::Debug::ObjectInstanceAddressTracker<ElementArrayBuffer>::allObjectAddresses().size();
		EONIL_TEST_ASSERT(numobj == 0);
	}
	{
		size_t	numobj	=	Eonil::Improvisations::Debug::ObjectInstanceAddressTracker<Program>::allObjectAddresses().size();
		EONIL_TEST_ASSERT(numobj == 0);
	}
	
}
@end























































////
////  AAAppDelegate.m
////  OSXTester
////
////  Created by Hoon ; on 6/19/13.
////  Copyright (c) 2013 Eonil. All rights reserved.
////
//
//
//#include "AATestStatus.h"
//#include "AATestRendering0.h"
//#include "AATestRendering1.h"
//#include "AATestRendering2.h"
//
//#import "AAAppDelegate.h"
//
//
//
//using namespace	Eonil::Improvisations::MediaEngine::Graphics;
//using namespace	Eonil::Improvisations::MediaEngine::Graphics::Stub;
//using namespace	Eonil::Improvisations::MediaEngine::Graphics::Value;
//using namespace	Eonil::Improvisations::MediaEngine::Graphics::Server;
//
//@implementation AAAppDelegate
//{
//	NSWindow*		_win;
//	EEGraphicsDrawableView*	_glV;
//	NSTimer*		_tmr;
//}
//- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
//{	
//	_win	=	[[NSWindow alloc] init];
//	
//	[_win setFrame:NSRectFromCGRect(CGRectMake(200, 200, 400, 400)) display:YES];
//	[_win makeKeyAndOrderFront:self];
//	
//	_glV	=	[[EEGraphicsDrawableView alloc] initWithFrame:NSRectFromCGRect(CGRectMake(200, 200, 400, 400))];
//	_glV._draw = ^()
//	{
//		TestStatus();
//		
//		TestClearScreen();
//		TestRenderingWithOnlyVertexesInClientMemory();
//		TestRenderingWithOnlyVertexesInServerMemory();
//		TestRenderingWithVertexesAndIndexesInClientMemory();
//		TestRenderingWithVertexesAndIndexesInServerMemory();
//		TestRendering1RenderingWithTransform();
//		
//		NSString*		fp0		=	[[NSBundle mainBundle] pathForResource:@"02" ofType:@"png"];
//		PlanarTexture	tex		=	Server::PlanarTexture::Utility::_DEV_textureWithFileAtPath(fp0.UTF8String);
//		TestRendering2RenderingWithTexture(tex);
//		
//		////
//		
//		{
//			size_t	numobj	=	Eonil::Improvisations::Debug::ObjectInstanceAddressTracker<ArrayBuffer>::allObjectAddresses().size();
//			EONIL_TEST_ASSERT(numobj == 0);
//		}
//		{
//			size_t	numobj	=	Eonil::Improvisations::Debug::ObjectInstanceAddressTracker<ElementArrayBuffer>::allObjectAddresses().size();
//			EONIL_TEST_ASSERT(numobj == 0);
//		}
//		{
//			size_t	numobj	=	Eonil::Improvisations::Debug::ObjectInstanceAddressTracker<Program>::allObjectAddresses().size();
//			EONIL_TEST_ASSERT(numobj == 0);
//		}
//	};
//	
//	NSView*	cv	=	_win.contentView;
//	cv.wantsLayer				=	YES;
//	cv.layer					=	[[CALayer alloc] init];
//	cv.layer.backgroundColor	=	[NSColor redColor].CGColor;
//	
//	[_win.contentView addSubview:_glV];
//	
//	_glV.translatesAutoresizingMaskIntoConstraints	=	NO;
//	[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeCenterX) relatedBy:(NSLayoutRelationEqual) toItem:_glV attribute:(NSLayoutAttributeCenterX) multiplier:1 constant:0]];
//	[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeCenterY) relatedBy:(NSLayoutRelationEqual) toItem:_glV attribute:(NSLayoutAttributeCenterY) multiplier:1 constant:0]];
//	[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeWidth) relatedBy:(NSLayoutRelationEqual) toItem:_glV attribute:(NSLayoutAttributeWidth) multiplier:1 constant:0]];
//	[cv addConstraint:[NSLayoutConstraint constraintWithItem:cv attribute:(NSLayoutAttributeHeight) relatedBy:(NSLayoutRelationEqual) toItem:_glV attribute:(NSLayoutAttributeHeight) multiplier:1 constant:0]];
//	
//	[NSTimer scheduledTimerWithTimeInterval:1.0/60.0 target:self selector:@selector(tick:) userInfo:nil repeats:YES];
//}
//- (void)tick:(id)sender
//{
//	[_glV setNeedsDisplay:YES];
//}
//@end
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
////@implementation AATestGLView
////- (void)drawRect:(NSRect)dirtyRect
////{
////
////	////
////
////	GLuint	db_name;
////	eeglGenRenderbuffers(1, &db_name);
////	eeglBindRenderbuffer(GL_RENDERBUFFER, db_name);
////	eeglRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, self.frame.size.width, self.frame.size.height);
////	eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, db_name);
////
////	{
////		TestStatus();
////
////		TestClearScreen();
////		TestRenderingWithOnlyVertexesInClientMemory();
////		TestRenderingWithOnlyVertexesInServerMemory();
////		TestRenderingWithVertexesAndIndexesInClientMemory();
////		TestRenderingWithVertexesAndIndexesInServerMemory();
////		TestRendering1RenderingWithTransform();
////
////		NSString*		fp0		=	[[NSBundle mainBundle] pathForResource:@"02" ofType:@"png"];
////		PlanarTexture	tex		=	Server::PlanarTexture::Utility::_DEV_textureWithFileAtPath(fp0.UTF8String);
////		TestRendering2RenderingWithTexture(tex);
////
////		[self.openGLContext flushBuffer];
////	}
////	eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
////	eeglDeleteRenderbuffer(db_name);
////
////	////
////
////	{
////		size_t	numobj	=	Eonil::Improvisations::Debug::ObjectInstanceAddressTracker<ArrayBuffer>::allObjectAddresses().size();
////		EONIL_TEST_ASSERT(numobj == 0);
////	}
////	{
////		size_t	numobj	=	Eonil::Improvisations::Debug::ObjectInstanceAddressTracker<ElementArrayBuffer>::allObjectAddresses().size();
////		EONIL_TEST_ASSERT(numobj == 0);
////	}
////	{
////		size_t	numobj	=	Eonil::Improvisations::Debug::ObjectInstanceAddressTracker<Program>::allObjectAddresses().size();
////		EONIL_TEST_ASSERT(numobj == 0);
////	}
////
////}
////@end
//
//
