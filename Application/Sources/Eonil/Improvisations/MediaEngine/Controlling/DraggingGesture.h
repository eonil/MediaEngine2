//
//  DraggingGesture.h
//  TheMagnetismGame
//
//  Created by Hoon H. on 4/17/14.
//  Copyright (c) 2014 Eonil Company. All rights reserved.
//

#pragma	once
#include "Common.h"
EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_BEGIN








class
DraggingGesture final
{
	
public:
	enum class
	PHASE : Size
	{
		NONE,
		BEGIN,
		CONTINUE,
		END,
		CANCEL,
	};

	////
	
	DraggingGesture() = default;
	
	auto	phase() const -> PHASE const&;
	auto	origination() const -> Vector2 const&;
	auto	destination() const -> Vector2 const&;
	
	auto	setBegin(Vector2 const& coordinate) -> void;
	auto	setContinue(Vector2 const& coordinate) -> void;
	auto	setEnd(Vector2 const& coordinate) -> void;
	auto	setCancel() -> void;
	auto	setNone() -> void;

private:
	PHASE		_phase		{PHASE::NONE};
	Vector2		_orig_pos	{};
	Vector2		_dest_pos	{};
};










EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_END