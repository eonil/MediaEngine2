//
//  iOS.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#pragma once
#include "../Common.h"
#if	EONIL_MEDIA_ENGINE_TARGET_IOS
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

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

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END
#endif