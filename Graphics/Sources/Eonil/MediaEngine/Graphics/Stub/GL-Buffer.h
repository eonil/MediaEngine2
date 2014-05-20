//
//  GL-Buffer.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__GL_Buffer__
#define __EonilGraphics__GL_Buffer__

#include "GL-Common.h"
#include "GL-Get.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Stub
	{
		EEGL_STUB_API_DECO void			eeglGetBufferParameteriv(GLenum const target, GLenum const pname, GLint* const params);
		EEGL_STUB_API_DECO GLint const		eeglGetBufferParameteri(GLenum const target, GLenum const pname);
		
		
		
		
		////
		
		EEGL_STUB_API_DECO void			eeglGenBuffers(GLsizei const n, GLuint* const buffers);
		EEGL_STUB_API_DECO GLuint const	eeglGenBuffer();
		EEGL_STUB_API_DECO void			eeglDeleteBuffers(GLsizei const n, GLuint const* const buffers);
		EEGL_STUB_API_DECO void			eeglDeleteBuffer(GLuint const name);
		
		EEGL_STUB_API_DECO void			eeglBindBuffer(GLenum const target, GLuint const buffer);
		EEGL_STUB_API_DECO void			eeglUnbindBufer(GLenum const target);
		
		EEGL_STUB_API_DECO void			eeglBufferData(GLenum const target, GLsizeiptr const size, GLvoid const * const data, GLenum const usage);
		EEGL_STUB_API_DECO void			eeglBufferSubData(GLenum const target, GLintptr const offset, GLsizeiptr const size, GLvoid const * const data);
		

		
		
		
		
		
		
	}
	
	
}}}}

#endif /* defined(__EonilGraphics__GL_Buffer__) */











