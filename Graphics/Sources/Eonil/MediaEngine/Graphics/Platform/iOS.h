//
//  iOS.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__iOS__
#define __EonilGraphics__iOS__

#if	EONIL_MEDIA_ENGINE_TARGET_IOS

#include "../Common.h"






namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Platforms
	{
		class
		iOS
		{
		public:
			static bool const	hasCurrentGLContext();
			
//			static auto	fullscreenNativeDrawableSurface() -> Utility::NativeDrawableSurface;
		};
	}
	
	
}}}}





#endif

#endif /* defined(__EonilGraphics__iOS__) */
