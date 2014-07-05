//
//  GL-Texture.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "GL-Texture.h"
#include "GL-Context.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Stub
{
	namespace
	ASSERTION
	{
		EEGL_STUB_API_DECO void
		EEGL_ASSERT_TEX_IMAGE_2D_INTERNAL_FORMAT_ENUM_CHECK(GLint const internalformat)
		{
			#if	EONIL_MEDIA_ENGINE_TARGET_MINIMUM
			EEGL_ASSERT(internalformat == GL_ALPHA || internalformat == GL_RGB || internalformat == GL_RGBA);
			#else
			#if	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
			EEGL_ASSERT(internalformat == GL_ALPHA || internalformat == GL_LUMINANCE || internalformat == GL_LUMINANCE_ALPHA || internalformat == GL_RGB || internalformat == GL_RGBA);
			#endif
			#endif
		}
	}
	
	EEGL_STUB_API_DECO GLboolean const
	eeglIsTexture(GLuint const texture)
	{
		GLboolean const	value	=	glIsTexture(texture);
		EEGL_ASSERT_NO_GL_ERROR();
		return	value;
	}
	
	EEGL_STUB_API_DECO void
	eeglGetTexParameterfv(GLenum const target, GLenum const pname, GLfloat* const params)
	{
		EEGL_ASSERT((target == GL_TEXTURE_2D && eeglGetInteger(GL_TEXTURE_BINDING_2D) != 0) || (target == GL_TEXTURE_CUBE_MAP && eeglGetInteger(GL_TEXTURE_BINDING_CUBE_MAP) != 0));

		EEGL_ASSERT(target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP);
		EEGL_ASSERT(pname == GL_TEXTURE_MIN_FILTER || pname == GL_TEXTURE_MAG_FILTER || pname == GL_TEXTURE_WRAP_S || pname == GL_TEXTURE_WRAP_T);

		glGetTexParameterfv(target, pname, params);
		EEGL_ASSERT_NO_GL_ERROR();
	}
	EEGL_STUB_API_DECO void
	eeglGetTexParameteriv(GLenum const target, GLenum const pname, GLint* const params)
	{
		EEGL_ASSERT((target == GL_TEXTURE_2D && eeglGetInteger(GL_TEXTURE_BINDING_2D) != 0) || (target == GL_TEXTURE_CUBE_MAP && eeglGetInteger(GL_TEXTURE_BINDING_CUBE_MAP) != 0));

		EEGL_ASSERT(target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP);
		EEGL_ASSERT(pname == GL_TEXTURE_MIN_FILTER || pname == GL_TEXTURE_MAG_FILTER || pname == GL_TEXTURE_WRAP_S || pname == GL_TEXTURE_WRAP_T);
		glGetTexParameteriv(target, pname, params);
		EEGL_ASSERT_NO_GL_ERROR();
	}
	EEGL_STUB_API_DECO GLfloat const
	eeglGetTexParameterf(GLenum const target, GLenum const pname)
	{
		GLfloat	value;
		eeglGetTexParameterfv(target, pname, &value);
		return	value;
	}
	EEGL_STUB_API_DECO GLint const
	eeglGetTexParameteri(GLenum const target, GLenum const pname)
	{
		GLint	value;
		eeglGetTexParameteriv(target, pname, &value);
		return	value;
	}
	
	
	////
	
	
	
	EEGL_STUB_API_DECO void
	eeglGenTextures(GLsizei const n, GLuint* const textures)
	{
		glGenTextures(n, textures);
		EEGL_ASSERT_NO_GL_ERROR();
		
		if (USE_DEBUGGING_ASSERTIONS)
		{
			EEGL_ASSERT(n != 0);
		}
	}
	
	EEGL_STUB_API_DECO GLuint const
	eeglGenTexture()
	{
		GLuint	name;
		eeglGenTextures(1, &name);
		return	name;
	}

	EEGL_STUB_API_DECO void
	eeglDeleteTextures(GLsizei const n, GLuint const * const textures)
	{
		glDeleteTextures(n, textures);
		EEGL_ASSERT_NO_GL_ERROR();
	}
	
	EEGL_STUB_API_DECO void
	eeglDeleteTexture(GLuint const name)
	{
		EEGL_ASSERT(name != 0);
		eeglDeleteTextures(1, &name);
	}
	
	
	
	
	
	EEGL_STUB_API_DECO void
	eeglBindTexture(GLenum const target, GLuint const texture)
	{
		EEGL_ASSERT_NO_GL_ERROR();
		
//				EEGL_ASSERT(eeglIsTexture(texture));
		EEGL_ASSERT(target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP);
		
		glBindTexture(target, texture);
		EEGL_ASSERT_NO_GL_ERROR();
	}
	EEGL_STUB_API_DECO void
	eeglUnbindTexture(GLenum const target)
	{
		EEGL_ASSERT_NO_GL_ERROR();
		
		EEGL_ASSERT((target == GL_TEXTURE_2D && eeglGetInteger(GL_TEXTURE_BINDING_2D) != 0) || (target == GL_TEXTURE_CUBE_MAP && eeglGetInteger(GL_TEXTURE_BINDING_CUBE_MAP) != 0));
		EEGL_ASSERT(target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP);
		
		glBindTexture(target, 0);
		EEGL_ASSERT_NO_GL_ERROR();
	}
	
	
	
	
	
	////
	
	
	
	EEGL_STUB_API_DECO void
	eeglTexParameterf(GLenum const target, GLenum const pname, GLfloat const param)
	{
		EEGL_ASSERT(target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP);
		EEGL_ASSERT(pname == GL_TEXTURE_MIN_FILTER || pname == GL_TEXTURE_MAG_FILTER || pname == GL_TEXTURE_WRAP_S || pname == GL_TEXTURE_WRAP_T);
		if (USE_DEBUGGING_ASSERTIONS)
		{
			if (pname == GL_TEXTURE_MIN_FILTER)
			{
				EEGL_ASSERT(param == GL_NEAREST || param == GL_LINEAR || param == GL_NEAREST_MIPMAP_NEAREST || param == GL_LINEAR_MIPMAP_NEAREST || param == GL_NEAREST_MIPMAP_LINEAR || param == GL_LINEAR_MIPMAP_LINEAR);
			}
			if (pname == GL_TEXTURE_MAG_FILTER)
			{
				EEGL_ASSERT(param == GL_NEAREST || param == GL_LINEAR);
			}
			if (pname == GL_TEXTURE_WRAP_S || pname == GL_TEXTURE_WRAP_T)
			{
				EEGL_ASSERT(param == GL_CLAMP_TO_EDGE || param == GL_MIRRORED_REPEAT || param == GL_REPEAT);
			}
		}
		glTexParameterf(target, pname, param);
		EEGL_ASSERT_NO_GL_ERROR();
	}
	
	EEGL_STUB_API_DECO void
	eeglTexParameteri(GLenum const target, GLenum const pname, GLint const param)
	{
		EEGL_ASSERT(target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP);
		EEGL_ASSERT(pname == GL_TEXTURE_MIN_FILTER || pname == GL_TEXTURE_MAG_FILTER || pname == GL_TEXTURE_WRAP_S || pname == GL_TEXTURE_WRAP_T);
		if (USE_DEBUGGING_ASSERTIONS)
		{
			if (pname == GL_TEXTURE_MIN_FILTER)
			{
				EEGL_ASSERT(param == GL_NEAREST || param == GL_LINEAR || param == GL_NEAREST_MIPMAP_NEAREST || param == GL_LINEAR_MIPMAP_NEAREST || param == GL_NEAREST_MIPMAP_LINEAR || param == GL_LINEAR_MIPMAP_LINEAR);
			}
			if (pname == GL_TEXTURE_MAG_FILTER)
			{
				EEGL_ASSERT(param == GL_NEAREST || param == GL_LINEAR);
			}
			if (pname == GL_TEXTURE_WRAP_S || pname == GL_TEXTURE_WRAP_T)
			{
				EEGL_ASSERT(param == GL_CLAMP_TO_EDGE || param == GL_MIRRORED_REPEAT || param == GL_REPEAT);
			}
		}
		glTexParameteri(target, pname, param);
		EEGL_ASSERT_NO_GL_ERROR();
	}
	
//			EEGL_STUB_API_DECO void
//			eeglTexParameterfv(GLenum const target, GLenum const pname, GLfloat const * params)
//			{
//				EEGL_ASSERT(target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP);
//				EEGL_ASSERT(pname == GL_TEXTURE_MIN_FILTER || pname == GL_TEXTURE_MAG_FILTER || pname == GL_TEXTURE_WRAP_S || pname == GL_TEXTURE_WRAP_T);
//				//	TODO: How to get number of parameters?
//				glTexParameterfv(target, pname, params);
//				EEGL_ASSERT_NO_GL_ERROR();
//			}
//			EEGL_STUB_API_DECO void
//			eeglTexParameteriv(GLenum const target, GLenum const pname, GLint const * params)
//			{
//				EEGL_ASSERT(target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP);
//				EEGL_ASSERT(pname == GL_TEXTURE_MIN_FILTER || pname == GL_TEXTURE_MAG_FILTER || pname == GL_TEXTURE_WRAP_S || pname == GL_TEXTURE_WRAP_T);
//				//	TODO: How to get number of parameters?
//				glTexParameteriv(target, pname, params);
//				EEGL_ASSERT_NO_GL_ERROR();
//			}
	
	
	
	EEGL_STUB_API_DECO void
	eeglTexImage2D(GLenum const target, GLint const level, GLint const internalformat, GLsizei const width, GLsizei const height, GLint const border, GLenum const format, GLenum const type, const GLvoid * const data)
	{
		EEGL_ASSERT((target == GL_TEXTURE_2D && eeglGetInteger(GL_TEXTURE_BINDING_2D) != 0) || (target == GL_TEXTURE_CUBE_MAP && eeglGetInteger(GL_TEXTURE_BINDING_CUBE_MAP) != 0));
		
		EEGL_ASSERT(target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP_POSITIVE_X || target == GL_TEXTURE_CUBE_MAP_NEGATIVE_X || target == GL_TEXTURE_CUBE_MAP_POSITIVE_Y || target == GL_TEXTURE_CUBE_MAP_NEGATIVE_Y || target == GL_TEXTURE_CUBE_MAP_POSITIVE_Z || target == GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
		EEGL_ASSERT(level >= 0);
		ASSERTION::EEGL_ASSERT_TEX_IMAGE_2D_INTERNAL_FORMAT_ENUM_CHECK(internalformat);
//			EEGL_ASSERT((width >= 64 && target == GL_TEXTURE_2D) || (width >= 16 && target != GL_TEXTURE_2D));
//			EEGL_ASSERT((height >= 64 && target == GL_TEXTURE_2D) || (height >= 16 && target != GL_TEXTURE_2D));
		
		EEGL_ASSERT((width >= 16 && target == GL_TEXTURE_2D) || (width >= 16 && target != GL_TEXTURE_2D));
		EEGL_ASSERT((height >= 16 && target == GL_TEXTURE_2D) || (height >= 16 && target != GL_TEXTURE_2D));
		
		EEGL_ASSERT(border == 0);
		EEGL_ASSERT(format == internalformat);
		EEGL_ASSERT(type == GL_UNSIGNED_BYTE || type == GL_UNSIGNED_SHORT_5_6_5 || type == GL_UNSIGNED_SHORT_4_4_4_4 || type == GL_UNSIGNED_SHORT_5_5_5_1);
		//	Data pointer can be NULL.
		glTexImage2D(target, level, internalformat, width, height, border, format, type, data);
		EEGL_ASSERT_NO_GL_ERROR();
	}
	
	EEGL_STUB_API_DECO void
	eeglTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *data)
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			EEGL_ASSERT((target == GL_TEXTURE_2D && eeglGetInteger(GL_TEXTURE_BINDING_2D) != 0) || (target == GL_TEXTURE_CUBE_MAP && eeglGetInteger(GL_TEXTURE_BINDING_CUBE_MAP) != 0));
		}

		glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, data);
		EEGL_ASSERT_NO_GL_ERROR();
	}
	
	
	
	
	
	
	
	
	
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END

