//
//  GL-Custom.cpp
//  Graphics
//
//  Created by Hoon H. on 14/5/24.
//
//

#include "GL-Custom.h"
#include "GL-Context.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Stub
	{
		
		
		EEGL_STUB_API_DECO bool
		eeglGetVendorIsATI()
		{
			GLubyte const*	bytes1	=	eeglGetString(GL_VENDOR);
			char const*		bytes2	=	(char const*)bytes1;
			str				s3		=	str(bytes2, 3);				//	The vendor string may contain extra characters. Especially ATI have several variants, and checking only first three characters will be better.
			return	s3 == "ATI";
		}
		


		
		EEGL_STUB_API_DECO GLint const
		eeglGet_ARRAY_BUFFER_BINDING()
		{
			return	eeglGetInteger(GL_ARRAY_BUFFER);
		}
		
		
	}
	
}}}}

