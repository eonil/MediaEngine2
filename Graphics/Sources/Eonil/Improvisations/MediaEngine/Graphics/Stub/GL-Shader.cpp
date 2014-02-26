//
//  GL-Shader.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "GL-Shader.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Stub
	{
		/*
		 GL Shader is ref-counted obejct.
		 */

		
		
		

		
		
		
		
		
		
		
		EEGL_STUB_API_DECO GLboolean const
		eeglIsShader(GLuint const shader)
		{
			GLboolean const		value	=	glIsShader(shader);
			EEGL_ASSERT_NO_GL_ERROR();
			return	value;
		}
		
		EEGL_STUB_API_DECO void
		eeglGetShaderiv(GLuint const shader, GLenum const pname, GLint * const params)
		{
			EEGL_ASSERT((pname == GL_SHADER_TYPE) ||
				   (pname == GL_DELETE_STATUS) ||
				   (pname == GL_COMPILE_STATUS) ||
				   (pname == GL_INFO_LOG_LENGTH) ||
				   (pname == GL_SHADER_SOURCE_LENGTH));
			
			glGetShaderiv(shader, pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_STUB_API_DECO GLint const
		eeglGetShaderi(GLuint const shader, GLenum const pname)
		{
			GLint	value;
			eeglGetShaderiv(shader, pname, &value);
			return	value;
		}
		
		EEGL_STUB_API_DECO void
		eeglGetShaderSource(GLuint const shader, GLsizei const bufsize, GLsizei * const length, GLchar * const source)
		{
			EEGL_ASSERT(eeglIsShader(shader));
			EEGL_ASSERT(eeglGetShaderi(shader, GL_DELETE_STATUS) == GL_FALSE);
			EEGL_ASSERT(bufsize > 0);
			glGetShaderSource(shader, bufsize, length, source);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
//			EEGL_STUB_API_DECO void
//			eeglGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint *range, GLint *precision)
//			{
//				glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
//				EEGL_ASSERT_NO_GL_ERROR();
//			}
		
		
		EEGL_STUB_API_DECO void
		eeglGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei *length, GLchar *infolog)
		{
			EEGL_ASSERT(eeglIsShader(shader));
			EEGL_ASSERT(eeglGetShaderi(shader, GL_DELETE_STATUS) == GL_FALSE);
			glGetShaderInfoLog(shader, bufsize, length, infolog);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		////
		
		
		EEGL_STUB_API_DECO GLuint const
		eeglCreateShader(GLenum const type)
		{
			GLuint const	shader	=	glCreateShader(type);
			EEGL_ASSERT_NO_GL_ERROR();
			EEGL_ASSERT(eeglIsShader(shader));
			EEGL_ASSERT(eeglGetShaderi(shader, GL_DELETE_STATUS) == GL_FALSE);
			return	shader;
		}
		
		EEGL_STUB_API_DECO void
		eeglDeleteShader(GLuint const shader)
		{
			EEGL_ASSERT(eeglIsShader(shader));
			EEGL_ASSERT(eeglGetShaderi(shader, GL_DELETE_STATUS) == GL_FALSE);
			glDeleteShader(shader);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		////
		
		EEGL_STUB_API_DECO void
		eeglShaderSource(GLuint const shader, GLsizei const count, GLchar const * * const string, GLint const * const length)
		{
			EEGL_ASSERT(eeglIsShader(shader));
			EEGL_ASSERT(eeglGetShaderi(shader, GL_DELETE_STATUS) == GL_FALSE);
			glShaderSource(shader, count, string, length);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_STUB_API_DECO void
		eeglCompileShader(GLuint const shader)
		{
			EEGL_ASSERT(eeglIsShader(shader));
			EEGL_ASSERT(eeglGetShaderi(shader, GL_DELETE_STATUS) == GL_FALSE);
			glCompileShader(shader);
			EEGL_ASSERT_NO_GL_ERROR();
			
			if (Doctor::useStateValidation())
			{
				if (eeglGetShaderi(shader, GL_COMPILE_STATUS) == GL_FALSE)
				{
					std::string const	str	=	eeglGetShaderInfoLogString(shader);
					Doctor::log("Shader compilation failure:");
					Doctor::log(str);
					Doctor::log("source:");
					Doctor::log(eeglGetShaderSourceString(shader));
					EEGL_ASSERT(false);
				}
			}
		}
		
		EEGL_STUB_API_DECO void
		eeglReleaseShaderCompiler(void)
		{
			#if	EONIL_MEDIA_ENGINE_TARGET_OSX
			//	No-op.
			#endif
			
			#if EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
			EEGL_ASSERT(eeglGetBoolean(GL_SHADER_COMPILER) == GL_TRUE);
			glReleaseShaderCompiler();
			EEGL_ASSERT_NO_GL_ERROR();
			#endif
		}
		
//			EEGL_STUB_API_DECO void
//			eeglShaderBinary(GLsizei n, const GLuint *shaders, GLenum binaryformat, const GLvoid *binary, GLsizei length)
//			{
//				glShaderBinary(n, shaders, binaryformat, binary, length);
//				EEGL_ASSERT_NO_GL_ERROR();
//			}
//			EEGL_STUB_API_DECO void
//			eeglShaderBinary(GLuint const shader, GLenum const binaryFormat, GLvoid const * const binary, GLsizei const length)
//			{
//				eeglShaderBinary(1, &shader, binaryFormat, binary, length);
//			}
		
		

		
		
		
		
		
		
		
		
		////
		
		
#ifdef		__cplusplus
		EEGL_STUB_API_DECO void
		eeglShaderSourceString(GLuint const shader, std::string const string)
		{
			char const * const		cstr		=	string.c_str();
			GLchar const *			glstrs[1]	=	{ (GLchar const *)cstr };
			GLint const 			len			=	(GLint)strlen(cstr);
			GLint const * const		lenptr		=	&len;
			
			eeglShaderSource(shader, 1, glstrs, lenptr);
		}
		EEGL_STUB_API_DECO std::string const
		eeglGetShaderSourceString(GLuint const shader)
		{
			GLint const	len		=	eeglGetShaderi(shader, GL_SHADER_SOURCE_LENGTH);
			if (len == 0)
			{
				return	"";
			}
			else
			{
				GLchar		buf[len];
				GLint		len2;
				
				eeglGetShaderSource(shader, len, &len2, buf);
				EEGL_ASSERT(buf[len2] == '\0');
				buf[len2]	=	'\0';	//	For safety.
				EEGL_ASSERT(len == len2+1);
				return	std::string(buf);
			}
		}
		EEGL_STUB_API_DECO std::string const
		eeglGetShaderInfoLogString(GLuint const shader)
		{
			GLint const	len	=	eeglGetShaderi(shader, GL_INFO_LOG_LENGTH);
			if (len == 0)
			{
				return	"";
			}
			else
			{
				GLchar		buf[len];
				GLint		len2;
				
				eeglGetShaderInfoLog(shader, len, &len2, buf);
				EEGL_ASSERT(buf[len2] == '\0');
				buf[len2]	=	'\0';	//	For safety.
				EEGL_ASSERT(len == len2+1);
				
				return	std::string(buf);
			}
		}
#endif
	}
	
}}}}
