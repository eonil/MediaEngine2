//
//  GL-Context.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#pragma once
#include "GL-Common.h"
#include "GL-Framebuffer.h"
#include "GL-Texture.h"
#include "GL-Program.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN
namespace
Stub
{
	////	Get.
	
	EEGL_STUB_API_DECO void				eeglGetBooleanv(GLenum const pname, GLboolean * const params);
	EEGL_STUB_API_DECO void				eeglGetFloatv(GLenum const pname, GLfloat * const params);
	EEGL_STUB_API_DECO void				eeglGetIntegerv(GLenum const pname, GLint * const params);
	
	EEGL_STUB_API_DECO GLboolean const	eeglGetBoolean(GLenum const pname);
	EEGL_STUB_API_DECO GLboolean const	eeglGetFloat(GLenum const pname);
	EEGL_STUB_API_DECO GLint const		eeglGetInteger(GLenum const pname);
	EEGL_STUB_API_DECO GLubyte const*	eeglGetString(GLenum const name);
	
	EEGL_STUB_API_DECO void				eeglGetVertexAttribfv(GLuint const index, GLenum const pname, GLfloat * const params);
	EEGL_STUB_API_DECO void				eeglGetVertexAttribiv(GLuint const index, GLenum const pname, GLint * const params);
	EEGL_STUB_API_DECO GLfloat const	eeglGetVertexAttribf(GLuint const index, GLenum const pname);
	EEGL_STUB_API_DECO GLint const		eeglGetVertexAttribi(GLuint const index, GLenum const pname);
	
	EEGL_STUB_API_DECO void				eeglGetVertexAttribPointerv(GLuint const index, GLenum const pname, GLvoid** const pointer);
	EEGL_STUB_API_DECO GLvoid* const	eeglGetVertexAttribPointerv(GLuint const index, GLenum const pname);
	
#ifdef	__cplusplus
#endif
	
	EEGL_STUB_API_DECO void				eeglViewport(GLint const x, GLint const y, GLsizei const width, GLsizei const height);
	EEGL_STUB_API_DECO void				eeglScissor(GLint const x, GLint const y, GLsizei const width, GLsizei const height);

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	////	Capability.
	
	EEGL_STUB_API_DECO void				eeglEnable(GLenum const cap);
	EEGL_STUB_API_DECO void				eeglDisable(GLenum const cap);
	EEGL_STUB_API_DECO GLboolean const	eeglIsEnabled(GLenum const cap);
	
	
	
	////	Per-fragment operations.
	
//		EEGL_STUB_API_DECO void			eeglStencilFunc(GLenum const func, GLint const ref, GLuint const mask);
	EEGL_STUB_API_DECO void			eeglStencilFuncSeparate(GLenum const face, GLenum const func, GLint const ref, GLuint const mask);
//		EEGL_STUB_API_DECO void			eeglStencilOp(GLenum const sfail, GLenum const dpfail, GLenum const dppass);
	EEGL_STUB_API_DECO void			eeglStencilOpSeparate(GLenum const face, GLenum const sfail, GLenum const dpfail, GLenum const dppass);
	
	EEGL_STUB_API_DECO void			eeglDepthFunc(GLenum const func);
	EEGL_STUB_API_DECO void			eeglDepthRangef(GLclampf const nearVal, GLclampf const farVal);
	
	EEGL_STUB_API_DECO void			eeglBlendFunc(GLenum const sfactor, GLenum const dfactor);
	EEGL_STUB_API_DECO void			eeglBlendEquation(GLenum const mode);
	EEGL_STUB_API_DECO void			eeglBlendColor(GLclampf const red, GLclampf const green, GLclampf const blue, GLclampf const alpha);
	EEGL_STUB_API_DECO void			eeglBlendEquationSeparate(GLenum const modeRGB, GLenum const modeAlpha);
	EEGL_STUB_API_DECO void			eeglBlendFuncSeparate(GLenum const srcRGB, GLenum const dstRGB, GLenum const srcAlpha, GLenum const dstAlpha);
	
	
	////	Texturing.
	
	EEGL_STUB_API_DECO void			eeglActiveTexture(GLenum const texture);
	
	
	
	////	Vertex channeling.
	
	EEGL_STUB_API_DECO void			eeglEnableVertexAttribArray(GLuint const index);
	EEGL_STUB_API_DECO void			eeglDisableVertexAttribArray(GLuint const index);
	EEGL_STUB_API_DECO void			eeglVertexAttribPointer(GLuint const indx, GLint const size, GLenum const type, GLboolean const normalized, GLsizei const stride, GLvoid const * const ptr);
	
	
	
	
	////	Drawing.
	
	EEGL_STUB_API_DECO void			eeglClear(GLbitfield const mask);
	EEGL_STUB_API_DECO void			eeglClearDepthf(GLclampf depth);
	EEGL_STUB_API_DECO void			eeglClearColor(GLclampf const red, GLclampf const green, GLclampf const blue, GLclampf const alpha);
	EEGL_STUB_API_DECO void			eeglClearStencil(GLint const s);
	EEGL_STUB_API_DECO void			eeglDrawArrays(GLenum const mode, GLint const first, GLsizei const count);
	EEGL_STUB_API_DECO void			eeglDrawElement(GLenum const mode, GLsizei const count, GLenum const type, GLvoid const * const indices);
	
}	

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END
