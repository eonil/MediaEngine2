//
//  GL-Get-VertexAttrib.h
//  EonilGraphics
//
//  Created by Eonil on 5/2/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__GL_Get_VertexAttrib__
#define __EonilGraphics__GL_Get_VertexAttrib__

#include "../Debugging/Doctor.h"
#include "GL-Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Stub
	{
		using namespace Debugging;
		
		EEGL_STUB_API_DECO void				eeglGetVertexAttribfv(GLuint const index, GLenum const pname, GLfloat * const params);
		EEGL_STUB_API_DECO void				eeglGetVertexAttribiv(GLuint const index, GLenum const pname, GLint * const params);
		EEGL_STUB_API_DECO GLfloat const		eeglGetVertexAttribf(GLuint const index, GLenum const pname);
		EEGL_STUB_API_DECO GLint const			eeglGetVertexAttribi(GLuint const index, GLenum const pname);
		
		EEGL_STUB_API_DECO void				eeglGetVertexAttribPointerv(GLuint const index, GLenum const pname, GLvoid** const pointer);
		EEGL_STUB_API_DECO GLvoid* const		eeglGetVertexAttribPointerv(GLuint const index, GLenum const pname);
		
#ifdef	__cplusplus
#endif
	}
	
}}}}

#endif /* defined(__EonilGraphics__GL_Get_VertexAttrib__) */
