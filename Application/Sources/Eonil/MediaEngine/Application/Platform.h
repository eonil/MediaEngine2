//
//  Platform.h
//  Application
//
//  Created by Hoon H. on 3/11/14.
//
//

#ifndef __Application__Platform__
#define __Application__Platform__



#include <Eonil/MediaEngine/Foundation.h>
#include <Eonil/MediaEngine/Graphics.h>



#if	EONIL_MEDIA_ENGINE_TARGET_IOS
#	if	EE_LANG_OBJC
#		include "Apple/iOS/Platform_iOS.h"
#	else
#		error `Platform` class for iOS requires Objective-C++ compilation context. Include this header file in .mm file.
#	endif
#endif

#if	EONIL_MEDIA_ENGINE_TARGET_OSX
#	if	EE_LANG_OBJC
#		include "Apple/OSX/Platform_OSX.h"
#	else
#		error `Platform` class for OS X requires Objective-C++ compilation context. Include this header file in .mm file.
#	endif
#endif



#endif /* defined(__Application__Platform__) */
