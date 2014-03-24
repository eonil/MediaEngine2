//
//  Query.cpp
//  Graphics
//
//  Created by Hoon H. on 3/24/14.
//
//

#include "Query.h"

#include "../Stub/GL.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		using namespace Stub;
		
		
		

		
		
		
		auto Query::
		maximumVertexUniformVectorCount() const -> Size
		{
#if			EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
			auto	c1	=	Stub::eeglGetInteger(GL_MAX_VERTEX_UNIFORM_COMPONENTS);
			EONIL_DEBUG_ASSERT(c1 % 4 == 0);
			if (eeglGetVendorIsATI())
			{
				/*
				 ATI/AMD GPU drivers has a bug that reports wrong number.
				 It must be divided by 4 to get correct number.
				 */
				c1	/=	4;
			}
			return	c1 / 4;
#elif		EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
			return	Stub::eeglGetInteger(GL_MAX_VERTEX_UNIFORM_VECTORS);
#else
#error		EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
#endif
		}
		
		
		
		
		
		
	}
	
}}}}