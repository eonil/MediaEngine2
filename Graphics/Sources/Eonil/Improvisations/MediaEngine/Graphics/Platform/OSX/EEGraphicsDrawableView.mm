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








@implementation EEGraphicsDrawableView
{
}

- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat *)format
{
	/*
	 This method shouldn't be deleted because this will be called by the superclass, and any exception will be silently
	 ignored.
	 */
	return	[super initWithFrame:frameRect pixelFormat:format];
}
- (id)initWithFrame:(CGRect)frame
{
	self	=	[super initWithFrame:frame];
	if (self)
	{
	}
	return	self;
}
- (id)init
{
	return	[self initWithFrame:CGRectZero];
}
- (void)dealloc
{
}

- (void)prepareGraphicsContext
{
	
}
- (void)cleanupGraphicsContext
{

}
- (void)presentRenderbuffer
{

}



- (void)drawRect:(NSRect)dirtyRect
{
	EONIL_DEBUG_ASSERT(self.superview.wantsLayer);
	EONIL_DEBUG_ASSERT(self.superview.layer != nil);
	
	////
	
	[super drawRect:dirtyRect];
	
	////
	
	{
		Renderbuffer	rb1		{Renderbuffer::FORMAT::DEPTH16, self.frame.size.width, self.frame.size.height};
		eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb1.name());
		self._draw();
		[self.openGLContext flushBuffer];
		eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
	}
}
@end


















#endif // EONIL_MEDIA_ENGINE_TARGET_OSX