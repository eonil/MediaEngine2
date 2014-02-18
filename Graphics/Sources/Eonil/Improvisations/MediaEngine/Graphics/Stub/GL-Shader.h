//
//  GL-Shader.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__GL_Shader__
#define __EonilGraphics__GL_Shader__

#include "GL-Get.h"
#include "GL-Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Stub
	{
		/*
		 GL Shader is ref-counted obejct.
		 */

		EEGL_INLINE GLboolean const	eeglIsShader(GLuint const shader);
		
		EEGL_INLINE void			eeglGetShaderiv(GLuint const shader, GLenum const pname, GLint * const params);
		EEGL_INLINE GLint const	eeglGetShaderi(GLuint const shader, GLenum const pname);
		
		EEGL_INLINE void			eeglGetShaderSource(GLuint const shader, GLsizei const bufsize, GLsizei * const length, GLchar * const source);
		
//			EEGL_INLINE void
//			eeglGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision)
//			{
//				glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
//				EEGL_ASSERT_NO_GL_ERROR();
//			}
		
		
		EEGL_INLINE void			eeglGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei *length, GLchar *infolog);
		
		////
		
		EEGL_INLINE GLuint const		eeglCreateShader(GLenum const type);
		EEGL_INLINE void				eeglDeleteShader(GLuint const shader);
		
		////
		
		EEGL_INLINE void			eeglShaderSource(GLuint const shader, GLsizei const count, GLchar const * * const string, GLint const * const length);
		EEGL_INLINE void			eeglCompileShader(GLuint const shader);
		EEGL_INLINE void			eeglReleaseShaderCompiler(void);
		
//			EEGL_INLINE void
//			eeglShaderBinary(GLsizei n, const GLuint *shaders, GLenum binaryformat, const GLvoid *binary, GLsizei length)
//			{
//				glShaderBinary(n, shaders, binaryformat, binary, length);
//				EEGL_ASSERT_NO_GL_ERROR();
//			}
//			EEGL_INLINE void
//			eeglShaderBinary(GLuint const shader, GLenum const binaryFormat, GLvoid const * const binary, GLsizei const length)
//			{
//				eeglShaderBinary(1, &shader, binaryFormat, binary, length);
//			}
		
		

		
		
		
		
		
		
		
		
		////
		
		
#ifdef		__cplusplus
		EEGL_INLINE void							eeglShaderSourceString(GLuint const shader, std::string const string);
		EEGL_INLINE std::string const			eeglGetShaderSourceString(GLuint const shader);
		EEGL_INLINE std::string const			eeglGetShaderInfoLogString(GLuint const shader);
#endif
	}
	
}}}}

#endif /* defined(__EonilGraphics__GL_Shader__) */















