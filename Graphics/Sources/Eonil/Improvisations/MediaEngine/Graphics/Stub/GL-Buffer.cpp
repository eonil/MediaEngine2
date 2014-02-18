//
//  GL-Buffer.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "GL-Buffer.h"



namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Stub
	{
		EEGL_INLINE void
		eeglGetBufferParameteriv(GLenum const target, GLenum const pname, GLint* const params)
		{
			EEGL_ASSERT(target == GL_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER);
			EEGL_ASSERT(pname == GL_BUFFER_SIZE || pname == GL_BUFFER_USAGE);
			
			glGetBufferParameteriv(target, pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_INLINE GLint const
		eeglGetBufferParameteri(GLenum const target, GLenum const pname)
		{
			GLint	param;
			eeglGetBufferParameteriv(target, pname, &param);
			return	param;
		}
		
		
		
		
		
		
		
		
		
		////
		
		
		
		
		EEGL_INLINE void
		eeglGenBuffers(GLsizei const n, GLuint* const buffers)
		{
			glGenBuffers(n, buffers);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE GLuint const
		eeglGenBuffer()
		{
			GLuint	name	=	0;
			eeglGenBuffers(1, &name);
			
			EEGL_ASSERT(name != 0);
			return	name;
		}
		EEGL_INLINE void
		eeglDeleteBuffers(GLsizei const n, GLuint const* const buffers)
		{
			if (Doctor::useStateValidation())
			{
				for (GLsizei i=0; i<n; i++)
				{
					EEGL_ASSERT(buffers[i] != 0);
				}
			}
			glDeleteBuffers(n, buffers);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglDeleteBuffer(GLuint const name)
		{
			eeglDeleteBuffers(1, &name);
		}
		
		
		
		
		
		EEGL_INLINE void
		eeglBindBuffer(GLenum const target, GLuint const buffer)
		{
			if (Doctor::useStateValidation())
			{
				EEGL_ASSERT(target == GL_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER);
				EEGL_ASSERT(buffer != 0);
			}
			glBindBuffer(target, buffer);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUnbindBufer(GLenum const target)
		{
			if (Doctor::useStateValidation())
			{
				EEGL_ASSERT(target == GL_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER);
			}
//				if (Doctor::useResourceCleansing())
			{
				glBindBuffer(target, 0);
				EEGL_ASSERT_NO_GL_ERROR();
			}
		}
		
		
		
		
		
		
		
		
		EEGL_INLINE void
		eeglBufferData(GLenum const target, GLsizeiptr const size, GLvoid const * const data, GLenum const usage)
		{
			EEGL_ASSERT(target == GL_ARRAY_BUFFER || target == GL_ELEMENT_ARRAY_BUFFER);
			EEGL_ASSERT(eeglGetInteger(GL_ARRAY_BUFFER_BINDING) != 0 || eeglGetInteger(GL_ELEMENT_ARRAY_BUFFER_BINDING) != 0);		//	Target buffer must be bound currently.
			EEGL_ASSERT(data == nullptr || (data != nullptr && size > 0));
			EEGL_ASSERT(usage == GL_STREAM_DRAW || usage == GL_STATIC_DRAW || usage == GL_DYNAMIC_DRAW);
			glBufferData(target, size, data, usage);
			EEGL_ASSERT_NO_GL_ERROR();
			EEGL_ASSERT(eeglGetBufferParameteri(GL_ARRAY_BUFFER, GL_BUFFER_SIZE) == size);
		}
		
		EEGL_INLINE void
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

}}}}