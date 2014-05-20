//
//  ____Eonil_MediaEngine_Controlling_UserGestureCapturingView_OSX.h
//  TheMagnetismGame
//
//  Created by Hoon H. on 4/16/14.
//  Copyright (c) 2014 Eonil Company. All rights reserved.
//

#pragma once

#include <Eonil/MediaEngine/Foundation.h>
#if		EONIL_MEDIA_ENGINE_TARGET_OSX
#if		! EE_LANG_OBJC
#error	"This header must be imported only in an Objective-C++ program."
#endif

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

#if	__cplusplus
#include "Common.h"
#include "../TouchGestureCapturing.h"
using namespace	Eonil::Improvisations::MediaEngine::Controlling;
#else
typedef	struct	TouchGestureCapturing	TouchGestureCapturing;
#endif

@interface	____Eonil_MediaEngine_Controlling_UserGestureCapturingView_OSX : NSView
@property	(readwrite,nonatomic,assign)	TouchGestureCapturing*	touchCpaturing;
@end

#endif	//	EONIL_MEDIA_ENGINE_TARGET_OSX