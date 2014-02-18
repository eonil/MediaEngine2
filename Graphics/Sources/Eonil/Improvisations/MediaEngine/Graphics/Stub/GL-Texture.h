//
//  GL-Texture.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__GL_Texture__
#define __EonilGraphics__GL_Texture__

#include "GL-Get.h"
#include "GL-Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Stub
	{			
		EEGL_INLINE GLboolean const	eeglIsTexture(GLuint const texture);
		
		EEGL_INLINE void				eeglGetTexParameterfv(GLenum const target, GLenum const pname, GLfloat* const params);
		EEGL_INLINE void				eeglGetTexParameteriv(GLenum const target, GLenum const pname, GLint* const params);
		EEGL_INLINE GLfloat const	eeglGetTexParameterf(GLenum const target, GLenum const pname);
		EEGL_INLINE GLint const		eeglGetTexParameteri(GLenum const target, GLenum const pname);
		////
		
		EEGL_INLINE void			eeglGenTextures(GLsizei const n, GLuint* const textures);
		EEGL_INLINE GLuint const	eeglGenTexture();
		EEGL_INLINE void			eeglDeleteTextures(GLsizei const n, GLuint const * const textures);
		EEGL_INLINE void			eeglDeleteTexture(GLuint const name);
		EEGL_INLINE void			eeglBindTexture(GLenum const target, GLuint const texture);
		EEGL_INLINE void			eeglUnbindTexture(GLenum const target);

		////
		
		EEGL_INLINE void			eeglTexParameterf(GLenum const target, GLenum const pname, GLfloat const param);
		EEGL_INLINE void			eeglTexParameteri(GLenum const target, GLenum const pname, GLint const param);
		
//			EEGL_INLINE void
//			eeglTexParameterfv(GLenum const target, GLenum const pname, GLfloat const * params)
//			{
//				EEGL_ASSERT(target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP);
//				EEGL_ASSERT(pname == GL_TEXTURE_MIN_FILTER || pname == GL_TEXTURE_MAG_FILTER || pname == GL_TEXTURE_WRAP_S || pname == GL_TEXTURE_WRAP_T);
//				//	TODO: How to get number of parameters?
//				glTexParameterfv(target, pname, params);
//				EEGL_ASSERT_NO_GL_ERROR();
//			}
//			EEGL_INLINE void
//			eeglTexParameteriv(GLenum const target, GLenum const pname, GLint const * params)
//			{
//				EEGL_ASSERT(target == GL_TEXTURE_2D || target == GL_TEXTURE_CUBE_MAP);
//				EEGL_ASSERT(pname == GL_TEXTURE_MIN_FILTER || pname == GL_TEXTURE_MAG_FILTER || pname == GL_TEXTURE_WRAP_S || pname == GL_TEXTURE_WRAP_T);
//				//	TODO: How to get number of parameters?
//				glTexParameteriv(target, pname, params);
//				EEGL_ASSERT_NO_GL_ERROR();
//			}
		
		
		
		EEGL_INLINE void			eeglTexImage2D(GLenum const target, GLint const level, GLint const internalformat, GLsizei const width, GLsizei const height, GLint const border, GLenum const format, GLenum const type, const GLvoid * const pixels);
		EEGL_INLINE void			eeglTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
		
		
		
		
	}
	
}}}}

#endif /* defined(__EonilGraphics__GL_Texture__) */
