//
//  Query.cpp
//  Graphics
//
//  Created by Hoon H. on 3/24/14.
//
//

#include "Query.h"
#include "../Stub/GL.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Server
{
	using namespace ____internal_impl_of_opengl_es_2_0_driver____;
	
	
	

	
	
	
	auto Query::
	maximumVertexUniformVectorCount() const -> sz
	{
#if			EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
		auto	float_count	=	Stub::eeglGetInteger(GL_MAX_VERTEX_UNIFORM_COMPONENTS);
		
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(float_count % 4 == 0);
		}
		
//			if (eeglGetVendorIsATI())
//			{
//				/*
//				 ATI/AMD GPU drivers has a bug that reports wrong number.
//				 It must be divided by 4 to get correct number.
//				 */
//				float_count	/=	4;
//			}
		sz	vector4_count	=	float_count / 4;
		return	vector4_count;
#elif		EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
		auto	c1	=	Stub::eeglGetInteger(GL_MAX_VERTEX_UNIFORM_VECTORS);
		return	c1;
#else
#error		EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
#endif
	}
	
	
	
	
	
	
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END
