//
//  GL-Common.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/28/13.
//
//

#ifndef __EonilGraphics__GL_Common__
#define __EonilGraphics__GL_Common__

#define 	EEGL_STUB_API_DECO

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

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
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
		
		
		
		auto	toGLsizei(Size const& v) -> GLsizei;
		auto	fromGLsizei(GLsizei const& v) -> Size;
		
		auto	toGLuint(Size const& v) -> GLuint;
		auto	fromGLuint(GLuint const& v) -> Size;
		
		auto	toGLfloat(Scalar const* v) -> GLfloat const*;
		auto	toGLfloat(Vector4 const* v) -> GLfloat const*;
		auto	toGLfloat(Matrix4 const* v) -> GLfloat const*;
		
		auto	toGLchar(str const& v) -> GLchar const*;
		
		
		
		
		
		
		
		
		
		
		
	}
	
}}}}

#endif /* defined(__EonilGraphics__GL_Common__) */
