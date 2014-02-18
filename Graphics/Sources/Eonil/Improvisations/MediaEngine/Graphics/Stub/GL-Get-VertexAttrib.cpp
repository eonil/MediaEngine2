//
//  GL-Get-VertexAttrib.cpp
//  EonilGraphics
//
//  Created by Eonil on 5/2/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "GL-Get-VertexAttrib.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Stub
	{
		using namespace Debugging;
		
		EEGL_INLINE void
		eeglGetVertexAttribfv(GLuint const index, GLenum const pname, GLfloat * const params)
		{
			glGetVertexAttribfv(index, pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_INLINE void
		eeglGetVertexAttribiv(GLuint const index, GLenum const pname, GLint * const params)
		{
			glGetVertexAttribiv(index, pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		EEGL_INLINE GLfloat const
		eeglGetVertexAttribf(GLuint const index, GLenum const pname)
		{
			GLfloat	params[1];
			eeglGetVertexAttribfv(index, pname, params);
			return	params[0];
		}
		
		EEGL_INLINE GLint const
		eeglGetVertexAttribi(GLuint const index, GLenum const pname)
		{
			GLint	params[1];
			eeglGetVertexAttribiv(index, pname, params);
			return	params[0];
		}

		/*!
		 @param	pointer		Out parameter.
		 */
		EEGL_INLINE void
		eeglGetVertexAttribPointerv(GLuint const index, GLenum const pname, GLvoid** const pointer)
		{
			EEGL_ASSERT(pname == GL_VERTEX_ATTRIB_ARRAY_POINTER);
//				EEGL_ASSERT(pointer != NULL, "Out parameter point shouldn't be a `NULL`.");
			glGetVertexAttribPointerv(index, pname, pointer);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		EEGL_INLINE GLvoid* const
		eeglGetVertexAttribPointerv(GLuint const index, GLenum const pname)
		{
			GLvoid*	ptraddr	=	NULL;
			eeglGetVertexAttribPointerv(index, pname, &ptraddr);
			return	ptraddr;
		}
		
		
		
#ifdef	__cplusplus
#endif
	}
	
}}}}

