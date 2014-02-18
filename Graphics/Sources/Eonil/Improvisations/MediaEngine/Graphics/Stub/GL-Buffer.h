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
		EEGL_INLINE void			eeglGetBufferParameteriv(GLenum const target, GLenum const pname, GLint* const params);
		EEGL_INLINE GLint const		eeglGetBufferParameteri(GLenum const target, GLenum const pname);
		
		
		
		
		////
		
		EEGL_INLINE void			eeglGenBuffers(GLsizei const n, GLuint* const buffers);
		EEGL_INLINE GLuint const	eeglGenBuffer();
		EEGL_INLINE void			eeglDeleteBuffers(GLsizei const n, GLuint const* const buffers);
		EEGL_INLINE void			eeglDeleteBuffer(GLuint const name);
		
		EEGL_INLINE void			eeglBindBuffer(GLenum const target, GLuint const buffer);
		EEGL_INLINE void			eeglUnbindBufer(GLenum const target);
		
		EEGL_INLINE void			eeglBufferData(GLenum const target, GLsizeiptr const size, GLvoid const * const data, GLenum const usage);
		EEGL_INLINE void			eeglBufferSubData(GLenum const target, GLintptr const offset, GLsizeiptr const size, GLvoid const * const data);
		

		
		
		
		
		
		
	}
	
	
}}}}

#endif /* defined(__EonilGraphics__GL_Buffer__) */











