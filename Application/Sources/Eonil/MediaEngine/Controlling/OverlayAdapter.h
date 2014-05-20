//
//  OverlayAdapter.h
//  TheMagnetismGame
//
//  Created by Hoon H. on 4/16/14.
//  Copyright (c) 2014 Eonil Company. All rights reserved.
//

#pragma once
#include "Common.h"
#include "TouchGestureCapturing.h"
EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_BEGIN











class
OverlayAdapter final
{
	struct	Core;
	uptr<Core>	_core{};
	
public:
	OverlayAdapter();
	~OverlayAdapter();

	auto	dragging() const -> DraggingGesture const&;

	auto	step(Application::Stepping const&) -> void;
};









EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_END
