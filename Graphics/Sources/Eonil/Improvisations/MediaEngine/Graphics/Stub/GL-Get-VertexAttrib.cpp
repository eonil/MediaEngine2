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
		
		EEGL_STUB_API_DECO void
		eeglGetVertexAttribfv(GLuint const index, GLenum const pname, GLfloat * const params)
		{
			glGetVertexAttribfv(index, pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_STUB_API_DECO void
		eeglGetVertexAttribiv(GLuint const index, GLenum const pname, GLint * const params)
		{
			glGetVertexAttribiv(index, pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		EEGL_STUB_API_DECO GLfloat const
		eeglGetVertexAttribf(GLuint const index, GLenum const pname)
		{
			GLfloat	params[1];
			eeglGetVertexAttribfv(index, pname, params);
			return	params[0];
		}
		
		EEGL_STUB_API_DECO GLint const
		eeglGetVertexAttribi(GLuint const index, GLenum const pname)
		{
			GLint	params[1];
			eeglGetVertexAttribiv(index, pname, params);
			return	params[0];
		}

		/*!
		 @param	pointer		Out parameter.
		 */
		EEGL_STUB_API_DECO void
		eeglGetVertexAttribPointerv(GLuint const index, GLenum const pname, GLvoid** const pointer)
		{
			EEGL_ASSERT(pname == GL_VERTEX_ATTRIB_ARRAY_POINTER);
//				EEGL_ASSERT(pointer != NULL, "Out parameter point shouldn't be a `NULL`.");
			glGetVertexAttribPointerv(index, pname, pointer);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		EEGL_STUB_API_DECO GLvoid* const
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

