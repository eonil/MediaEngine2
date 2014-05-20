//
//  GL-Framebuffer.h
//  EonilGraphics
//
//  Created by Eonil on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__GL_Framebuffer__
#define __EonilGraphics__GL_Framebuffer__

#include "../Common.h"
#include "GL-Common.h"
#include "../Debugging/Doctor.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Stub
	{
		using namespace Eonil::Improvisations::MediaEngine::Graphics::Debugging;
		
		EEGL_STUB_API_DECO void			eeglGenFramebuffers(GLsizei const n, GLuint* const framebuffers);
		EEGL_STUB_API_DECO void			eeglDeleteFramebuffers(GLsizei const n, GLuint const* const framebuffers);
		
		EEGL_STUB_API_DECO GLuint const	eeglGenFramebuffer();
		EEGL_STUB_API_DECO void			eeglDeleteFramebuffer(GLuint const framebuffer);
		
		
		
		EEGL_STUB_API_DECO void			eeglBindFramebuffer(GLenum const target, GLuint const framebuffer);
		EEGL_STUB_API_DECO void			eeglUnbindFramebuffer(GLenum const target);
		
		
		EEGL_STUB_API_DECO void			eeglFramebufferTexture2D(GLenum const target, GLenum const attachment, GLenum const textarget, GLuint const texture, GLint const level);

		EEGL_STUB_API_DECO void		 	eeglFramebufferRenderbuffer(GLenum const target, GLenum const attachment, GLenum const renderbuffertarget, GLuint const renderbuffer);

		
		
		
		
		
		
		
		
		
		EEGL_STUB_API_DECO GLenum const	eeglCheckFramebufferStatus(GLenum const target);
	}
	
}}}}

#endif /* defined(__EonilGraphics__GL_Framebuffer__) */
