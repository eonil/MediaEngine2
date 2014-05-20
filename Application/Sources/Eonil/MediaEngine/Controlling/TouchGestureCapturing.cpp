//
//  TouchGestureCapturing.cpp
//  TheMagnetismGame
//
//  Created by Hoon H. on 4/16/14.
//  Copyright (c) 2014 Eonil Company. All rights reserved.
//

#include "TouchGestureCapturing.h"
EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_BEGIN












struct
TouchGestureCapturing::Core
{
	TouchGestureCapturing::TOUCH_STACK	current	{};
	TouchGestureCapturing::TOUCH_STACK	future	{};
};





TouchGestureCapturing::TouchGestureCapturing() : _core(new Core())
{
}
TouchGestureCapturing::~TouchGestureCapturing()
{
}

auto
TouchGestureCapturing::touches() const -> TOUCH_STACK const&
{
	return	_core->current;
}
auto
TouchGestureCapturing::push(Touch &&touch) -> void
{
	EONIL_DEBUG_ASSERT_WITH_MESSAGE(_core->future.size() < _core->future.capacity(), "Too many touch events are queued. You need to call `step` method at proper location. This error happens only in debug mode, and any further events all will be lost in release mode.");
	
	if (_core->future.size() < _core->future.capacity())
	{
		_core->future.push(std::move(touch));
	}
}
auto
TouchGestureCapturing::step(const Size &tick) -> void
{
	std::swap(_core->current, _core->future);
	_core->future.clear();
}










EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_END