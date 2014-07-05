//
//  GL-Common.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/28/13.
//
//

#include "GL-Common.h"
#include "../____dbg____.h"
#include <limits>

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Stub
{
	
	/*
	 These are primitive type conversion (cast) operations.
	 Why do we need this? To be notified on bad(overflow, underflow...)
	 operations.
	 */
	auto
	toGLsizei(sz const& v) -> GLsizei
	{
		assertForUnsignedNumericRange<sz, GLuint>(v);
//			EONIL_DEBUG_ASSERT(v <= std::numeric_limits<GLsizei>::max());
		return	GLsizei(v);
	}
	auto
	fromGLsizei(GLsizei const& v) -> sz
	{
		assertForUnsignedNumericRange<GLuint, sz>(v);
//			EONIL_DEBUG_ASSERT(v <= std::numeric_limits<Size>::max());
		return	sz(v);
	}
	
	
	
	auto
	toGLuint(sz const& v) -> GLuint
	{
		assertForUnsignedNumericRange<sz, GLuint>(v);
//			EONIL_DEBUG_ASSERT(v <= std::numeric_limits<GLuint>::max());
		return	GLint(v);
	}
	auto
	fromGLuint(GLuint const& v) -> sz
	{
		assertForUnsignedNumericRange<GLuint, sz>(v);
//			EONIL_DEBUG_ASSERT(v <= std::numeric_limits<Size>::max());
		return	sz(v);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	auto
	toGLfloat(Scalar const* v) -> GLfloat const*
	{
		return	(GLfloat const*)v;
	}
	auto
	toGLfloat(Vector4 const* v) -> GLfloat const*
	{
		return	(GLfloat const*)v;
	}
	auto
	toGLfloat(Matrix4 const* v) -> GLfloat const*
	{
		return	(GLfloat const*)v;
	}


	auto
	toGLchar(str const& v) -> GLchar const*
	{
		return	v.c_str();
	}
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END





