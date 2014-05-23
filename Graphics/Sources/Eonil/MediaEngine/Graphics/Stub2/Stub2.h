//
//  Stub2.h
//  Graphics
//
//  Created by Hoon H. on 14/5/24.
//
//

#pragma once
#include "../Common.h"
EONIL_MEDIA_ENGINE_GRAPHICS_STUB2_NAMESPACE_BEGIN





/*
 A trial to make as-is but with C++ OpenGL stub.
 But this is really useless and suspended.
 */

struct
eegl_resource
{
	GLuint	name	=	0;
	
	eegl_resource(GLuint const name) : name(name) {}
	
	operator GLuint() const
	{
		return	name;
	}
};

struct
eegl_buffer : eegl_resource
{
};

struct
eegl_texture : eegl_resource
{
};

struct
eegl_shader : eegl_resource
{
};

struct
eegl_program : eegl_resource
{
	auto	AttachShader(eegl_shader const shader) -> void;
	auto	DetachShader(eegl_shader const shader) -> void;
	
	auto	BindAttribLocation(GLuint const index, GLchar const* name) -> void;
	
	auto	GetActiveAttrib(GLuint const index, GLsizei const bufSize, GLsizei* const length, GLint* const size, GLenum* const type, GLchar* const name) -> void;
	auto	GetActiveUniform(GLuint const index, GLsizei const bufSize, GLsizei* const length, GLint* const size, GLenum* const type, GLchar* const name) -> void;
	auto	GetAttachedShaders(GLsizei const maxCount, GLsizei* const count, GLuint* const shaders) -> void;
	auto	GetAttribLocation(GLchar const* name) -> void;
};

struct
eegl_renderbuffer : eegl_resource
{
};

struct
eegl_framebuffer : eegl_resource
{
};




struct
eegl_context_es_2_0_core
{
	auto	GetError(void) -> GLenum;
	auto	GetBooleanv(GLenum const pname, GLboolean* const params) -> void;
	auto	GetFloatv(GLenum const pname, GLfloat* const params) -> void;
	auto	GetIntegerv(GLenum const pname, GLint* const params) -> void;
	auto	GetFramebufferAttachmentParameteriv(GLenum const target, GLenum const attachment, GLenum const pname, GLint* const params) -> void;
	
	auto	Enable(GLenum const cap) -> void;
	auto	Disable(GLenum const cap) -> void;
	auto	Hint(GLenum const target, GLenum const mode) -> void;
	
	auto	GenBuffers(GLsizei const n, eegl_buffer* const buffers) -> void;
	auto	BindBuffer(GLenum const target, eegl_buffer const buffer) -> void;
	auto	DeleteBuffers(GLsizei const n, eegl_buffer const* const buffers) -> void;
	
	auto	GenTextures(GLsizei const n, eegl_texture* const textures) -> void;
	auto	BindTexture() -> void;
	auto	GenerateMipmap(GLenum const target) -> void;
	auto	ActiveTexture(GLenum const texture) -> void;
	auto	DeleteTextures(GLsizei const n, eegl_texture const* const textures) -> void;
	
	auto	CreateShader() -> eegl_shader;
	auto	CompileShader(eegl_shader const shader) -> void;
	auto	DeleteShader(eegl_shader const shader) -> void;

	auto	CreateProgram() -> eegl_program;
 	auto	UseProgram(eegl_program const program) -> void;
	auto	DeleteProgram(eegl_program const program) -> void;
	
	auto	GenRenderbuffers(GLsizei const n, eegl_renderbuffer* const renderbuffers) -> void;
	auto	BindRenderbuffer(GLenum const target, eegl_renderbuffer const renderbuffer) -> void;
	auto	DeleteRenderbuffers(GLsizei const n, eegl_renderbuffer const* const renderbuffers) -> void;
	
	auto	GenFramebuffers(GLsizei const n, eegl_framebuffer* const framebuffers) -> void;
	auto	BindFramebuffer(GLenum const target, eegl_framebuffer const framebuffer) -> void;
	auto	DeleteFramebuffers(GLsizei const n, eegl_framebuffer const* const framebuffers) -> void;
	
	auto	ColorMask(GLboolean const red, GLboolean const green, GLboolean const blue, GLboolean const alpha) -> void;
	auto	Clear(GLbitfield const mask) -> void;
	
	auto	DrawArray(GLenum const mode, GLint const first, GLsizei const count) -> void;
	auto	DrawElements(GLenum const mode, GLsizei const count, GLenum const type, GLvoid const* const indices) -> void;
	
	auto	Finish(void) -> void;
	auto	Flush(void) -> void;
};

struct
eegl_context_es_2_0_extras
{
	auto	GenBuffer() -> eegl_buffer;
	auto	DeleteBuffer(eegl_buffer const) -> void;
	
	auto	GenTexture() -> eegl_texture;
	auto	DeleteTexture(eegl_texture const) -> void;
	
	auto	GetBoolean(GLenum const pname) -> GLboolean;
	auto	GetFloat(GLenum const pname) -> GLfloat;
	auto	GetInteger(GLenum const pname) -> GLint;
};

struct
eegl_context : eegl_context_es_2_0_core, eegl_context_es_2_0_extras
{
	
};





EONIL_MEDIA_ENGINE_GRAPHICS_STUB2_NAMESPACE_END
