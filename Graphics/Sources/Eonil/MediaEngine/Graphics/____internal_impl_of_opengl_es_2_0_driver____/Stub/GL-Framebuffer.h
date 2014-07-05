//
//  GL-Framebuffer.h
//  EonilGraphics
//
//  Created by Eonil on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#pragma once
#include "GL-Common.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Stub
{	
	
	EEGL_STUB_API_DECO void					eeglGetFramebufferAttachmentParameteriv(GLenum const target, GLenum const attachment, GLenum const pname, GLint* const params);
	EEGL_STUB_API_DECO GLint const			eeglGetFramebufferAttachmentParameteri(GLenum const target, GLenum const attachment, GLenum const pname);
	

	
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

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END
