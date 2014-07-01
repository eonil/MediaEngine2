////
////  Stub2.h
////  Graphics
////
////  Created by Hoon H. on 14/5/24.
////
////
//
//#pragma once
//#include "../Common.h"
//EONIL_MEDIA_ENGINE_GRAPHICS_STUB2_NAMESPACE_BEGIN
//
//
//
//
//
///*
// A trial to make as-is but with C++ OpenGL stub.
// But this is really useless and suspended.
// */
//
////
////
////
////
////
////template <typename T>	using	eegl_remote_server_object_proxy_ptr		=	local<T>;
////template <typename T>	using	rep										=	eegl_remote_server_object_proxy_ptr<T>;
//
//
//
//
//template <typename T>	class	eegl_remote_server_object_proxy_ptr;
//
//
//class
//eegl_object
//{
//protected:
//	eegl_object() = delete;
//	
//	////
//	
//	eegl_object(GLuint name);
//	operator GLuint() const;
//	
//private:
//	GLuint	_name;	//	GL spec defines zero-name as null semantics over all places. Framebuffer has a little exceptional stuffs, but same. See `eegl_framebuffer_ptr` for details.
//};
//
//
///*!
// A pointer to a remote object in graphics server.
// This is semantically a pointer, but indicates an object in server instead of
// local memory address.
// */
//template <typename T>
//class
//eegl_remote_server_object_proxy_ptr
//{
//	using	CLASS	=	eegl_remote_server_object_proxy_ptr;
//	
//public:
//	eegl_remote_server_object_proxy_ptr() = default;
//	eegl_remote_server_object_proxy_ptr(eegl_remote_server_object_proxy_ptr const&) = default;
//	eegl_remote_server_object_proxy_ptr(eegl_remote_server_object_proxy_ptr&&) = default;
//	~eegl_remote_server_object_proxy_ptr() = default;
//	
//	auto	operator=(eegl_remote_server_object_proxy_ptr const&) -> eegl_remote_server_object_proxy_ptr& = default;
//	auto	operator=(eegl_remote_server_object_proxy_ptr&&) -> eegl_remote_server_object_proxy_ptr& = default;
//	
//	////
//	
//	eegl_remote_server_object_proxy_ptr(T);
//	operator GLuint() const;
//	
//	auto	operator==(std::nullptr_t const&) const -> bool;
//	auto	operator!=(std::nullptr_t const&) const -> bool;
//	auto	operator==(CLASS const&) const -> bool;
//	auto	operator!=(CLASS const&) const -> bool;
//	
//private:
//	static GLuint const NULL_NUMBER	=	0;
//	
//	T		_remote_obj_ptr	=	NULL_NUMBER;
//};
//
//template <typename T>
//eegl_remote_server_object_proxy_ptr<T>::eegl_remote_server_object_proxy_ptr(T const o) : _remote_obj_ptr(o)
//{
//	static_assert(sizeof(CLASS) == sizeof(GLuint), "Memory layout of `eegl_object_ptr` must be equal to `GLuint`");
//}
//template <typename T>
//eegl_remote_server_object_proxy_ptr<T>::operator GLuint() const
//{
//	return	_remote_obj_ptr;
//}
//
//template <typename T>
//auto
//eegl_remote_server_object_proxy_ptr<T>::operator==(const std::nullptr_t &) const -> bool
//{
//	return	_remote_obj_ptr == NULL_NUMBER;
//}
//template <typename T>
//auto
//eegl_remote_server_object_proxy_ptr<T>::operator!=(const std::nullptr_t &) const -> bool
//{
//	return	_remote_obj_ptr != NULL_NUMBER;
//}
//template <typename T>
//auto
//eegl_remote_server_object_proxy_ptr<T>::operator==(CLASS const& o) const -> bool
//{
//	return	_remote_obj_ptr == o._remote_obj_ptr;
//}
//template <typename T>
//auto
//eegl_remote_server_object_proxy_ptr<T>::operator!=(CLASS const& o) const -> bool
//{
//	return	_remote_obj_ptr != o._remote_obj_ptr;
//}
//
//template <typename T>	using	rep	=	eegl_remote_server_object_proxy_ptr<T>;			//	REmote Proxy pointer.
//
//class	eegl_buffer;
//class	eegl_texture;
//class	eegl_shader;
//class	eegl_program;
//class	eegl_renderbuffer;
//class	eegl_framebuffer;
//
//
//
//
//
//
//
//
//
//
//
//
//struct
//eegl_buffer
//{
//};
//
//struct
//eegl_texture
//{
//};
//
//struct
//eegl_shader
//{
//	auto	CompileShader() -> void;
//};
//
//struct
//eegl_program
//{
//	auto	AttachShader(rep<eegl_shader const> shader) -> void;
//	auto	DetachShader(rep<eegl_shader const> shader) -> void;
//	
//	auto	BindAttribLocation(GLuint index, GLchar const* name) -> void;
//	
//	auto	GetActiveAttrib(GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) -> void;
//	auto	GetActiveUniform(GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) -> void;
//	auto	GetAttachedShaders(GLsizei maxCount, GLsizei* count, GLuint* shaders) -> void;
//	auto	GetAttribLocation(GLchar const* name) -> void;
//};
//
//struct
//eegl_renderbuffer
//{
//};
//
///*!
// @discussion
// OpenGL ES 2.0 spec defines zero-name framebuffer can be used to indicate default framebuffer. (window-system provided)
// Anyway modifying or querying any state from the zero-name framebuffer is prohibited. That means, zero-name is practically
// has null semantics.
// 
// >	While a non-zero framebuffer object name is bound, GL operations on target GL_FRAMEBUFFER affect the bound framebuffer object, 
// >	and queries of target GL_FRAMEBUFFER or of framebuffer details such as GL_DEPTH_BITS return state from the bound framebuffer object.
// >	While framebuffer object name zero is bound, as in the initial state, attempts to modify or query state on target GL_FRAMEBUFFER
// >	generates an GL_INVALID_OPERATION error.
// 
// From these facts, I decided treating zero-name as null is also makes sense even on framebuffer. Zero-name framebuffer just means
// indicating a default buffer with null pointer.
// */
//struct
//eegl_framebuffer
//{
//};
//
//
//
//
//struct
//eegl_context_es_2_0_core
//{
//	auto	GetError(void) -> GLenum;
//	auto	GetBooleanv(GLenum pname, GLboolean* params) -> void;
//	auto	GetFloatv(GLenum pname, GLfloat* const params) -> void;
//	auto	GetIntegerv(GLenum pname, GLint* const params) -> void;
//	auto	GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* const params) -> void;
//	
//	////
//	
//	auto	Enable(GLenum cap) -> void;
//	auto	Disable(GLenum cap) -> void;
//	auto	Hint(GLenum target, GLenum mode) -> void;
//	
//	auto	GenBuffers(GLsizei n, eegl_buffer* buffers) -> void;
//	auto	BindBuffer(GLenum target, eegl_buffer buffer) -> void;
//	auto	DeleteBuffers(GLsizei n, eegl_buffer const* buffers) -> void;
////	auto	BufferData
//	
//	auto	GenTextures(GLsizei n, eegl_texture_ptr* textures) -> void;
//	auto	BindTexture() -> void;
//	auto	GenerateMipmap(GLenum target) -> void;
//	auto	ActiveTexture(GLenum texture) -> void;
//	auto	DeleteTextures(GLsizei n, eegl_texture const* textures) -> void;
//	
//	auto	CreateShader() -> rep<eegl_shader>;
//	auto	DeleteShader(rep<eegl_shader> shader) -> void;
//
//	auto	CreateProgram() -> rep<eegl_program>;
// 	auto	UseProgram(rep<eegl_program> program) -> void;
//	auto	DeleteProgram(rep<eegl_program> program) -> void;
//	
//	auto	GenRenderbuffers(GLsizei n, eegl_renderbuffer* renderbuffers) -> void;
//	auto	BindRenderbuffer(GLenum target, eegl_renderbuffer renderbuffer) -> void;
//	auto	DeleteRenderbuffers(GLsizei n, eegl_renderbuffer const* renderbuffers) -> void;
//	
//	auto	GenFramebuffers(GLsizei n, eegl_framebuffer* framebuffers) -> void;
//	auto	BindFramebuffer(GLenum target, eegl_framebuffer framebuffer) -> void;
//	auto	DeleteFramebuffers(GLsizei n, eegl_framebuffer const* framebuffers) -> void;
//	
////	auto	ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) -> void;
//	auto	Clear(GLbitfield mask) -> void;
//	
//	auto	DrawArray(GLenum mode, GLint first, GLsizei count) -> void;
//	auto	DrawElements(GLenum mode, GLsizei count, GLenum type, GLvoid const* indices) -> void;
//	
//	auto	Finish(void) -> void;
//	auto	Flush(void) -> void;
//};
//
//struct
//eegl_context_es_2_0_extras
//{
//	auto	GetBoolean(GLenum pname) -> GLboolean;
//	auto	GetFloat(GLenum pname) -> GLfloat;
//	auto	GetInteger(GLenum pname) -> GLint;
//	
//	////
//	
//	auto	GenBuffer() -> local<eegl_buffer>;
//	auto	DeleteBuffer(eegl_buffer) -> void;
//	
//	auto	GenTexture() -> rep<eegl_texture>;
//	auto	DeleteTexture(rep<eegl_texture>) -> void;
//};
//
//struct
//eegl_context : eegl_context_es_2_0_core, eegl_context_es_2_0_extras
//{
//	
//};
//
//
//
//
//
//EONIL_MEDIA_ENGINE_GRAPHICS_STUB2_NAMESPACE_END
