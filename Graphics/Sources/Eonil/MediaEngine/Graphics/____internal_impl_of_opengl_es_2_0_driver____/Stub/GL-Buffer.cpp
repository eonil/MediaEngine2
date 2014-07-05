//
//  GL-Buffer.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "GL-Buffer.h"
#include "GL-Context.h"
#include "____dbg____.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Stub
{
	
	
	
	
	
	
	
	
	
	
	EEGL_STUB_API_DECO GLboolean 
	eeglIsBuffer(GLuint const buffer)
	{
		GLboolean const	r	=	glIsBuffer(buffer);
		EEGL_ASSERT_NO_GL_ERROR();
		return	r;
	}
	
	
	
	
	
	
	
	EEGL_STUB_API_DECO void
	eeglGetBufferParameteriv(GLenum const target, GLenum const pname, GLint* const params)
	{
		EEGL_ASSERT(target == GL_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER);
		EEGL_ASSERT(pname == GL_BUFFER_SIZE || pname == GL_BUFFER_USAGE);
		
		if (USE_DEBUGGING_ASSERTIONS)
		{
			if (target == GL_ARRAY_BUFFER)
			{
				EEGL_ASSERT(eeglGetBoolean(GL_ARRAY_BUFFER_BINDING) != 0);
			}
			if (target == GL_ELEMENT_ARRAY_BUFFER)
			{
				EEGL_ASSERT(eeglGetBoolean(GL_ELEMENT_ARRAY_BUFFER_BINDING) != 0);
			}
		}
		
		glGetBufferParameteriv(target, pname, params);
		EEGL_ASSERT_NO_GL_ERROR();
	}
	
	EEGL_STUB_API_DECO GLint
	eeglGetBufferParameteri(GLenum const target, GLenum const pname)
	{
		GLint	param;
		eeglGetBufferParameteriv(target, pname, &param);
		return	param;
	}
	
	
	
	
	
	
	
	
	
	////
	
	
	
	
	EEGL_STUB_API_DECO void
	eeglGenBuffers(GLsizei const n, GLuint* const buffers)
	{
		glGenBuffers(n, buffers);
		EEGL_ASSERT_NO_GL_ERROR();
	}
	EEGL_STUB_API_DECO GLuint 
	eeglGenBuffer()
	{
		GLuint	name	=	0;
		eeglGenBuffers(1, &name);
		
		EEGL_ASSERT(name != 0);
		return	name;
	}
	EEGL_STUB_API_DECO void
	eeglDeleteBuffers(GLsizei const n, GLuint const* const buffers)
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			for (GLsizei i=0; i<n; i++)
			{
				EEGL_ASSERT(buffers[i] != 0);
			}
		}
		glDeleteBuffers(n, buffers);
		EEGL_ASSERT_NO_GL_ERROR();
	}
	EEGL_STUB_API_DECO void
	eeglDeleteBuffer(GLuint const name)
	{
		eeglDeleteBuffers(1, &name);
	}
	
	
	
	
	
	EEGL_STUB_API_DECO void
	eeglBindBuffer(GLenum const target, GLuint const buffer)
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			EEGL_ASSERT(target == GL_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER);
			EEGL_ASSERT(buffer != 0);
		}
		glBindBuffer(target, buffer);
		EEGL_ASSERT_NO_GL_ERROR();
	}
	EEGL_STUB_API_DECO void
	eeglUnbindBufer(GLenum const target)
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			EEGL_ASSERT(target == GL_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER);
		}
//				if (Doctor::useResourceCleansing())
		{
			glBindBuffer(target, 0);
			EEGL_ASSERT_NO_GL_ERROR();
		}
	}
	
	
	
	
	
	
	
	
	EEGL_STUB_API_DECO void
	eeglBufferData(GLenum const target, GLsizeiptr const size, GLvoid const * const data, GLenum const usage)
	{
		EEGL_ASSERT(target == GL_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER);
		EEGL_ASSERT(eeglGetInteger(GL_ARRAY_BUFFER_BINDING) != 0 || eeglGetInteger(GL_ELEMENT_ARRAY_BUFFER_BINDING) != 0);		//	Target buffer must be bound currently.
		EEGL_ASSERT(data == nullptr || (data != nullptr && size > 0));
		EEGL_ASSERT(usage == GL_STREAM_DRAW || usage == GL_STATIC_DRAW || usage == GL_DYNAMIC_DRAW);
		glBufferData(target, size, data, usage);
		EEGL_ASSERT_NO_GL_ERROR();
		
		/*!
		 @todo
		 Created buffer allocates a lot more memory then required. (128 for 32) 
		 I think this is desinged behavior. So we need to full every buffer as much as possible.
		 Anyway, treat OK if allocated buffer is equal or larger than requested.
		 */
//			auto	a1	=	eeglGetBufferParameteri(target, GL_BUFFER_SIZE);
		EEGL_ASSERT(eeglGetBufferParameteri(target, GL_BUFFER_SIZE) >= size);
	}
	
	EEGL_STUB_API_DECO void
	eeglBufferSubData(GLenum const target, GLintptr const offset, GLsizeiptr const size, GLvoid const * const data)
	{
		EEGL_ASSERT(target == GL_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER);
		EEGL_ASSERT(eeglGetInteger(GL_ARRAY_BUFFER_BINDING) != 0 || eeglGetInteger(GL_ELEMENT_ARRAY_BUFFER_BINDING) != 0);
		EEGL_ASSERT(data == nullptr || (data != nullptr && size > 0));
		EEGL_ASSERT(eeglGetBufferParameteri(target, GL_BUFFER_SIZE) >= offset + size);
		glBufferSubData(target, offset, size, data);
		EEGL_ASSERT_NO_GL_ERROR();
	}

	

	
			
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END

