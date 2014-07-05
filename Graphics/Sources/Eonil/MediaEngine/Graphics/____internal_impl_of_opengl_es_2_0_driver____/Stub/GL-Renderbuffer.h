//
//  GL-Renderbuffer.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/1/13.
//
//

#pragma once
#include "GL-Common.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Stub
{
	EEGL_STUB_API_DECO void			eeglGetRenderbufferParameteriv(GLenum const target, GLenum const pname, GLint* const params);
	EEGL_STUB_API_DECO GLint const	eeglGetRenderbufferParameteri(GLenum const target, GLenum const pname);
	
	
	EEGL_STUB_API_DECO void			eeglGenRenderbuffers(GLsizei const n, GLuint* const renderbuffers);
	EEGL_STUB_API_DECO void			eeglDeleteRenderbuffers(GLsizei const n, GLuint const* const renderbuffers);
	
	EEGL_STUB_API_DECO GLuint const	eeglGenRenderbuffer();
	EEGL_STUB_API_DECO void			eeglDeleteRenderbuffer(GLuint const renderbuffer);
	
	EEGL_STUB_API_DECO void			eeglBindRenderbuffer(GLenum const target, GLuint const renderbuffer);
	EEGL_STUB_API_DECO void			eeglUnbindRenderbuffer(GLenum const target);
	
	EEGL_STUB_API_DECO void			eeglRenderbufferStorage(GLenum const target, GLenum const internalformat, GLsizei const width, GLsizei const height);
	
	
	
	EEGL_STUB_API_DECO GLboolean const	eeglIsRenderbuffer(GLuint const renderbuffer);
	
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END




