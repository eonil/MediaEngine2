//
//  EEGraphicsDrawableView.m
//  Graphics
//
//  Created by Hoon H. on 2/10/14.
//
//

#import "EEGraphicsDrawableView.h"

#if	EONIL_MEDIA_ENGINE_TARGET_IOS








//#include "BridgingController.h"

//using namespace Eonil::Improvisations::MediaEngine::Graphics::Platform::iOS;



//#import <OpenGLES/EAGL.h>

#include "../../Stub/GL-Common.h"
//#include "../../Stub/GL-Buffer.h"
#include "../../Stub/GL-Framebuffer.h"
#include "../../Stub/GL-Renderbuffer.h"
#include "../../Server/ServerObjectProxy.h"

using namespace	Eonil::Improvisations::MediaEngine::Graphics;
using namespace	Eonil::Improvisations::MediaEngine::Graphics::Stub;








@implementation EEGraphicsDrawableView
{
	EAGLContext*			_ctx;
	
	GLuint					_fbmain;
	GLuint					_rbcolor;
	GLuint					_rbdepth;
}
- (id)initWithFrame:(CGRect)frame
{
	self	=	[super initWithFrame:frame];
	if (self)
	{
	}
	return	self;
}
- (void)dealloc
{
	EONIL_DEBUG_ASSERT(_fbmain == 0);
	EONIL_DEBUG_ASSERT(_rbcolor == 0);
	EONIL_DEBUG_ASSERT(_rbdepth == 0);
}

- (void)prepareGraphicsContext
{
	EONIL_DEBUG_ASSERT(_fbmain == 0);
	EONIL_DEBUG_ASSERT(_rbcolor == 0);
	EONIL_DEBUG_ASSERT(_rbdepth == 0);
	
	CAEAGLLayer*	_layer2	=	(id)self.layer;
	
	_ctx	=	[[EAGLContext alloc] initWithAPI:(kEAGLRenderingAPIOpenGLES2) sharegroup:nil];
	
	GLsizei	width	=	_layer2.bounds.size.width * _layer2.contentsScale;
	GLsizei	height	=	_layer2.bounds.size.height * _layer2.contentsScale;
	
	[EAGLContext setCurrentContext:_ctx];
	
	glGenFramebuffers(1, &_fbmain);
	glBindFramebuffer(GL_FRAMEBUFFER, _fbmain);
	
	_rbcolor	=	eeglGenRenderbuffer();
	eeglBindRenderbuffer(GL_RENDERBUFFER, _rbcolor);
	BOOL	ok	=	[_ctx renderbufferStorage:GL_RENDERBUFFER fromDrawable:_layer2];
	EONIL_DEBUG_ASSERT_WITH_MESSAGE(ok, "Cannot initialize system-provided OpenGL ES 2.0 render-buffer storage.");
	eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _rbcolor);
	eeglUnbindRenderbuffer(GL_RENDERBUFFER);
	
	_rbdepth	=	eeglGenRenderbuffer();
	eeglBindRenderbuffer(GL_RENDERBUFFER, _rbdepth);
	eeglRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
	eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rbdepth);
	eeglUnbindRenderbuffer(GL_RENDERBUFFER);
}
- (void)cleanupGraphicsContext
{
	EONIL_DEBUG_ASSERT(_fbmain != 0);
	EONIL_DEBUG_ASSERT(_rbcolor != 0);
	EONIL_DEBUG_ASSERT(_rbdepth != 0);
	
	eeglBindRenderbuffer(GL_RENDERBUFFER, _rbdepth);
	eeglDeleteRenderbuffer(_rbdepth);
	eeglUnbindRenderbuffer(GL_RENDERBUFFER);
	
	eeglBindRenderbuffer(GL_RENDERBUFFER, _rbcolor);
	BOOL	ok	=	[_ctx renderbufferStorage:GL_RENDERBUFFER fromDrawable:nil];
	EONIL_DEBUG_ASSERT_WITH_MESSAGE(ok, "Cannot cleanup system-provided OpenGL ES 2.0 render-buffer storage.");
	eeglDeleteRenderbuffers(1, &_rbcolor);
	eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, 0);
//	eeglUnbindRenderbuffer(GL_RENDERBUFFER);
	
	glBindFramebuffer(GL_FRAMEBUFFER, _fbmain);
	glDeleteFramebuffers(1, &_fbmain);
	
	[EAGLContext setCurrentContext:nil];
	
	_ctx	=	nil;
}
- (void)presentRenderbuffer
{
	EONIL_DEBUG_ASSERT(_fbmain != 0);
	EONIL_DEBUG_ASSERT(_rbcolor != 0);
	EONIL_DEBUG_ASSERT(_rbdepth != 0);
	
	eeglBindRenderbuffer(GL_RENDERBUFFER, _rbcolor);
	[_ctx presentRenderbuffer:GL_RENDERBUFFER];
	eeglUnbindRenderbuffer(GL_RENDERBUFFER);
}


+ (Class)layerClass
{
	return	[CAEAGLLayer class];
}
@end


















#endif // EONIL_MEDIA_ENGINE_TARGET_IOS