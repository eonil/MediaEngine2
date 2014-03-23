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
#include "../../Stub/GL-Get.h"
//#include "../../Stub/GL-Buffer.h"
#include "../../Stub/GL-Framebuffer.h"
#include "../../Stub/GL-Renderbuffer.h"
#include "../../Server/ServerObjectProxy.h"

using namespace	Eonil::Improvisations::MediaEngine::Graphics;
using namespace	Eonil::Improvisations::MediaEngine::Graphics::Stub;


namespace
{
	class
	GLManagerPlain
	{
		GLuint		_fbmain		{0};					//	Rendering target buffer.
		GLuint		_rbcolor	{0};
		GLuint		_rbdepth	{0};
		
		
	public:
		using		PROC	=	std::function<void(void)>;
		
		struct
		SystemCall
		{
			PROC		init	{};
			PROC		term	{};
			PROC		step	{};
		};
		
		SystemCall	_syscall	{};
		
	public:
		GLManagerPlain(GLsizei width, GLsizei height, SystemCall const& syscall) : _syscall(syscall)
		{			
			glGenFramebuffers(1, &_fbmain);
			glBindFramebuffer(GL_FRAMEBUFFER, _fbmain);
			
			_rbcolor	=	eeglGenRenderbuffer();
			eeglBindRenderbuffer(GL_RENDERBUFFER, _rbcolor);
			
			_syscall.init();
			
			eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _rbcolor);
			eeglUnbindRenderbuffer(GL_RENDERBUFFER);
			
			_rbdepth	=	eeglGenRenderbuffer();
			eeglBindRenderbuffer(GL_RENDERBUFFER, _rbdepth);
			eeglRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
			eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rbdepth);
			eeglUnbindRenderbuffer(GL_RENDERBUFFER);
		}
		~GLManagerPlain()
		{
			eeglBindRenderbuffer(GL_RENDERBUFFER, _rbdepth);
			eeglDeleteRenderbuffer(_rbdepth);
			eeglUnbindRenderbuffer(GL_RENDERBUFFER);
			
			eeglBindRenderbuffer(GL_RENDERBUFFER, _rbcolor);
			
			_syscall.term();
			
			eeglDeleteRenderbuffers(1, &_rbcolor);
			eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, 0);
//			eeglUnbindRenderbuffer(GL_RENDERBUFFER);
			
			glBindFramebuffer(GL_FRAMEBUFFER, _fbmain);
			glDeleteFramebuffers(1, &_fbmain);
			
		}
		
		auto
		present() const -> void
		{
			eeglBindRenderbuffer(GL_RENDERBUFFER, _rbcolor);
			_syscall.step();
			eeglUnbindRenderbuffer(GL_RENDERBUFFER);
		}
	};
	
	
	class
	GLManagerWithMSAA
	{
		GLuint		_fb_main_sampling	{0};
		GLuint		_rb_color_sampling	{0};
		GLuint		_rb_depth_sampling	{0};
		
		GLuint		_fbmain		{0};					//	Rendering target buffer.
		GLuint		_rbcolor	{0};
		GLuint		_rbdepth	{0};
		
		
		
	public:
		using		PROC	=	std::function<void(void)>;
		
		struct
		SystemCall
		{
			PROC		init	{};
			PROC		term	{};
			PROC		step	{};
		};
		
		SystemCall	_syscall	{};
		
	public:
		GLManagerWithMSAA(GLsizei width, GLsizei height, SystemCall const& syscall) : _syscall(syscall)
		{
			/*!
			 Any other value will not be accepted by the OS.
			 */
			static GLsizei const	IOS_DEFAULT_MULTISAMPLING_COUNT	=	4;
			
			{
				_fb_main_sampling	=	eeglGenFramebuffer();
				_rb_color_sampling	=	eeglGenRenderbuffer();
				_rb_depth_sampling	=	eeglGenRenderbuffer();
				
				{
					eeglBindFramebuffer(GL_FRAMEBUFFER, _fb_main_sampling);
					{
						eeglBindRenderbuffer(GL_RENDERBUFFER, _rb_color_sampling);
						glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, IOS_DEFAULT_MULTISAMPLING_COUNT, GL_RGBA8_OES, width, height);
						EEGL_ASSERT_NO_GL_ERROR();
						eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _rb_color_sampling);
						eeglUnbindRenderbuffer(GL_RENDERBUFFER);
					}
					{
						eeglBindRenderbuffer(GL_RENDERBUFFER, _rb_depth_sampling);
						glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, IOS_DEFAULT_MULTISAMPLING_COUNT, GL_DEPTH_COMPONENT16, width, height);
						EEGL_ASSERT_NO_GL_ERROR();
						eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rb_depth_sampling);
						eeglUnbindRenderbuffer(GL_RENDERBUFFER);
					}
					eeglCheckFramebufferStatus(GL_FRAMEBUFFER);
					eeglUnbindFramebuffer(GL_FRAMEBUFFER);
				}
			}
			
			_fbmain	=	eeglGenFramebuffer();
			eeglBindFramebuffer(GL_FRAMEBUFFER, _fbmain);
			
			_rbcolor	=	eeglGenRenderbuffer();
			eeglBindRenderbuffer(GL_RENDERBUFFER, _rbcolor);
			
			_syscall.init();
			
			eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _rbcolor);
			eeglUnbindRenderbuffer(GL_RENDERBUFFER);
			
			_rbdepth	=	eeglGenRenderbuffer();
			eeglBindRenderbuffer(GL_RENDERBUFFER, _rbdepth);
			eeglRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
			eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _rbdepth);
			eeglUnbindRenderbuffer(GL_RENDERBUFFER);
			
			////
			
			eeglBindFramebuffer(GL_FRAMEBUFFER, _fb_main_sampling);
		}
		~GLManagerWithMSAA()
		{
			eeglUnbindFramebuffer(GL_FRAMEBUFFER);
			
			////
			
			eeglBindRenderbuffer(GL_RENDERBUFFER, _rbdepth);
			eeglDeleteRenderbuffer(_rbdepth);
			eeglUnbindRenderbuffer(GL_RENDERBUFFER);
			
			eeglBindRenderbuffer(GL_RENDERBUFFER, _rbcolor);
			
			_syscall.term();
			
			eeglDeleteRenderbuffers(1, &_rbcolor);
			eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, 0);
			//	eeglUnbindRenderbuffer(GL_RENDERBUFFER);
			
			eeglBindFramebuffer(GL_FRAMEBUFFER, _fbmain);
			eeglDeleteFramebuffer(_fbmain);
		}
		
		auto
		present() const -> void
		{
			eeglUnbindFramebuffer(GL_FRAMEBUFFER);
			
			/*
			 Resolve samples to final color buffer.
			 */
			{
				glBindFramebuffer(GL_READ_FRAMEBUFFER_APPLE, _fb_main_sampling);
				EEGL_ASSERT_NO_GL_ERROR();
				
				glBindFramebuffer(GL_DRAW_FRAMEBUFFER_APPLE, _fbmain);
				EEGL_ASSERT_NO_GL_ERROR();
				
				glResolveMultisampleFramebufferAPPLE();
				EEGL_ASSERT_NO_GL_ERROR();
			
				vec<GLenum>	discarding_buffers	=	{GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT};
				glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, discarding_buffers.size(), discarding_buffers.data());
			}
			
			/*
			 Blit!
			 */
			{
//				EONIL_DEBUG_ASSERT(eeglGetInteger(GL_FRAMEBUFFER_BINDING) == _fbmain);
				eeglBindFramebuffer(GL_FRAMEBUFFER, _fbmain);
				
				eeglBindRenderbuffer(GL_RENDERBUFFER, _rbcolor);
				_syscall.step();
				eeglUnbindRenderbuffer(GL_RENDERBUFFER);
				
				eeglUnbindFramebuffer(GL_FRAMEBUFFER);
			}
			
			eeglBindFramebuffer(GL_FRAMEBUFFER, _fb_main_sampling);
		}
	};
	
	
	
	
	/*
	 Quick switch!
	 */
	using	GLManager	=	GLManagerWithMSAA;
}




















@implementation EEGraphicsDrawableView
{
	EAGLContext*		_ctx;
	
	BOOL				_wants_multisampling;
	
	uptr<GLManager>		_glman;
}
- (id)init
{
	[self doesNotRecognizeSelector:_cmd];
	return	nil;
}
- (id)initWithFrame:(CGRect)frame
{
	[self doesNotRecognizeSelector:_cmd];
	return	nil;
}
- (id)initWithFrame:(CGRect)frame multisampling:(BOOL)multisampling
{
	self	=	[super initWithFrame:frame];
	if (self)
	{
		_wants_multisampling	=	multisampling;
	}
	return	self;
}
- (void)dealloc
{
	EONIL_DEBUG_ASSERT_WITH_MESSAGE(_glman == nullptr, "`cleanupGraphicsContext` method must be called before killing this object.");
}

- (void)prepareGraphicsContext
{
	EONIL_DEBUG_ASSERT_WITH_MESSAGE([self.window isKindOfClass:[UIWindow class]], "This method must be called while this view is placed on a visible `UIWindow` to configure OpenGL rendering surface properly.");
	EONIL_DEBUG_ASSERT(_glman == nullptr);
	
	CAEAGLLayer*	_layer2	=	(id)self.layer;
	[_layer2 setContentsScale:self.window.screen.scale];
	
	_ctx	=	[[EAGLContext alloc] initWithAPI:(kEAGLRenderingAPIOpenGLES2) sharegroup:nil];
	
	GLsizei	width	=	_layer2.bounds.size.width * _layer2.contentsScale;
	GLsizei	height	=	_layer2.bounds.size.height * _layer2.contentsScale;
	
	[EAGLContext setCurrentContext:_ctx];
	
	////
	
	GLManager::SystemCall	syscall{};
	syscall.init	=	[self, &_layer2]()
	{
		BOOL	ok	=	[_ctx renderbufferStorage:GL_RENDERBUFFER fromDrawable:_layer2];
		EONIL_DEBUG_ASSERT_WITH_MESSAGE(ok, "Cannot initialize system-provided OpenGL ES 2.0 render-buffer storage.");
	};
	syscall.term	=	[self]()
	{
		BOOL	ok	=	[_ctx renderbufferStorage:GL_RENDERBUFFER fromDrawable:nil];
		EONIL_DEBUG_ASSERT_WITH_MESSAGE(ok, "Cannot cleanup system-provided OpenGL ES 2.0 render-buffer storage.");
	};
	syscall.step	=	[self]()
	{
		[_ctx presentRenderbuffer:GL_RENDERBUFFER];
	};
	_glman	=	uptr<GLManager>{new GLManager(width, height, syscall)};
}
- (void)cleanupGraphicsContext
{
	EONIL_DEBUG_ASSERT_WITH_MESSAGE([self.window isKindOfClass:[UIWindow class]], "This method must be called while this view is placed on a visible `UIWindow` to be matched with `prepareGraphicsContext` method.");
	EONIL_DEBUG_ASSERT(_glman != nullptr);
	
	_glman	=	nullptr;
	
	[EAGLContext setCurrentContext:nil];
	
	_ctx	=	nil;
}
- (void)presentRenderbuffer
{
	EONIL_DEBUG_ASSERT(_glman != nullptr);
	
	_glman->present();
}


+ (Class)layerClass
{
	return	[CAEAGLLayer class];
}
@end


















#endif // EONIL_MEDIA_ENGINE_TARGET_IOS