//
//  GL-Framebuffer.cpp
//  EonilGraphics
//
//  Created by Eonil on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "GL-Framebuffer.h"

#include "GL-Get.h"
#include "GL-Renderbuffer.h"


namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Stub
	{
		
		
		
		EEGL_INLINE void
		eeglGenFramebuffers(GLsizei const n, GLuint* const framebuffers)
		{
			glGenFramebuffers(n, framebuffers);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglDeleteFramebuffers(GLsizei const n, GLuint const* const framebuffers)
		{
			glDeleteFramebuffers(n, framebuffers);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_INLINE GLuint const
		eeglGenFramebuffer()
		{
			GLuint	n;
			eeglGenFramebuffers(1, &n);
			return	n;
		}
		EEGL_INLINE void
		eeglDeleteFramebuffer(GLuint const framebuffer)
		{
			eeglDeleteFramebuffers(1, &framebuffer);
		}
		
		
		
		
		
		
		
		
		
		
		
		EEGL_INLINE void
		eeglBindFramebuffer(GLenum const target, GLuint const framebuffer)
		{
			EEGL_ASSERT(target == GL_FRAMEBUFFER);
//#if not EEGL_IGNORE_ZERO_FRAMEBUFFER_NAME
			EEGL_ASSERT(framebuffer != 0);
//#endif
			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUnbindFramebuffer(GLenum const target)
		{
			EEGL_ASSERT(target == GL_FRAMEBUFFER);
			glBindFramebuffer(target, 0);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		

		EEGL_INLINE void
		eeglFramebufferTexture2D(GLenum const target, GLenum const attachment, GLenum const textarget, GLuint const texture, GLint const level)
		{
			EEGL_ASSERT(target == GL_FRAMEBUFFER);
			EEGL_ASSERT(attachment == GL_COLOR_ATTACHMENT0 or
									 attachment == GL_DEPTH_ATTACHMENT or
									 attachment == GL_STENCIL_ATTACHMENT);
			EEGL_ASSERT(textarget == GL_TEXTURE_2D or
									 textarget == GL_TEXTURE_CUBE_MAP_POSITIVE_X or
									 textarget == GL_TEXTURE_CUBE_MAP_NEGATIVE_X or
									 textarget == GL_TEXTURE_CUBE_MAP_POSITIVE_Y or
									 textarget == GL_TEXTURE_CUBE_MAP_NEGATIVE_Y or
									 textarget == GL_TEXTURE_CUBE_MAP_POSITIVE_Z or
									 textarget == GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
			EEGL_ASSERT(level == 0);
			glFramebufferTexture2D(target, attachment, textarget, texture, level);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglFramebufferRenderbuffer(GLenum const target, GLenum const attachment, GLenum const renderbuffertarget, GLuint const renderbuffer)
		{
			EEGL_ASSERT(target == GL_FRAMEBUFFER);
			EEGL_ASSERT(attachment == GL_COLOR_ATTACHMENT0 or
									 attachment == GL_DEPTH_ATTACHMENT or
									 attachment == GL_STENCIL_ATTACHMENT);
			EEGL_ASSERT(renderbuffertarget == GL_RENDERBUFFER);
			
//#if not EEGL_IGNORE_ZERO_FRAMEBUFFER_NAME
			EEGL_ASSERT(eeglGetInteger(GL_FRAMEBUFFER_BINDING) != 0);
//#endif
			EEGL_ASSERT(renderbuffer == 0 or eeglIsRenderbuffer(renderbuffer));
			
			glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
			EEGL_ASSERT_NO_GL_ERROR();
		}

		
		
		
		
		
		
		
		
		
		
		EEGL_INLINE GLenum const
		eeglCheckFramebufferStatus(GLenum const target)
		{
			EEGL_ASSERT(target == GL_FRAMEBUFFER);
			GLenum const	value	=	glCheckFramebufferStatus(target);
			EEGL_ASSERT_NO_GL_ERROR();
			EEGL_ASSERT(value == GL_FRAMEBUFFER_COMPLETE);
			return	value;
		}
	}
	
	
	
	
	
	
	
}}}}