//
//  GL-Get-Buffer.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "GL-Get-Buffer.h"


namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Stub
	{
		EEGL_INLINE GLint const
		eeglGet_ARRAY_BUFFER_BINDING()
		{
			return	eeglGetInteger(GL_ARRAY_BUFFER);
		}
	}

}}}}