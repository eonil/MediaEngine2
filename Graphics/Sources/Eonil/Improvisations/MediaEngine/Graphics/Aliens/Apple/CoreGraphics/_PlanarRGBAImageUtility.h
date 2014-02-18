//
//  _PlanarRGBAImageUtility.h
//  Graphics
//
//  Created by Hoon H. on 2/17/14.
//
//

#ifndef __Graphics___PlanarRGBAImageUtility__
#define __Graphics___PlanarRGBAImageUtility__

#if EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX










#include <cstdlib>
#import <QuartzCore/QuartzCore.h>

#include "../../../Common.h"
#include "../../../Stub/GL.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Aliens
	{
		using namespace	Eonil::Improvisations::MediaEngine::Graphics::Stub;
		
		
		
		
		
		
		
		
		
		
		
		
		auto	isPOT(Size const s) -> bool const;
		
		
		
		
		
		
		struct
		OpacityComponentOptimization
		{
			enum
			CODE
			{
				NONE,
				PREMULTIPLICATION,
			};
		};
		struct
		AlphaComponentPlacement
		{
			enum
			CODE
			{
				FIRST,		//!	Lowest address.
				LAST,		//!	Highest address.
			};
		};
		
		class
		TextureCoreUtil
		{
		public:
			
		};
		
		
		
		
		
		
		auto		RatioInByte(uint8_t const b) -> Scalar const;
		auto		ProcessIntoPremultipliedARGB8888Pixels(Legacy2013SharedMemory const pixels, bool const firstToLast, bool const multiplyAlpha) -> Legacy2013SharedMemory const;
		auto		NeedsAlphaPremultiplication(CGImageRef const image) -> bool const;
		
		
		/*!
		 This produces RGBA (premultiplied) texture image and returns a GL texture name to it.
		 You are responsible to delete the GL texture name.
		 
		 @discussion			RGBA(8888) format is primrily considered because it's GL standard.
		 By default, all rendering pipeline in this engine all uses premultiplied
		 image unless there's special concern. So this will also apply
		 premultiplication.
		 
		 @note					iPhone GPU is not optimal with RGBA texture, and actually it
		 likes ARGB(?, not sure) image.
		 The optimal format is not supported currently, but will be added later.
		 */
		auto		NameByCreatingTextureFromCGImage(CGImageRef const image, bool const flipInY) -> GLuint const;

		
			
		
	}
	
}}}}

#endif // EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX

#endif /* defined(__Graphics___PlanarRGBAImageUtility__) */
