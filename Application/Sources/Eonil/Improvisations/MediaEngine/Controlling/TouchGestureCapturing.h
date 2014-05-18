//
//  TouchGestureCapturing.h
//  TheMagnetismGame
//
//  Created by Hoon H. on 4/16/14.
//  Copyright (c) 2014 Eonil Company. All rights reserved.
//

#pragma once
#include "Common.h"
#include "Touch.h"
EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_BEGIN

	
	
	
	
	







/*!
 Detects user gesture input, and enqueues them.
 
 @discussion
 This analyze and parse the touch gestures, and queue them for later use.
 Client code can query all queued gestures, and can decide what to do with them.
 
 Gesture input can arrive at any time. Anyway to make query result stable, newrly
 arrived events after first query will not be visible until you call `step` method.
 If you want newrly arrived evetns, call `step` method.
 */
class
TouchGestureCapturing final
{
	static Size const	BUFFER_PER_STEP	=	16;
	
	using	TOUCH_STACK	=	StaticStableListStack<Touch, BUFFER_PER_STEP>;
	
	struct	Core;
	uptr<Core>		_core{};
	
public:
	TouchGestureCapturing();
	~TouchGestureCapturing();
	
	auto	touches() const -> TOUCH_STACK const&;
	auto	push(Touch&& touch) -> void;
	auto	step(Size const& tick) -> void;					//!	Purges current touch list, and brings queued touch events.
};












EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_END

