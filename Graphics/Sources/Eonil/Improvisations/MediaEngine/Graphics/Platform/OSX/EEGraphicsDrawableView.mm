//
//  EEGraphicsDrawableView.m
//  Graphics
//
//  Created by Hoon H. on 2/16/14.
//
//

#import "EEGraphicsDrawableView.h"

#if	EONIL_MEDIA_ENGINE_TARGET_OSX








//#include "BridgingController.h"

//using namespace Eonil::Improvisations::MediaEngine::Graphics::Platform::iOS;

#include "../../Stub/GL-Common.h"
//#include "../../Stub/GL-Buffer.h"
#include "../../Stub/GL-Framebuffer.h"
#include "../../Stub/GL-Renderbuffer.h"
#include "../../Server/ServerObjectProxy.h"
#include "../../Server/Framebuffer.h"

using namespace	Eonil::Improvisations::MediaEngine::Graphics;
using namespace	Eonil::Improvisations::MediaEngine::Graphics::Stub;
using namespace	Eonil::Improvisations::MediaEngine::Graphics::Server;








//@implementation EEGraphicsDrawableView
//{
//}
//
//- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)format
//{
//	/*
//	 This method shouldn't be deleted because this will be called by the superclass, and any exception will be silently
//	 ignored.
//	 */
//	if (self = [super initWithFrame:frameRect pixelFormat:format])
//	{
//	}
//	return	self;
//}
//- (id)initWithFrame:(CGRect)frame
//{
//	self	=	[super initWithFrame:frame];
//	if (self)
//	{
//	}
//	return	self;
//}
//- (id)init
//{
//	return	[self initWithFrame:CGRectZero];
//}
//- (void)dealloc
//{
//}
//
//- (void)prepareGraphicsContext
//{
//	
//}
//- (void)cleanupGraphicsContext
//{
//
//}
//- (void)presentRenderbuffer
//{
//
//}
//
//
//
//- (void)drawRect:(NSRect)dirtyRect
//{
//	EONIL_DEBUG_ASSERT([[NSThread currentThread] isEqual:[NSThread mainThread]]);
//	EONIL_DEBUG_ASSERT(self.superview.wantsLayer);
//	EONIL_DEBUG_ASSERT(self.superview.layer != nil);
//	
//	////
//	
//	[super drawRect:dirtyRect];
//	
//	////
//	
//	{
//		[self.openGLContext makeCurrentContext];
//		Renderbuffer	rb1		{Renderbuffer::FORMAT::DEPTH16, self.frame.size.width, self.frame.size.height};
//		eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb1.name());
//		self._draw();
//		[self.openGLContext flushBuffer];
//		eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
//	}
//}
//@end
















@implementation EEGraphicsDrawableView2 
{
	NSOpenGLContext*	_gl_ctx;
}
- (id)initWithFrame:(CGRect)frame
{
	self	=	[super initWithFrame:frame];
	if (self)
	{
		NSOpenGLPixelFormatAttribute	SENTINEL		=	0;
		NSOpenGLPixelFormatAttribute	pfas[]			=
		{
			NSOpenGLPFADoubleBuffer,
//			NSOpenGLPFAOpenGLProfile,	NSOpenGLProfileVersion3_2Core,
			/*!
			 It is very important that OpenGL 3.2+ is not compatible with
			 OpenGL ES 2.0, and the behavioral differences will lead program to crash.
			 So always use *legacy* profile. 
			 
			 GLSL ES 1.00 is very close to GLSL (DT) 1.2. GLSL (DT) 1.1 and 1.2 is almost
			 compatible, just revision update. GLSL (DT) 1.3+ is a new langauge, so it's
			 not compatible.
			 
			 @ref
			 http://stackoverflow.com/questions/10345323/is-opengl-backwards-compatible-with-opengl-es
			 */
			NSOpenGLPFAOpenGLProfile,	NSOpenGLProfileVersionLegacy,
			NSOpenGLPFAColorSize,		24,
			NSOpenGLPFAAlphaSize,		8,
			NSOpenGLPFADepthSize,		24,
			NSOpenGLPFAStencilSize,		8,
			NSOpenGLPFASampleBuffers,	1,
			NSOpenGLPFAMultisample,		
			NSOpenGLPFASamples,			4,
			NSOpenGLPFADoubleBuffer,
			SENTINEL,
		};
		
		NSOpenGLPixelFormat*			pf1				=	[[NSOpenGLPixelFormat alloc] initWithAttributes:pfas];
		
		_gl_ctx	=	[[NSOpenGLContext alloc] initWithFormat:pf1 shareContext:nil];
	}
	return	self;
}
- (void)prepareGraphicsContext
{
	EONIL_DEBUG_ASSERT_WITH_MESSAGE([self.window isKindOfClass:[NSWindow class]], "This method must be called while this view is placed on a visible `UIWindow` to configure OpenGL rendering surface properly.");
	EONIL_DEBUG_ASSERT(_gl_ctx != nil);
	
	[_gl_ctx setView:self];
	[_gl_ctx makeCurrentContext];
}
- (void)cleanupGraphicsContext
{
	EONIL_DEBUG_ASSERT_WITH_MESSAGE([self.window isKindOfClass:[NSWindow class]], "This method must be called while this view is placed on a visible `UIWindow` to be matched with `prepareGraphicsContext` method.");
	EONIL_DEBUG_ASSERT(_gl_ctx != nil);
	
	[_gl_ctx setView:nil];
	[NSOpenGLContext clearCurrentContext];
}
- (void)presentRenderbuffer
{
	EONIL_DEBUG_ASSERT([_gl_ctx view] == self);
	EONIL_DEBUG_ASSERT([_gl_ctx isEqual:[NSOpenGLContext currentContext]]);
	
	[_gl_ctx flushBuffer];
}
- (void)setFrame:(NSRect)frameRect
{
	[super setFrame:frameRect];
	[_gl_ctx update];
}
@end


























#endif // EONIL_MEDIA_ENGINE_TARGET_OSX