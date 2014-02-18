//
//  GL-Context.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__GL_Context__
#define __EonilGraphics__GL_Context__

#include "../Common.h"
#include "GL-Common.h"
#include "GL-Framebuffer.h"
#include "GL-Texture.h"
#include "GL-Program.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Stub
	{
		EEGL_INLINE void			eeglViewport(GLint const x, GLint const y, GLsizei const width, GLsizei const height);
		EEGL_INLINE void			eeglScissor(GLint const x, GLint const y, GLsizei const width, GLsizei const height);

		
		
		////	Capability.
		
		EEGL_INLINE void			eeglEnable(GLenum const cap);
		EEGL_INLINE void			eeglDisable(GLenum const cap);
		EEGL_INLINE GLboolean const	eeglIsEnabled(GLenum const cap);
		
		
		
		////	State
		
		EEGL_INLINE void			eeglBlendFunc(GLenum const sfactor, GLenum const dfactor);
		EEGL_INLINE void			eeglBlendEquation(GLenum const mode);
		EEGL_INLINE void			eeglBlendColor(GLclampf const red, GLclampf const green, GLclampf const blue, GLclampf const alpha);
		EEGL_INLINE void			eeglBlendEquationSeparate(GLenum const modeRGB, GLenum const modeAlpha);
		EEGL_INLINE void			eeglBlendFuncSeparate(GLenum const srcRGB, GLenum const dstRGB, GLenum const srcAlpha, GLenum const dstAlpha);
		
		EEGL_INLINE void			eeglDepthFunc(GLenum const func);
		EEGL_INLINE void			eeglDepthRangef(GLclampf const nearVal, GLclampf const farVal);
		
		/*!
		 TODO: Implement stencil and depth operation function stubs.
		 */
//			EEGL_INLINE void			eeglStencilFunc(GLenum const func, GLint const ref, GLuint const mask);
		
		////	Texturing.
		
		EEGL_INLINE void			eeglActiveTexture(GLenum const texture);
		
		
		
		////	Vertex channeling.
		
		EEGL_INLINE void			eeglEnableVertexAttribArray(GLuint const index);
		EEGL_INLINE void			eeglDisableVertexAttribArray(GLuint const index);
		EEGL_INLINE void			eeglVertexAttribPointer(GLuint const indx, GLint const size, GLenum const type, GLboolean const normalized, GLsizei const stride, GLvoid const * const ptr);
		
		
		
		
		////	Drawing.
		
		EEGL_INLINE void			eeglClear(GLbitfield const mask);
		EEGL_INLINE void			eeglClearDepthf(GLclampf depth);
		EEGL_INLINE void			eeglClearColor(GLclampf const red, GLclampf const green, GLclampf const blue, GLclampf const alpha);
		EEGL_INLINE void			eeglDrawArrays(GLenum const mode, GLint const first, GLsizei const count);
		EEGL_INLINE void			eeglDrawElement(GLenum const mode, GLsizei const count, GLenum const type, GLvoid const * const indices);
		
	}	
	
}}}}

#endif /* defined(__EonilGraphics__GL_Context__) */
