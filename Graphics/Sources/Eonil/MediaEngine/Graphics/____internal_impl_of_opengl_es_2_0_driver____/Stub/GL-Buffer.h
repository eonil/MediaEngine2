//
//  GL-Buffer.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#pragma once
#include "GL-Common.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Stub
{
	
	
	
	
	
	
	
	
	EEGL_STUB_API_DECO GLboolean	eeglIsBuffer(GLuint buffer);
	
	EEGL_STUB_API_DECO void			eeglGetBufferParameteriv(GLenum target, GLenum pname, GLint* const params);
	EEGL_STUB_API_DECO GLint		eeglGetBufferParameteri(GLenum target, GLenum pname);
	
	
	
	
	////
	
	EEGL_STUB_API_DECO void			eeglGenBuffers(GLsizei n, GLuint * buffers);
	EEGL_STUB_API_DECO GLuint		eeglGenBuffer();
	EEGL_STUB_API_DECO void			eeglDeleteBuffers(GLsizei n, GLuint const * buffers);
	EEGL_STUB_API_DECO void			eeglDeleteBuffer(GLuint name);
	
	EEGL_STUB_API_DECO void			eeglBindBuffer(GLenum target, GLuint buffer);
	EEGL_STUB_API_DECO void			eeglUnbindBufer(GLenum target);
	
	EEGL_STUB_API_DECO void			eeglBufferData(GLenum target, GLsizeiptr size, GLvoid const * data, GLenum usage);
	EEGL_STUB_API_DECO void			eeglBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid const * data);
	

	
	
	
	
	
	
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END













