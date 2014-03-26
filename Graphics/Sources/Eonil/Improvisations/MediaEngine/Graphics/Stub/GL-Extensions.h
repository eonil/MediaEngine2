//
//  GL-Extensions.h
//  Graphics
//
//  Created by Hoon H. on 3/26/14.
//
//

#ifndef __Graphics__GL_Extensions__
#define __Graphics__GL_Extensions__

#include "GL-Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Stub
	{
		
		/*
		 This file contains stub functions for all extensions including ARB.
		 ARB is treated as just another vendor.
		 
		 Take care that this is designed for OpenGL ES 2.0 level API.
		 */
		
		
		
		
#pragma mark	-	ARB
		
		
		
		
		
		
		
#pragma mark	-	OES
		
		
		
		
		
#pragma mark	-
		
#pragma mark	EXT_draw_instanced
		/*
		 @ref
		 http://www.khronos.org/registry/gles/extensions/EXT/draw_instanced.txt
		 */

		EEGL_STUB_API_DECO void		eeglDrawArraysInstancedEXT(GLenum const mode, GLint const first, GLsizei const count, GLsizei const instanceCount);
		EEGL_STUB_API_DECO void		eeglDrawElementsInstancedEXT(GLenum const mode, GLsizei const count, GLenum const type, const GLvoid * const indices, GLsizei const instanceCount);
		
		
#pragma mark	EXT_instanced_arrays
		/*
		 @ref
		 http://www.khronos.org/registry/gles/extensions/EXT/EXT_instanced_arrays.txt
		 */
		EEGL_STUB_API_DECO void		eeglVertexAttribDivisorEXT(GLuint const index, GLuint const divisor);
		EEGL_STUB_API_DECO void		eeglDrawArraysInstancedEXT(GLenum const mode, GLint const first, GLsizei const count, GLsizei const instanceCount);
		EEGL_STUB_API_DECO void		eeglDrawElementsInstancedEXT(GLenum const mode, GLsizei const count, GLenum const type, GLvoid const* const indices, GLsizei const instanceCount);

		
		
		
		
		
		
		
		
#pragma mark	-	Apple
		
		
		
		
		
#pragma mark	-	Nvidia
		
		
		
		
		
#pragma mark	-	ATI
		
		
		
		
		
				
		
	}
	
}}}}

#endif /* defined(__Graphics__GL_Extensions__) */
