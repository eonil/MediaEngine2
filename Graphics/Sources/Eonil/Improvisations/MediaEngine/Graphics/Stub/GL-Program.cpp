//
//  GL-Program.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "GL-Program.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Stub
	{
#ifdef 	__cplusplus
		EEGL_INLINE std::vector<GLuint> const		eeglGetAttachedShadersVector(GLuint const program);
#endif
		
		EEGL_INLINE GLboolean const				eeglIsProgram(GLuint const program);
		EEGL_INLINE GLint const					eeglGetProgrami(GLuint const program, GLenum const pname);
		
		static void EEGL_ASSERT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION(GLuint const program)
		{
			EEGL_ASSERT(program != 0);
			EEGL_ASSERT(eeglIsProgram(program));
			EEGL_ASSERT(eeglGetProgrami(program, GL_DELETE_STATUS) == GL_FALSE);
			EEGL_ASSERT(eeglGetProgrami(program, GL_LINK_STATUS) == GL_TRUE);
		}
		static void EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION()
		{
			EEGL_ASSERT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION(eeglGetInteger(GL_CURRENT_PROGRAM));
		}
		
		
		
		
		
		
		
		
		
		
		EEGL_INLINE GLboolean const
		eeglIsProgram(GLuint const program)
		{
			GLboolean const	value	=	glIsProgram(program);
			EEGL_ASSERT_NO_GL_ERROR();
			return	value;
		}
		EEGL_INLINE void
		eeglGetProgramiv(GLuint const program, GLenum const pname, GLint * const params)
		{
			EEGL_ASSERT((pname == GL_DELETE_STATUS) ||
								  (pname == GL_LINK_STATUS) ||
								  (pname == GL_VALIDATE_STATUS) ||
								  (pname == GL_INFO_LOG_LENGTH) ||
								  (pname == GL_ATTACHED_SHADERS) ||
								  (pname == GL_ACTIVE_ATTRIBUTES) ||
								  (pname == GL_ACTIVE_ATTRIBUTE_MAX_LENGTH) ||
								  (pname == GL_ACTIVE_UNIFORMS) ||
								  (pname == GL_ACTIVE_UNIFORM_MAX_LENGTH));
			
			glGetProgramiv(program, pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE GLint const
		eeglGetProgrami(GLuint const program, GLenum const pname)
		{
			GLint	value;
			eeglGetProgramiv(program, pname, &value);
			return	value;
		}
		
		
		
		
		EEGL_INLINE void
		eeglGetActiveUniform(GLuint const program, GLuint const index, GLsizei const bufsize, GLsizei * const length, GLint * const size, GLenum * const type, GLchar * const name)
		{
			EEGL_ASSERT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION(program);
			EEGL_ASSERT(index < eeglGetProgrami(program, GL_ACTIVE_UNIFORMS));
			glGetActiveUniform(program, index, bufsize, length, size, type, name);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglGetActiveAttrib(GLuint const program, GLuint const index, GLsizei const bufsize, GLsizei * const length, GLint * const size, GLenum * const type, GLchar * const name)
		{
			EEGL_ASSERT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION(program);
			EEGL_ASSERT(index < eeglGetProgrami(program, GL_ACTIVE_ATTRIBUTES));
			glGetActiveAttrib(program, index, bufsize, length, size, type, name);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		EEGL_INLINE GLint const
		eeglGetUniformLocation(GLuint const program, GLchar const * const name)
		{
			EEGL_ASSERT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION(program);
			GLint const	loc	=	glGetUniformLocation(program, name);
			EEGL_ASSERT_NO_GL_ERROR();
			return	loc;
		}
		EEGL_INLINE GLint const
		eeglGetAttribLocation(GLuint const program, GLchar const * const name)
		{
			EEGL_ASSERT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION(program);
			GLint const	loc	=	glGetAttribLocation(program, name);
			EEGL_ASSERT_NO_GL_ERROR();
			return	loc;
		}
		
		EEGL_INLINE void
		eeglGetUniformfv(GLuint const program, GLint const location, GLfloat * const params)
		{
			glGetUniformfv(program, location, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglGetUniformiv(GLuint const program, GLint const location, GLint * const params)
		{
			glGetUniformiv(program, location, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglGetProgramInfoLog(GLuint const program, GLsizei const bufsize, GLsizei * const length, GLchar * const infolog)
		{
			EEGL_ASSERT(eeglGetProgrami(program, GL_DELETE_STATUS) == GL_FALSE);
			EEGL_ASSERT(program != 0);
			EEGL_ASSERT(eeglIsProgram(program));
			glGetProgramInfoLog(program, bufsize, length, infolog);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_INLINE void
		eeglGetAttachedShaders(GLuint const program, GLsizei const maxcount, GLsizei * const count, GLuint * const shaders)
		{
			EEGL_ASSERT(eeglGetProgrami(program, GL_DELETE_STATUS) == GL_FALSE);
			EEGL_ASSERT(program != 0);
			EEGL_ASSERT(eeglIsProgram(program));
			
			glGetAttachedShaders(program, maxcount, count, shaders);
			EEGL_ASSERT_NO_GL_ERROR();
			
			EEGL_ASSERT(count == NULL or maxcount >= *count);	//	You are missing some shaders.
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		////
		
		
		
		EEGL_INLINE GLuint
		eeglCreateProgram()
		{
			GLuint const	pn	=	glCreateProgram();
			EEGL_ASSERT_NO_GL_ERROR();
			EEGL_ASSERT(pn != 0);
			EEGL_ASSERT(eeglIsProgram(pn));
			return	pn;
		}
		
		EEGL_INLINE void
		eeglDeleteProgram(GLuint const name)
		{
			EEGL_ASSERT(eeglGetProgrami(name, GL_DELETE_STATUS) == GL_FALSE);
			EEGL_ASSERT(name != 0);
			EEGL_ASSERT(eeglIsProgram(name));
			glDeleteProgram(name);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		////
		
		
		EEGL_INLINE void
		eeglAttachShader(GLuint const program, GLuint const shader)
		{
			EEGL_ASSERT(eeglGetProgrami(program, GL_DELETE_STATUS) == GL_FALSE);
			EEGL_ASSERT(eeglIsProgram(program) == GL_TRUE);
			EEGL_ASSERT(eeglIsShader(shader));
			glAttachShader(program, shader);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglDetachShader(GLuint program, GLuint shader)
		{
			EEGL_ASSERT(eeglGetProgrami(program, GL_DELETE_STATUS) == GL_FALSE);
			EEGL_ASSERT(eeglIsProgram(program) == GL_TRUE);
			EEGL_ASSERT(eeglIsShader(shader));
			glDetachShader(program, shader);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_INLINE void
		eeglLinkProgram(GLuint const program)
		{
			EEGL_ASSERT(eeglIsProgram(program));
			EEGL_ASSERT(eeglGetProgrami(program, GL_DELETE_STATUS) == GL_FALSE);
			glLinkProgram(program);
			EEGL_ASSERT_NO_GL_ERROR();
			
			if (Doctor::useStateValidation())
			{
				if (not (eeglGetProgrami(program, GL_LINK_STATUS) == GL_TRUE))
				{
					Doctor::log(eeglGetProgramInfoLogString(program));
					EEGL_ASSERT(false);
				}
			}
			EEGL_ASSERT(eeglGetProgrami(program, GL_LINK_STATUS) == GL_TRUE);		//	The program must be linked before using.
		}
		
		EEGL_INLINE void
		eeglValidateProgram(GLuint program)
		{
			EEGL_ASSERT(eeglIsProgram(program));
			EEGL_ASSERT(eeglGetProgrami(program, GL_DELETE_STATUS) == GL_FALSE);
			glValidateProgram(program);
			EEGL_ASSERT_NO_GL_ERROR();
			
			EEGL_ASSERT(eeglGetProgrami(program, GL_VALIDATE_STATUS) == GL_TRUE);
		}
		
		////
		
		EEGL_INLINE void
		eeglBindAttribLocation(GLuint const program, GLuint const index, GLchar const * name)
		{
			if (Doctor::useResourceCleansing())
			{
				EEGL_ASSERT(eeglGetInteger(GL_CURRENT_PROGRAM) == 0);
			}
			EEGL_ASSERT(eeglGetProgrami(program, GL_DELETE_STATUS) == GL_FALSE);
			EEGL_ASSERT(index < eeglGetInteger(GL_MAX_VERTEX_ATTRIBS));
			EEGL_ASSERT(name != NULL);
			EEGL_ASSERT(eeglIsProgram(program));
			//	TODO: Check whether the program has the name actually.
			glBindAttribLocation(program, index, name);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_INLINE void
		eeglUseProgram(GLuint const name)
		{
			EEGL_ASSERT(name != 0);
			EEGL_ASSERT(eeglIsProgram(name));
			EEGL_ASSERT(eeglGetProgrami(name, GL_DELETE_STATUS) == GL_FALSE);
			EEGL_ASSERT(eeglGetProgrami(name, GL_LINK_STATUS) == GL_TRUE);		//	The program must be linked before using.
			EEGL_ASSERT(eeglGetProgrami(name, GL_ATTACHED_SHADERS) == 2);			//	The program must have both of vertex/fragment shaders.
			
			glUseProgram(name);
			if (Doctor::useStateValidation())
			{
				std::map<GLenum,std::string>	msgmap;
				msgmap[GL_INVALID_VALUE]		=	"GL_INVALID_VALUE is generated if program is neither 0 nor a value generated by OpenGL.";
				msgmap[GL_INVALID_OPERATION]	=	"GL_INVALID_OPERATION is generated if program is not a program object. GL_INVALID_OPERATION is generated if program could not be made part of current state.";
				Doctor::assertNoGLErrorWithMessageDesignations(msgmap);
			}
		}
		
		EEGL_INLINE void
		eeglUnuseProgram()
		{
			if (Doctor::useResourceCleansing())
			{
				EEGL_ASSERT(eeglGetInteger(GL_CURRENT_PROGRAM) != 0);
				EEGL_ASSERT(eeglIsProgram(eeglGetInteger(GL_CURRENT_PROGRAM)));
				EEGL_ASSERT(eeglGetProgrami(eeglGetInteger(GL_CURRENT_PROGRAM), GL_DELETE_STATUS) == GL_FALSE);
				glUseProgram(0);
				EEGL_ASSERT_NO_GL_ERROR();
			}
		}
		
		
		
		////
		
		EEGL_INLINE void
		eeglUniform1f(GLint const location, GLfloat const v0)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform1f(location, v0);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUniform2f(GLint const location, GLfloat const v0, GLfloat const v1)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform2f(location, v0, v1);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUniform3f(GLint const location, GLfloat const v0, GLfloat const v1, GLfloat const v2)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform3f(location, v0, v1,v2);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUniform4f(GLint const location, GLfloat const v0, GLfloat const v1, GLfloat const v2, GLfloat const v3)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform4f(location, v0, v1, v2, v3);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		EEGL_INLINE void
		eeglUniform1i(GLint const location, GLint const v0)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform1i(location, v0);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUniform2i(GLint const location, GLint const v0, GLint const v1)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform2i(location, v0, v1);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUniform3i(GLint const location, GLint const v0, GLint const v1, GLint const v2)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform3i(location, v0, v1,v2);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUniform4i(GLint const location, GLint const v0, GLint const v1, GLint const v2, GLint const v3)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform4i(location, v0, v1, v2, v3);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		EEGL_INLINE void
		eeglUniform1fv(GLint const location, GLsizei const count, GLfloat const * const value)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform1fv(location, count, value);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUniform2fv(GLint const location, GLsizei const count, GLfloat const * const value)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform1fv(location, count, value);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUniform3fv(GLint const location, GLsizei const count, GLfloat const * const value)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform1fv(location, count, value);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUniform4fv(GLint const location, GLsizei const count, GLfloat const * const value)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform1fv(location, count, value);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		EEGL_INLINE void
		eeglUniform1iv(GLint const location, GLsizei const count, GLint const * const value)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform1iv(location, count, value);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUniform2iv(GLint const location, GLsizei const count, GLint const * const value)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform1iv(location, count, value);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUniform3iv(GLint const location, GLsizei const count, GLint const * const value)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform1iv(location, count, value);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUniform4iv(GLint const location, GLsizei const count, GLint const * const value)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			
			glUniform1iv(location, count, value);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		EEGL_INLINE void
		eeglUniformMatrix2fv(GLint const location, GLsizei const count, GLboolean const transpose, GLfloat const * const value)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			EEGL_ASSERT(transpose == GL_FALSE);
			
			glUniformMatrix2fv(location, count, transpose, value);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUniformMatrix3fv(GLint const location, GLsizei const count, GLboolean const transpose, GLfloat const * const value)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			EEGL_ASSERT(transpose == GL_FALSE);
			
			glUniformMatrix3fv(location, count, transpose, value);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglUniformMatrix4fv(GLint const location, GLsizei const count, GLboolean const transpose, GLfloat const * const value)
		{
			EEGL_ASSERT_CURRENT_PROGRAM_IS_VALID_FOR_SLOT_OPERATION();
			EEGL_ASSERT(transpose == GL_FALSE);
			
			glUniformMatrix4fv(location, count, transpose, value);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		
		
		
		
		
		
		
		
#ifdef __cplusplus
		EEGL_INLINE std::string const
		eeglGetProgramInfoLogString(GLuint program)
		{
			GLint const	len	=	eeglGetProgrami(program, GL_INFO_LOG_LENGTH);
			GLchar		buf[len+1];
			GLint		len2;
			
			eeglGetProgramInfoLog(program, len, &len2, buf);
			buf[len]	=	'\0';	//	For safety.
			EEGL_ASSERT(len >= len2);
			
			return	std::string(buf);
		}
		
		EEGL_INLINE std::vector<GLuint> const
		eeglGetAttachedShadersVector(GLuint const program)
		{
			GLsizei const	maxcount	=	eeglGetProgrami(program, GL_ATTACHED_SHADERS);
			GLsizei			curcount	=	0;
			GLuint			shaders[maxcount];
			eeglGetAttachedShaders(program, maxcount, &curcount, shaders);
			EEGL_ASSERT(maxcount == curcount);
			
			std::vector<GLuint>	svec;
			for (int i=0; i>curcount; i++)
			{
				svec.push_back(shaders[i]);
			}
			return	svec;
		}
#endif
	}
	
}}}}

