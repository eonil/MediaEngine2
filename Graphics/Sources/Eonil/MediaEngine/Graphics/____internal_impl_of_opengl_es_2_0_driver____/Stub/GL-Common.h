//
//  GL-Common.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/28/13.
//
//

#pragma once
#include "../common_of____internal_impl_of_opengl_es_2_0_driver____.h"
#define EEGL_STUB_API_DECO

/*!
The issue about Apportable known to been fixed by the developers.
Anyway it is not yet confirmed, so the code is kept by commentizing.
*/
///*!
// Apportable had insane update at 1.0.15 which returns `0` for valid 
// framebuffer/renderbuffer name. This disrupts all assertion system.
// 
// As a workaround, I had to put this flag not to perform related 
// assertions under Apportable environment. Remove these flags and get
// back related assertions if Apportable removes the insane behavior.
// */
//#if		EONIL_MEDIA_ENGINE_TARGET_APPORTABLE
//#define	EEGL_IGNORE_ZERO_FRAMEBUFFER_NAME	1
//#define	EEGL_IGNORE_ZERO_RENDERBUFFER_NAME	1
//#else
//#define	EEGL_IGNORE_ZERO_FRAMEBUFFER_NAME	0
//#define	EEGL_IGNORE_ZERO_RENDERBUFFER_NAME	0
//#endif
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Stub
{
	
	/*
	 These are primitive type conversion (cast) operations.
	 Why do we need this? To be notified on bad(overflow, underflow...)
	 operations.
	 
	 Conversion with numeric range limit assertion.
	 This is provided only for corresponding types for GL types.
	 If you want conversion between unrelated types, then you have
	 to do it yourself.
	 */
	
	
	
	auto	toGLsizei(sz const& v) -> GLsizei;
	auto	fromGLsizei(GLsizei const& v) -> sz;
	
	auto	toGLuint(sz const& v) -> GLuint;
	auto	fromGLuint(GLuint const& v) -> sz;
	
	auto	toGLfloat(Scalar const* v) -> GLfloat const*;
	auto	toGLfloat(Vector4 const* v) -> GLfloat const*;
	auto	toGLfloat(Matrix4 const* v) -> GLfloat const*;
	
	auto	toGLchar(str const& v) -> GLchar const*;
	
	
	
	
	
	
	
	
	
	
	
	
	
	class
	EEGLname
	{
	public:
		EEGLname(EEGLname const&) = default;
		EEGLname(EEGLname&&) = default;
		
		auto operator=(EEGLname const&) -> EEGLname& = default;
		auto operator=(EEGLname&&) -> EEGLname& = default;
		
	public:
		EEGLname(GLuint const value) : _value(value)
		{
		}
		
		operator GLuint() const
		{
			return	_value;
		}
		
	private:
		GLuint	_value	=	{};
	};
	
	struct
	EEGLbuffer : EEGLname
	{
		using	EEGLname::EEGLname;
	};
//		struct
//		EEGLarraybuffer : EEGLbuffer
//		{
//			using	EEGLbuffer::EEGLbuffer;
//		};
//		struct
//		EEGLelementarraybuffer : EEGLbuffer
//		{
//			using	EEGLbuffer::EEGLbuffer;
//		};
	struct
	EEGLtexture : EEGLname
	{
		using	EEGLname::EEGLname;
	};
//		struct
//		EEGLtexture2d : EEGLtexture
//		{
//			using	EEGLtexture::EEGLtexture;
//		};
	
	struct
	EEGLshader : EEGLname
	{
		using	EEGLname::EEGLname;
	};
	struct
	EEGLprogram : EEGLname
	{
		using	EEGLname::EEGLname;
	};
	
	struct
	EEGLrenderbuffer : EEGLname
	{
		using	EEGLname::EEGLname;
	};
	struct
	EEGLframebuffer : EEGLname
	{
		using	EEGLname::EEGLname;
	};
	
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END

