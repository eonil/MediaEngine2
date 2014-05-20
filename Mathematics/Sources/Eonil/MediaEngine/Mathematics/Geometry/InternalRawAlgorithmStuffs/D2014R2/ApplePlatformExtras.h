//
//  ApplePlatformExtras.h
//  Mathematics
//
//  Created by Hoon H. on 14/5/19.
//
//

/*
 Provides access to Apple platform specific features if available.
 */

#pragma once
#include "../../../Common.h"
#if	(EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
/*
 Do not include whole GLKit which needs Objective-C context.
 */
//#include <GLKit/GLKit.h>	//	This requires Objective-C context.
#include <GLKit/GLKitBase.h>
#include <GLKit/GLKMath.h>
#include <CoreGraphics/CoreGraphics.h>
#define EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_APPLE_PLATFORM_EXTRAS_READY		1
#else
#define EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_APPLE_PLATFORM_EXTRAS_READY		0
#endif


