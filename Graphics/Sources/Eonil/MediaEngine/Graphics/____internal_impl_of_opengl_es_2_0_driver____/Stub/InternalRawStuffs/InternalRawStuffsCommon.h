//
//  InternalRawStuffsCommon.h
//  Graphics
//
//  Created by Hoon H. on 14/5/24.
//
//


#pragma once
#include "../../common_of____internal_impl_of_opengl_es_2_0_driver____.h"
#define	EEGL_STUB_API_DECO
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
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Stub
{










	
	namespace
	{
		template<typename T>
		static inline auto
		contains_target_in_samples(T const& target, vec<T> const& samples) -> bool
		{
			return	std::find(samples.begin(), samples.end(), target) != samples.end();
		}
	}






}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END

