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
			auto	float_count	=	Stub::eeglGetInteger(GL_MAX_VERTEX_UNIFORM_COMPONENTS);
			EONIL_DEBUG_ASSERT(float_count % 4 == 0);
			if (eeglGetVendorIsATI())
			{
				/*
				 ATI/AMD GPU drivers has a bug that reports wrong number.
				 It must be divided by 4 to get correct number.
				 */
				float_count	/=	4;
			}
			Size	vector4_count	=	float_count / 4;
			return	vector4_count;
#elif		EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
			auto	c1	=	Stub::eeglGetInteger(GL_MAX_VERTEX_UNIFORM_VECTORS);
			return	c1;
#else
#error		EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
#endif
		}
		
		
		
		
		
		
	}
	
}}}}