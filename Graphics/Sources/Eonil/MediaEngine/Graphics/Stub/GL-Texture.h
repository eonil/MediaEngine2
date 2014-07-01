//
//  GL-Texture.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__GL_Texture__
#define __EonilGraphics__GL_Texture__
#include "GL-Common.h"
namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	namespace
	Stub
	{
		
		
		
		
		
		
		
		EEGL_STUB_API_DECO GLboolean const	eeglIsTexture(GLuint const texture);
		
		EEGL_STUB_API_DECO void				eeglGetTexParameterfv(GLenum const target, GLenum const pname, GLfloat* const params);
		EEGL_STUB_API_DECO void				eeglGetTexParameteriv(GLenum const target, GLenum const pname, GLint* const params);
		EEGL_STUB_API_DECO GLfloat const	eeglGetTexParameterf(GLenum const target, GLenum const pname);
		EEGL_STUB_API_DECO GLint const		eeglGetTexParameteri(GLenum const target, GLenum const pname);
		////
		
		EEGL_STUB_API_DECO void			eeglGenTextures(GLsizei const n, GLuint* const textures);
		EEGL_STUB_API_DECO GLuint const	eeglGenTexture();
		EEGL_STUB_API_DECO void			eeglDeleteTextures(GLsizei const n, GLuint const * const textures);
		EEGL_STUB_API_DECO void			eeglDeleteTexture(GLuint const name);
		EEGL_STUB_API_DECO void			eeglBindTexture(GLenum const target, GLuint const texture);
		EEGL_STUB_API_DECO void			eeglUnbindTexture(GLenum const target);

		////
		
		EEGL_STUB_API_DECO void			eeglTexParameterf(GLenum const target, GLenum const pname, GLfloat const param);
		EEGL_STUB_API_DECO void			eeglTexParameteri(GLenum const target, GLenum const pname, GLint const param);
		
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
		
		
		
		EEGL_STUB_API_DECO void			eeglTexImage2D(GLenum const target, GLint const level, GLint const internalformat, GLsizei const width, GLsizei const height, GLint const border, GLenum const format, GLenum const type, const GLvoid * const data);
		EEGL_STUB_API_DECO void			eeglTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *data);
		
		
		
	
		
		
		
		
		
		
	}
}}}}
#endif /* defined(__EonilGraphics__GL_Texture__) */
