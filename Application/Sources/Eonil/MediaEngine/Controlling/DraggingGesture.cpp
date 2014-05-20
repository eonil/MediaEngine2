//
//  DraggingGesture.cpp
//  TheMagnetismGame
//
//  Created by Hoon H. on 4/17/14.
//  Copyright (c) 2014 Eonil Company. All rights reserved.
//

#include "DraggingGesture.h"
EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_BEGIN





auto
DraggingGesture::phase() const -> PHASE const&
{
	return	_phase;
}
auto
DraggingGesture::origination() const -> Vector2 const&
{
	EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT(_phase != PHASE::NONE);
	
	return	_orig_pos;
}
auto
DraggingGesture::destination() const -> Vector2 const&
{
	EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT(_phase != PHASE::NONE);
	
	return	_dest_pos;
}

auto
DraggingGesture::
setBegin(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector2 &coordinate) -> void
{
	EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT(_phase == PHASE::NONE or _phase == PHASE::END or _phase == PHASE::CANCEL);
	
	_phase		=	PHASE::BEGIN;
	_orig_pos	=	coordinate;
	_dest_pos	=	coordinate;
}

auto
DraggingGesture::
setContinue(Vector2 const& coordinate) -> void
{
	EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT(_phase != PHASE::NONE);
	EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT(_phase != PHASE::END);
	
	_phase		=	PHASE::CONTINUE;
	_dest_pos	=	coordinate;
}
auto
DraggingGesture::
setEnd(Vector2 const& coordinate) -> void
{
	EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT(_phase != PHASE::NONE);
	EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT(_phase != PHASE::END);
	
	_phase		=	PHASE::END;
	_dest_pos	=	coordinate;
}
auto
DraggingGesture::
setCancel() -> void
{
	EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT(_phase != PHASE::NONE);
	EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT(_phase != PHASE::END);
	
	_phase		=	PHASE::CANCEL;
}
auto
DraggingGesture::
setNone() -> void
{
	EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT(_phase == PHASE::END or _phase == PHASE::CANCEL);
	EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT(_phase != PHASE::NONE);
	EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT(_phase != PHASE::BEGIN);
	EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT(_phase != PHASE::CONTINUE);
	
	_phase		=	PHASE::NONE;
}











EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_END