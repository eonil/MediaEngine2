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
 But this is really not required right now, and suspended.
 
 Stub(1)	=	C level procedural API with heavy assertions.
 Stub2		=	C++ level object-oriented API. Thin wrapper around C API. Likely to be renamed to something else.
 
 */





/*!
 A proxy to a remote object in graphics server.
 A proxy object is semantically a pointer to remote object. Treat this like a pointer.
 The only noticeable differences are:
 
 -	You cannot access the value at all using dereference operator `*` because it is located on remote machine.
 -	Then, you cannot create a proxy directly using address-of operator `&`.
 -	You access feature directly on member access operator `.` rather then indirect access operator `->`.
 
 @note
 I considered using of fully pointer form by wrapping templated local pointer class.
 But that is unnecessarily complex, and still this class as subtle differences from real pointers
 like address-of, deference stuffs. It's better to take the difference than trying to mimic pointers.
 */
class
eegl_object_proxy
{
	using	CLASS	=	eegl_object_proxy;
public:
	eegl_object_proxy() = default;
	eegl_object_proxy(eegl_object_proxy const&) = default;
	eegl_object_proxy(eegl_object_proxy&&) = default;
	~eegl_object_proxy() = default;
	
	auto	operator=(eegl_object_proxy const&) -> eegl_object_proxy& = default;
	auto	operator=(eegl_object_proxy&&) -> eegl_object_proxy& = default;
	
	////
	
	eegl_object_proxy(GLuint name);
	operator GLuint() const;
	
	auto	operator==(std::nullptr_t const&) const -> bool;
	auto	operator!=(std::nullptr_t const&) const -> bool;
	auto	operator==(CLASS const&) const -> bool;
	auto	operator!=(CLASS const&) const -> bool;
	
private:
	static GLuint const NULL_NUMBER	=	0;
	
	GLuint	_name	=	NULL_NUMBER;	//	GL spec defines zero-name as null semantics over all places. Framebuffer has a little exceptional stuffs, but same. See `eegl_framebuffer_proxy` for details.
};



















struct
eegl_buffer_proxy : eegl_object_proxy
{
	using	eegl_object_proxy::eegl_object_proxy;
	
	////
	
	auto	IsBuffer() -> GLboolean;
};

struct
eegl_texture_proxy : eegl_object_proxy
{
	using	eegl_object_proxy::eegl_object_proxy;
	
	////
	
	auto	IsTexture() -> GLboolean;
};

/*!
 Object methods are defined here if the methods can be called without binding to a context.
 */
struct
eegl_shader_proxy : eegl_object_proxy
{
	using	eegl_object_proxy::eegl_object_proxy;
	
	////
	
	auto	IsShader() -> GLboolean;
};

/*!
 Object methods are defined here if the methods can be called without binding to a context.
 */
struct
eegl_program_proxy : eegl_object_proxy
{
	using	eegl_object_proxy::eegl_object_proxy;
	
	////
	
	auto	GetActiveAttrib(GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) -> void;
	auto	GetActiveUniform(GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) -> void;
	auto	GetAttachedShaders(GLsizei maxCount, GLsizei * count, GLuint * shaders) -> void;
	auto	GetAttribLocation(GLchar const * name) -> void;
	auto	IsProgram() -> GLboolean;
	auto	ValidateProgram() -> void;
	
	////
	
	auto	LinkProgram() -> void;
	auto	AttachShader(eegl_shader_proxy shader) -> void;
	auto	DetachShader(eegl_shader_proxy shader) -> void;
	auto	BindAttribLocation(GLuint index, GLchar const * name) -> void;
};

struct
eegl_renderbuffer_proxy : eegl_object_proxy
{
	using	eegl_object_proxy::eegl_object_proxy;
	
	////
};

/*!
 @discussion
 OpenGL ES 2.0 spec defines zero-name framebuffer can be used to indicate default framebuffer. (window-system provided)
 Anyway modifying or querying any state from the zero-name framebuffer is prohibited. That means, zero-name is practically
 has null semantics.
 
 >	While a non-zero framebuffer object name is bound, GL operations on target GL_FRAMEBUFFER affect the bound framebuffer object, 
 >	and queries of target GL_FRAMEBUFFER or of framebuffer details such as GL_DEPTH_BITS return state from the bound framebuffer object.
 >	While framebuffer object name zero is bound, as in the initial state, attempts to modify or query state on target GL_FRAMEBUFFER
 >	generates an GL_INVALID_OPERATION error.
 
 From these facts, I decided treating zero-name as null is also makes sense even on framebuffer. Zero-name framebuffer just means
 indicating a default buffer with null pointer.
 */
struct
eegl_framebuffer_proxy : eegl_object_proxy
{
	using	eegl_object_proxy::eegl_object_proxy;
};







struct
eegl_context_es_2_0_core
{
	auto	GetError(void) -> GLenum;
	auto	GetBooleanv(GLenum pname, GLboolean * params) -> void;
	auto	GetFloatv(GLenum pname, const GLfloat * params) -> void;
	auto	GetIntegerv(GLenum pname, const GLint * params) -> void;
	auto	GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, const GLint * params) -> void;
	auto	CheckFramebufferStatus(GLenum target) -> GLenum;
//	auto	PixelStorei(GLenum pname, GLint param) -> void;
	
//	auto	ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * data) -> void;
	
	////
	
	auto	Enable(GLenum cap) -> void;
	auto	Disable(GLenum cap) -> void;
//	auto	Hint(GLenum target, GLenum mode) -> void;
	
	auto	GenBuffers(GLsizei n, eegl_buffer_proxy* buffers) -> void;
	auto	BindBuffer(GLenum target, eegl_buffer_proxy buffer) -> void;
	auto	BufferData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage) -> void;
	auto	BufferSubdata(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data) -> void;
	auto	DeleteBuffers(GLsizei n, const eegl_buffer_proxy * buffers) -> void;
	
	auto	GenTextures(GLsizei n, eegl_texture_proxy* textures) -> void;
	auto	BindTexture(GLenum target, eegl_texture_proxy texture) -> void;
//	auto	GenerateMipmap(GLenum target) -> void;
	auto	TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * data) -> void;
	auto	TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * data) -> void;
	auto	TexParameterf(GLenum target, GLenum pname, GLfloat param) -> void;
	auto	TexParameteri(GLenum target, GLenum pname, GLint param) -> void;
	auto	ActiveTexture(GLenum texture) -> void;
	auto	DeleteTextures(GLsizei n, eegl_texture_proxy const* textures) -> void;
	
	auto	CreateShader(GLenum type) -> eegl_shader_proxy;
	auto	CompileShader(eegl_shader_proxy shader) -> void;
	auto	DeleteShader(eegl_shader_proxy shader) -> void;

	auto	CreateProgram() -> eegl_program_proxy;
 	auto	UseProgram(eegl_program_proxy program) -> void;
	auto	DeleteProgram(eegl_program_proxy program) -> void;
	
	auto	GenRenderbuffers(GLsizei n, eegl_renderbuffer_proxy * renderbuffers) -> void;
	auto	BindRenderbuffer(GLenum target, eegl_renderbuffer_proxy renderbuffer) -> void;
	auto	RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) -> void;
	auto	DeleteRenderbuffers(GLsizei n, const eegl_renderbuffer_proxy * renderbuffers) -> void;
	
	auto	GenFramebuffers(GLsizei n, eegl_framebuffer_proxy * framebuffers) -> void;
	auto	BindFramebuffer(GLenum target, eegl_framebuffer_proxy framebuffer) -> void;
	auto	FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) -> void;
	auto	FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) -> void;
	auto	DeleteFramebuffers(GLsizei n, const eegl_framebuffer_proxy * framebuffers) -> void;
	
	auto	Scissor(GLint x, GLint y, GLsizei width, GLsizei height) -> void;
	auto	BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) -> void;
	auto	BlendFunc(GLenum sfactor, GLenum dfactor) -> void;
	auto	BlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) -> void;
	
//	auto	ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) -> void;
	auto	Clear(GLbitfield mask) -> void;
	auto	DrawArray(GLenum mode, GLint first, GLsizei count) -> void;
	auto	DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices) -> void;
	
//	auto	Finish(void) -> void;
//	auto	Flush(void) -> void;
};

struct
eegl_context_es_2_0_extras
{
	auto	GetBoolean(GLenum pname) -> GLboolean;
	auto	GetFloat(GLenum pname) -> GLfloat;
	auto	GetInteger(GLenum pname) -> GLint;
	
	////
	
	auto	GenBuffer() -> eegl_buffer_proxy;
	auto	DeleteBuffer(eegl_buffer_proxy) -> void;
	
	auto	GenTexture() -> eegl_texture_proxy;
	auto	DeleteTexture(eegl_texture_proxy) -> void;
};










struct
eegl_context : eegl_context_es_2_0_core, eegl_context_es_2_0_extras
{
};





EONIL_MEDIA_ENGINE_GRAPHICS_STUB2_NAMESPACE_END
