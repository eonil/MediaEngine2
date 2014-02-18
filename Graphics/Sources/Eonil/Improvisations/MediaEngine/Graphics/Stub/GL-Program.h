//
//  GL-Program.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__GL_Program__
#define __EonilGraphics__GL_Program__

#include "GL-Common.h"
#include "GL-Get.h"
#include "GL-Shader.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Stub
	{
#ifdef 	__cplusplus
		EEGL_INLINE std::vector<GLuint> const	eeglGetAttachedShadersVector(GLuint const program);
#endif
		
		EEGL_INLINE GLboolean const				eeglIsProgram(GLuint const program);
		EEGL_INLINE GLint const					eeglGetProgrami(GLuint const program, GLenum const pname);
		

		
		
		
		
		
		
		
		
		
		EEGL_INLINE GLboolean const	eeglIsProgram(GLuint const program);
		EEGL_INLINE void			eeglGetProgramiv(GLuint const program, GLenum const pname, GLint * const params);
		EEGL_INLINE GLint const		eeglGetProgrami(GLuint const program, GLenum const pname);
		
		
		
		EEGL_INLINE void			eeglGetActiveUniform(GLuint const program, GLuint const index, GLsizei const bufsize, GLsizei * const length, GLint * const size, GLenum * const type, GLchar * const name);
		EEGL_INLINE void			eeglGetActiveAttrib(GLuint const program, GLuint const index, GLsizei const bufsize, GLsizei * const length, GLint * const size, GLenum * const type, GLchar * const name);
		
		EEGL_INLINE GLint const		eeglGetUniformLocation(GLuint const program, GLchar const * const name);
		EEGL_INLINE GLint const		eeglGetAttribLocation(GLuint const program, GLchar const * const name);
		
		EEGL_INLINE void			eeglGetUniformfv(GLuint const program, GLint const location, GLfloat * const params);
		EEGL_INLINE void			eeglGetUniformiv(GLuint const program, GLint const location, GLint * const params);
		EEGL_INLINE void			eeglGetProgramInfoLog(GLuint const program, GLsizei const bufsize, GLsizei * const length, GLchar * const infolog);
		EEGL_INLINE void			eeglGetAttachedShaders(GLuint const program, GLsizei const maxcount, GLsizei * const count, GLuint * const shaders);
		
		
		
		
		////

		EEGL_INLINE GLuint			eeglCreateProgram();
		
		EEGL_INLINE void			eeglDeleteProgram(GLuint const name);
		
		////
		
		EEGL_INLINE void			eeglAttachShader(GLuint const program, GLuint const shader);
		EEGL_INLINE void			eeglDetachShader(GLuint program, GLuint shader);
		EEGL_INLINE void			eeglLinkProgram(GLuint const program);
		EEGL_INLINE void			eeglValidateProgram(GLuint program);
		
		////
		
		EEGL_INLINE void			eeglBindAttribLocation(GLuint const program, GLuint const index, GLchar const * name);
		EEGL_INLINE void			eeglUseProgram(GLuint const name);
		EEGL_INLINE void			eeglUnuseProgram();
		
		////
		
		EEGL_INLINE void			eeglUniform1f(GLint const location, GLfloat const v0);
		EEGL_INLINE void			eeglUniform2f(GLint const location, GLfloat const v0, GLfloat const v1);
		EEGL_INLINE void			eeglUniform3f(GLint const location, GLfloat const v0, GLfloat const v1, GLfloat const v2);
		EEGL_INLINE void			eeglUniform4f(GLint const location, GLfloat const v0, GLfloat const v1, GLfloat const v2, GLfloat const v3);
		
		EEGL_INLINE void			eeglUniform1i(GLint const location, GLint const v0);
		EEGL_INLINE void			eeglUniform2i(GLint const location, GLint const v0, GLint const v1);
		EEGL_INLINE void			eeglUniform3i(GLint const location, GLint const v0, GLint const v1, GLint const v2);
		EEGL_INLINE void			eeglUniform4i(GLint const location, GLint const v0, GLint const v1, GLint const v2, GLint const v3);
		
		EEGL_INLINE void			eeglUniform1fv(GLint const location, GLsizei const count, GLfloat const * const value);
		EEGL_INLINE void			eeglUniform2fv(GLint const location, GLsizei const count, GLfloat const * const value);
		EEGL_INLINE void			eeglUniform3fv(GLint const location, GLsizei const count, GLfloat const * const value);
		EEGL_INLINE void			eeglUniform4fv(GLint const location, GLsizei const count, GLfloat const * const value);
		
		EEGL_INLINE void			eeglUniform1iv(GLint const location, GLsizei const count, GLint const * const value);
		EEGL_INLINE void			eeglUniform2iv(GLint const location, GLsizei const count, GLint const * const value);
		EEGL_INLINE void			eeglUniform3iv(GLint const location, GLsizei const count, GLint const * const value);
		EEGL_INLINE void			eeglUniform4iv(GLint const location, GLsizei const count, GLint const * const value);
		
		EEGL_INLINE void			eeglUniformMatrix2fv(GLint const location, GLsizei const count, GLboolean const transpose, GLfloat const * const value);
		EEGL_INLINE void			eeglUniformMatrix3fv(GLint const location, GLsizei const count, GLboolean const transpose, GLfloat const * const value);
		EEGL_INLINE void			eeglUniformMatrix4fv(GLint const location, GLsizei const count, GLboolean const transpose, GLfloat const * const value);
		
		
		
		
		
		
		
		
		
		
#ifdef __cplusplus
		EEGL_INLINE std::string const			eeglGetProgramInfoLogString(GLuint program);
		EEGL_INLINE std::vector<GLuint> const	eeglGetAttachedShadersVector(GLuint const program);
#endif
	}
	
}}}}















#endif /* defined(__EonilGraphics__GL_Program__) */







