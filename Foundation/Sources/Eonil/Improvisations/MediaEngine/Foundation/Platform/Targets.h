//
//  Targets.h
//  Foundation
//
//  Created by Hoon H. on 2/5/14.
//
//

#ifndef __Foundation__Targets__
#define __Foundation__Targets__







/*!
 `EONIL_MEDIA_ENGINE_TARGET_MINIMUM` means a virtual platform which support least common set.
 This is default implementation which is compatible to all supported platforms.
 Platform-specific optimization can be archived with another `EONIL_MEDIA_ENGINE_TARGET_...` 
 macros.
 */

#define EONIL_MEDIA_ENGINE_TARGET_MINIMUM				(1)

#define EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0			(0)
#define EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2			(0)

//#define EONIL_MEDIA_ENGINE_TARGET_POSIX				(0)
#define EONIL_MEDIA_ENGINE_TARGET_OSX					(0)
#define EONIL_MEDIA_ENGINE_TARGET_IOS					(0)
#define EONIL_MEDIA_ENGINE_TARGET_IOS_DEVICE			(0)
#define EONIL_MEDIA_ENGINE_TARGET_IOS_SIMULATOR			(0)
//#define EONIL_MEDIA_ENGINE_TARGET_WINDOWS				(0)
//#define EONIL_MEDIA_ENGINE_TARGET_WINDOWS_WIN32		(0)
//#define EONIL_MEDIA_ENGINE_TARGET_WINDOWS_WIN64		(0)
#define EONIL_MEDIA_ENGINE_TARGET_LINUX					(0)
#define EONIL_MEDIA_ENGINE_TARGET_ANDROID				(0)
//#define EONIL_MEDIA_ENGINE_TARGET_LINUX_UBUNTU		(0)

#define EONIL_MEDIA_ENGINE_TARGET_APPORTABLE			(0)



#ifdef _WIN64
	//define something for Windows (64-bit)
	#error	Unsupported platform. (maybe yet)
#elif _WIN32
	//define something for Windows (32-bit)
	#error	Unsupported platform.
#elif __APPLE__
	#include "TargetConditionals.h"
	#if TARGET_OS_IPHONE
		// iOS device
		#undef	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
		#define	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0			1
		#undef	EONIL_MEDIA_ENGINE_TARGET_IOS
		#define	EONIL_MEDIA_ENGINE_TARGET_IOS					1
		#undef	EONIL_MEDIA_ENGINE_TARGET_IOS_DEVICE
		#define	EONIL_MEDIA_ENGINE_TARGET_IOS_DEVICE			1
	#elif TARGET_IPHONE_SIMULATOR
		// iOS Simulator
		#undef	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
		#define	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0			1
		#undef	EONIL_MEDIA_ENGINE_TARGET_IOS
		#define	EONIL_MEDIA_ENGINE_TARGET_IOS					1
		#undef	EONIL_MEDIA_ENGINE_TARGET_IOS_SIMULATOR
		#define	EONIL_MEDIA_ENGINE_TARGET_IOS_SIMULATOR			1
	#elif TARGET_OS_MAC
		// OS X
		#undef	EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
		#define	EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2			1
		#undef	EONIL_MEDIA_ENGINE_TARGET_OSX
		#define	EONIL_MEDIA_ENGINE_TARGET_OSX					1
//		#error	Unsupported platform. (yet)
	#else
		// Unknown Apple platform.
		#error	Unsupported platform.
	#endif
#elif __linux
	#undef		EONIL_MEDIA_ENGINE_TARGET_LINUX
	#define		EONIL_MEDIA_ENGINE_TARGET_LINUX					1
	// linux
	#if	ANDROID
		//	Android
		#undef	EONIL_MEDIA_ENGINE_TARGET_ANDROID
		#define	EONIL_MEDIA_ENGINE_TARGET_ANDROID				1
	#else
		//	Any other linux.
		#error	Unsupported platform.
	#endif
#elif __unix // All unices not caught above
	 // Unix
	#error	Unsupported platform.
#elif __posix
	// POSIX
	#error	Unsupported platform.
#endif




#if	APPORTABLE
	#undef		EONIL_MEDIA_ENGINE_TARGET_IOS
	#define		EONIL_MEDIA_ENGINE_TARGET_IOS					1

	#undef		EONIL_MEDIA_ENGINE_TARGET_IOS_DEVICE			
	#define		EONIL_MEDIA_ENGINE_TARGET_IOS_DEVICE			1

	#undef		EONIL_MEDIA_ENGINE_TARGET_ANDROID
	#define		EONIL_MEDIA_ENGINE_TARGET_ANDROID				0
	#undef		EONIL_MEDIA_ENGINE_TARGET_APPORTABLE
	#define		EONIL_MEDIA_ENGINE_TARGET_APPORTABLE			1

	#undef		EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
	#define		EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0			1

	#undef		UINT8_MAX
	#define		UINT8_MAX										(255U)

#endif























#pragma mark	-	Langauge Detection

#ifdef		__cplusplus
#define 	EE_LANG_CPP			1
#else
#define 	EE_LANG_CPP			0
#endif

#ifdef		__OBJC__
#define 	EE_LANG_OBJC		1
#else
#define 	EE_LANG_OBJC		0
#endif









#endif /* defined(__Foundation__Targets__) */
