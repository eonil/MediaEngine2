//
//  GLNumbers.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/20/13.
//
//

#ifndef __EonilGraphics__GLNumbers__
#define __EonilGraphics__GLNumbers__

#include "../../Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Value
	{
		/*!
		 Conversion with numeric range limit assertion.
		 */
		namespace
		Conversion
		{
			GLsizei const	GLsizeiFromSize(Size const size);
			
			GLuint const	GLuintFromSize(Size const size);
			GLint const		GLintFromSize(Size const size);
		}
	}
	
}}}}

#endif /* defined(__EonilGraphics__GLNumbers__) */
