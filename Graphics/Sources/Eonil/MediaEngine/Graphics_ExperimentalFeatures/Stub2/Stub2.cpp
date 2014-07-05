//
//  Stub2.cpp
//  Graphics
//
//  Created by Hoon H. on 14/5/24.
//
//

#include "Stub2.h"
#include "../../Graphics/____internal_impl_of_opengl_es_2_0_driver____/Stub/GL.h"
EONIL_MEDIA_ENGINE_GRAPHICS_STUB2_NAMESPACE_BEGIN
using namespace ____internal_impl_of_opengl_es_2_0_driver____::Stub;











eegl_object_proxy::eegl_object_proxy(GLuint const o) : _name(o)
{
	static_assert(sizeof(CLASS) == sizeof(GLuint), "Memory layout of `eegl_object_ptr` must be equal to `GLuint`");
}
eegl_object_proxy::operator GLuint() const
{
	return	_name;
}

auto
eegl_object_proxy::operator==(const std::nullptr_t &) const -> bool
{
	return	_name == NULL_NUMBER;
}
auto
eegl_object_proxy::operator!=(const std::nullptr_t &) const -> bool
{
	return	_name != NULL_NUMBER;
}
auto
eegl_object_proxy::operator==(CLASS const& o) const -> bool
{
	return	_name == o._name;
}
auto
eegl_object_proxy::operator!=(CLASS const& o) const -> bool
{
	return	_name != o._name;
}

static_assert(sizeof(eegl_object_proxy) == sizeof(GLuint), "Memory layout of `eegl_object_proxy` must be equal to `GLuint`");


















auto
eegl_buffer_proxy::IsBuffer() -> GLboolean
{
	return	eeglIsBuffer(*this);
}


















auto
eegl_texture_proxy::IsTexture() -> GLboolean
{
	return	eeglIsTexture(*this);
}















auto
eegl_shader_proxy::IsShader() -> GLboolean
{
	return	eeglIsShader(*this);
}















auto
eegl_program_proxy::GetActiveAttrib(GLuint const index, GLsizei const bufSize, GLsizei * const length, GLint * const size, GLenum * const type, GLchar * const name) -> void
{
	eeglGetActiveAttrib(*this, index, bufSize, length, size, type, name);
}
auto
eegl_program_proxy::GetActiveUniform(GLuint const index, GLsizei const bufSize, GLsizei * const length, GLint * const size, GLenum * const type, GLchar * const name) -> void
{
	eeglGetActiveUniform(*this, index, bufSize, length, size, type, name);
}
auto
eegl_program_proxy::GetAttachedShaders(GLsizei const maxCount, GLsizei * const count, GLuint * const shaders) -> void
{
	eeglGetAttachedShaders(*this, maxCount, count, shaders);
}
auto
eegl_program_proxy::GetAttribLocation(GLchar const * name) -> void
{
	eeglGetAttribLocation(*this, name);
}
auto
eegl_program_proxy::IsProgram() -> GLboolean
{
	return	eeglIsProgram(*this);
}
auto
eegl_program_proxy::ValidateProgram() -> void
{
	eeglValidateProgram(*this);
}




auto
eegl_program_proxy::LinkProgram() -> void
{
	eeglLinkProgram(*this);
}
auto
eegl_program_proxy::AttachShader(eegl_shader_proxy const shader) -> void
{
	eeglAttachShader(*this, shader);
}
auto
eegl_program_proxy::DetachShader(eegl_shader_proxy const shader) -> void
{
	eeglAttachShader(*this, shader);
}
auto
eegl_program_proxy::BindAttribLocation(GLuint index, GLchar const* name) -> void
{
	eeglBindAttribLocation(*this, index, name);
}































auto
eegl_context_es_2_0_core::CheckFramebufferStatus(GLenum const target) -> GLenum
{
	return	eeglCheckFramebufferStatus(target);
}
//auto
//eegl_context_es_2_0_core::PixelStorei(GLenum const pname, GLint const param) -> void
//{
//}
//auto
//eegl_context_es_2_0_core::ReadPixels(GLint const x, GLint const y, GLsizei const width, GLsizei const height, GLenum const format, GLenum const type, GLvoid * const data) -> void
//{
//
//}




auto
eegl_context_es_2_0_core::Enable(GLenum const cap) -> void
{
	eeglEnable(cap);
}
auto
eegl_context_es_2_0_core::Disable(GLenum const cap) -> void
{
	eeglDisable(cap);
}
//auto
//eegl_context_es_2_0_core::Hint(GLenum const target, GLenum const mode) -> void
//{
//	eeglHint(target, mode);
//}




auto
eegl_context_es_2_0_core::GenBuffers(GLsizei const n, eegl_buffer_proxy* const buffers) -> void
{
	eeglGenBuffers(n, reinterpret_cast<GLuint*>(buffers));
}
auto
eegl_context_es_2_0_core::BindBuffer(GLenum const target, eegl_buffer_proxy const buffer) -> void
{
	eeglBindBuffer(target, buffer);
}
auto
eegl_context_es_2_0_core::DeleteBuffers(GLsizei const n, eegl_buffer_proxy const* const buffers) -> void
{
	eeglDeleteBuffers(n, reinterpret_cast<GLuint const*>(buffers));
}
auto
eegl_context_es_2_0_core::BufferData(GLenum const target, GLsizeiptr const size, const GLvoid * const data, GLenum const usage) -> void
{
	eeglBufferData(target, size, data, usage);
}
auto
eegl_context_es_2_0_core::BufferSubdata(GLenum const target, GLintptr const offset, GLsizeiptr const size, const GLvoid * const data) -> void
{
	eeglBufferSubData(target, offset, size, data);
}





auto
eegl_context_es_2_0_core::CreateShader(GLenum const type) -> eegl_shader_proxy
{
	return	eeglCreateShader(type);
}
auto
eegl_context_es_2_0_core::CompileShader(eegl_shader_proxy const shader) -> void
{
	eeglCompileShader(shader);
}
auto
eegl_context_es_2_0_core::DeleteShader(eegl_shader_proxy const shader) -> void
{
	eeglDeleteShader(shader);
}



auto
eegl_context_es_2_0_core::CreateProgram() -> eegl_program_proxy
{
	return	eeglCreateProgram();
}
auto
eegl_context_es_2_0_core::UseProgram(eegl_program_proxy const program) -> void
{
	eeglUseProgram(program);
}
auto
eegl_context_es_2_0_core::DeleteProgram(eegl_program_proxy const program) -> void
{
	eeglDeleteProgram(program);
}




auto
eegl_context_es_2_0_core::GenRenderbuffers(GLsizei n, eegl_renderbuffer_proxy * renderbuffers) -> void
{
	eeglGenRenderbuffers(n, reinterpret_cast<GLuint *>(renderbuffers));
}
auto
eegl_context_es_2_0_core::BindRenderbuffer(GLenum target, eegl_renderbuffer_proxy renderbuffer) -> void
{
	eeglBindRenderbuffer(target, renderbuffer);
}
auto
eegl_context_es_2_0_core::DeleteRenderbuffers(GLsizei n, const eegl_renderbuffer_proxy * renderbuffers) -> void
{
	eeglDeleteRenderbuffers(n, reinterpret_cast<GLuint const *>(renderbuffers));
}



auto
eegl_context_es_2_0_core::GenTextures(GLsizei const n, eegl_texture_proxy * const textures) -> void
{
	eeglGenTextures(n, reinterpret_cast<GLuint*>(textures));
}
auto
eegl_context_es_2_0_core::BindTexture(GLenum const target, eegl_texture_proxy const texture) -> void
{
	eeglBindTexture(target, texture);
}
//auto
//eegl_context_es_2_0_core::GenerateMipmap(GLenum const target) -> void
//{
//}
auto
eegl_context_es_2_0_core::TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * data) -> void
{
	eeglTexImage2D(target, level, internalformat, width, height, border, format, type, data);
}
auto
eegl_context_es_2_0_core::TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * data) -> void
{
	eeglTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, data);
}
auto
eegl_context_es_2_0_core::TexParameterf(GLenum target, GLenum pname, GLfloat param) -> void
{
	eeglTexParameterf(target, pname, param);
}
auto
eegl_context_es_2_0_core::TexParameteri(GLenum target, GLenum pname, GLint param) -> void
{
	eeglTexParameteri(target, pname, param);
}
auto
eegl_context_es_2_0_core::ActiveTexture(GLenum const texture) -> void
{
	eeglActiveTexture(texture);
}
auto
eegl_context_es_2_0_core::DeleteTextures(GLsizei const n, eegl_texture_proxy const* const textures) -> void
{
	eeglDeleteTextures(n, reinterpret_cast<GLuint const*>(textures));
}



auto
eegl_context_es_2_0_core::GenFramebuffers(GLsizei const n, eegl_framebuffer_proxy * const framebuffers) -> void
{
	eeglGenFramebuffers(n, reinterpret_cast<GLuint *>(framebuffers));
}
auto
eegl_context_es_2_0_core::BindFramebuffer(GLenum const target, eegl_framebuffer_proxy const framebuffer) -> void
{
	eeglBindFramebuffer(target, framebuffer);
}
auto
eegl_context_es_2_0_core::FramebufferRenderbuffer(GLenum const target, GLenum const attachment, GLenum const renderbuffertarget, GLuint const renderbuffer) -> void
{
	eeglFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}
auto
eegl_context_es_2_0_core::FramebufferTexture2D(GLenum const target, GLenum const attachment, GLenum const textarget, GLuint const texture, GLint const level) -> void
{
	eeglFramebufferTexture2D(target, attachment, textarget, texture, level);
}
auto
eegl_context_es_2_0_core::DeleteFramebuffers(GLsizei const n, const eegl_framebuffer_proxy * const framebuffers) -> void
{
	eeglDeleteFramebuffers(n, reinterpret_cast<GLuint const *>(framebuffers));
}



auto
eegl_context_es_2_0_core::Scissor(GLint const x, GLint const y, GLsizei const width, GLsizei const height) -> void
{
	eeglScissor(x, y, width, height);
}
auto
eegl_context_es_2_0_core::BlendFuncSeparate(GLenum const srcRGB, GLenum const dstRGB, GLenum const srcAlpha, GLenum const dstAlpha) -> void
{
	eeglBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}
auto
eegl_context_es_2_0_core::BlendFunc(GLenum const sfactor, GLenum const dfactor) -> void
{
	eeglBlendFunc(sfactor, dfactor);
}
auto
eegl_context_es_2_0_core::BlendColor(GLclampf const red, GLclampf const green, GLclampf const blue, GLclampf const alpha) -> void
{
	
	eeglBlendColor(red, green, blue, alpha);
}




auto
eegl_context_es_2_0_core::Clear(GLbitfield mask) -> void
{
	eeglClear(mask);
}
auto
eegl_context_es_2_0_core::DrawArray(GLenum const mode, GLint const first, GLsizei const count) -> void
{
	eeglDrawArrays(mode, first, count);
}
auto
eegl_context_es_2_0_core::DrawElements(GLenum const mode, GLsizei const count, GLenum const type, const GLvoid * const indices) -> void
{
	eeglDrawElement(mode, count, type, indices);
}





//auto
//eegl_context_es_2_0_core::Flush(void) -> void
//{
//}
//auto
//eegl_context_es_2_0_core::Finish(void) -> void
//{
//}






































auto
eegl_context_es_2_0_extras::GetBoolean(GLenum pname) -> GLboolean
{
	return	eeglGetBoolean(pname);
}
auto
eegl_context_es_2_0_extras::GetFloat(GLenum pname) -> GLfloat
{
	return	eeglGetFloat(pname);
}
auto
eegl_context_es_2_0_extras::GetInteger(GLenum pname) -> GLint
{
	return	eeglGetInteger(pname);
}

auto
eegl_context_es_2_0_extras::GenBuffer() -> eegl_buffer_proxy
{
	return	eeglGenBuffer();
}
auto
eegl_context_es_2_0_extras::DeleteBuffer(eegl_buffer_proxy const o) -> void
{
	eeglDeleteBuffer(o);
}

auto
eegl_context_es_2_0_extras::GenTexture() -> eegl_texture_proxy
{
	return	eeglGenTexture();
}
auto
eegl_context_es_2_0_extras::DeleteTexture(eegl_texture_proxy const o) -> void
{
	eeglDeleteTexture(o);
}

















EONIL_MEDIA_ENGINE_GRAPHICS_STUB2_NAMESPACE_END
