//
//  GL-Common.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/28/13.
//
//

#include "GL-Common.h"

#include <limits>

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Stub
	{
		
		/*
		 These are primitive type conversion (cast) operations.
		 Why do we need this? To be notified on bad(overflow, underflow...)
		 operations.
		 */
		auto
		toGLsizei(Size const& v) -> GLsizei
		{
			EONIL_DEBUG_ASSERT(v <= std::numeric_limits<GLsizei>::max());
			return	GLsizei(v);
		}
		auto
		fromGLsizei(GLsizei const& v) -> Size
		{
			EONIL_DEBUG_ASSERT(v <= std::numeric_limits<Size>::max());
			return	Size(v);
		}
		
		
		
		
		auto
		toGLint(Size const& v) -> GLint
		{
			EONIL_DEBUG_ASSERT(v <= std::numeric_limits<GLint>::max());
			return	GLint(v);
		}
		auto
		fromGLint(GLint const& v) -> Size
		{
			EONIL_DEBUG_ASSERT(v <= std::numeric_limits<Size>::max());
			return	Size(v);
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
	
}}}}



