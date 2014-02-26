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
		EEGL_STUB_API_DECO std::vector<GLuint> const	eeglGetAttachedShadersVector(GLuint const program);
#endif
		
		EEGL_STUB_API_DECO GLboolean const				eeglIsProgram(GLuint const program);
		EEGL_STUB_API_DECO GLint const					eeglGetProgrami(GLuint const program, GLenum const pname);
		

		
		
		
		
		
		
		
		
		
		EEGL_STUB_API_DECO GLboolean const	eeglIsProgram(GLuint const program);
		EEGL_STUB_API_DECO void			eeglGetProgramiv(GLuint const program, GLenum const pname, GLint * const params);
		EEGL_STUB_API_DECO GLint const		eeglGetProgrami(GLuint const program, GLenum const pname);
		
		
		
		EEGL_STUB_API_DECO void			eeglGetActiveUniform(GLuint const program, GLuint const index, GLsizei const bufsize, GLsizei * const length, GLint * const size, GLenum * const type, GLchar * const name);
		EEGL_STUB_API_DECO void			eeglGetActiveAttrib(GLuint const program, GLuint const index, GLsizei const bufsize, GLsizei * const length, GLint * const size, GLenum * const type, GLchar * const name);
		
		EEGL_STUB_API_DECO GLint const		eeglGetUniformLocation(GLuint const program, GLchar const * const name);
		EEGL_STUB_API_DECO GLint const		eeglGetAttribLocation(GLuint const program, GLchar const * const name);
		
		EEGL_STUB_API_DECO void			eeglGetUniformfv(GLuint const program, GLint const location, GLfloat * const params);
		EEGL_STUB_API_DECO void			eeglGetUniformiv(GLuint const program, GLint const location, GLint * const params);
		EEGL_STUB_API_DECO void			eeglGetProgramInfoLog(GLuint const program, GLsizei const bufsize, GLsizei * const length, GLchar * const infolog);
		EEGL_STUB_API_DECO void			eeglGetAttachedShaders(GLuint const program, GLsizei const maxcount, GLsizei * const count, GLuint * const shaders);
		
		
		
		
		////

		EEGL_STUB_API_DECO GLuint			eeglCreateProgram();
		
		EEGL_STUB_API_DECO void			eeglDeleteProgram(GLuint const name);
		
		////
		
		EEGL_STUB_API_DECO void			eeglAttachShader(GLuint const program, GLuint const shader);
		EEGL_STUB_API_DECO void			eeglDetachShader(GLuint program, GLuint shader);
		EEGL_STUB_API_DECO void			eeglLinkProgram(GLuint const program);
		EEGL_STUB_API_DECO void			eeglValidateProgram(GLuint program);
		
		////
		
		EEGL_STUB_API_DECO void			eeglBindAttribLocation(GLuint const program, GLuint const index, GLchar const * name);
		EEGL_STUB_API_DECO void			eeglUseProgram(GLuint const name);
		EEGL_STUB_API_DECO void			eeglUnuseProgram();
		
		////
		
		EEGL_STUB_API_DECO void			eeglUniform1f(GLint const location, GLfloat const v0);
		EEGL_STUB_API_DECO void			eeglUniform2f(GLint const location, GLfloat const v0, GLfloat const v1);
		EEGL_STUB_API_DECO void			eeglUniform3f(GLint const location, GLfloat const v0, GLfloat const v1, GLfloat const v2);
		EEGL_STUB_API_DECO void			eeglUniform4f(GLint const location, GLfloat const v0, GLfloat const v1, GLfloat const v2, GLfloat const v3);
		
		EEGL_STUB_API_DECO void			eeglUniform1i(GLint const location, GLint const v0);
		EEGL_STUB_API_DECO void			eeglUniform2i(GLint const location, GLint const v0, GLint const v1);
		EEGL_STUB_API_DECO void			eeglUniform3i(GLint const location, GLint const v0, GLint const v1, GLint const v2);
		EEGL_STUB_API_DECO void			eeglUniform4i(GLint const location, GLint const v0, GLint const v1, GLint const v2, GLint const v3);
		
		EEGL_STUB_API_DECO void			eeglUniform1fv(GLint const location, GLsizei const count, GLfloat const * const value);
		EEGL_STUB_API_DECO void			eeglUniform2fv(GLint const location, GLsizei const count, GLfloat const * const value);
		EEGL_STUB_API_DECO void			eeglUniform3fv(GLint const location, GLsizei const count, GLfloat const * const value);
		EEGL_STUB_API_DECO void			eeglUniform4fv(GLint const location, GLsizei const count, GLfloat const * const value);
		
		EEGL_STUB_API_DECO void			eeglUniform1iv(GLint const location, GLsizei const count, GLint const * const value);
		EEGL_STUB_API_DECO void			eeglUniform2iv(GLint const location, GLsizei const count, GLint const * const value);
		EEGL_STUB_API_DECO void			eeglUniform3iv(GLint const location, GLsizei const count, GLint const * const value);
		EEGL_STUB_API_DECO void			eeglUniform4iv(GLint const location, GLsizei const count, GLint const * const value);
		
		EEGL_STUB_API_DECO void			eeglUniformMatrix2fv(GLint const location, GLsizei const count, GLboolean const transpose, GLfloat const * const value);
		EEGL_STUB_API_DECO void			eeglUniformMatrix3fv(GLint const location, GLsizei const count, GLboolean const transpose, GLfloat const * const value);
		EEGL_STUB_API_DECO void			eeglUniformMatrix4fv(GLint const location, GLsizei const count, GLboolean const transpose, GLfloat const * const value);
		
		
		
		
		
		
		
		
		
		
#ifdef __cplusplus
		EEGL_STUB_API_DECO std::string const			eeglGetProgramInfoLogString(GLuint program);
		EEGL_STUB_API_DECO std::vector<GLuint> const	eeglGetAttachedShadersVector(GLuint const program);
#endif
	}
	
}}}}















#endif /* defined(__EonilGraphics__GL_Program__) */







