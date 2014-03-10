//
//  Platform.h
//  Application
//
//  Created by Hoon H. on 3/11/14.
//
//

#ifndef __Application__Platform__
#define __Application__Platform__


#include <Eonil/Improvisations/MediaEngine/Foundation/Foundation.h>
#include <Eonil/Improvisations/MediaEngine/Graphics/Graphics.h>


#if	EONIL_MEDIA_ENGINE_TARGET_IOS
#if	EE_LANG_OBJC
#include "Apple/iOS/Platform_iOS.h"
#else
#error `Platform` class for iOS requires Objective-C++ compilation context. Include this header file in .mm file.
#endif
#endif


#endif /* defined(__Application__Platform__) */
