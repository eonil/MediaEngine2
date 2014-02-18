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
		toGL(Size const& v) -> GLsizei
		{
			EONIL_DEBUG_ASSERT(v <= std::numeric_limits<GLsizei>::max());
			return	GLsizei(v);
		}
		auto
		fromGL(GLsizei const& v) -> Size
		{
			EONIL_DEBUG_ASSERT(v <= std::numeric_limits<Size>::max());
			return	Size(v);
		}
		
		
		
		
		
	}
	
}}}}



