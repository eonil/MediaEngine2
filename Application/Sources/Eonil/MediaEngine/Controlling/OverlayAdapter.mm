//
//  OverlayAdapter.cpp
//  TheMagnetismGame
//
//  Created by Hoon H. on 4/16/14.
//  Copyright (c) 2014 Eonil Company. All rights reserved.
//

#include "OverlayAdapter.h"
#include "DraggingGesture.h"


namespace
{
	
}

#define CURRENT_PLATFORM_IS_OK		0



#if	EONIL_MEDIA_ENGINE_TARGET_IOS
//#include <Eonil/Improvisations/MediaEngine/Application/Platform.h>
#include "../Application/Platform.h"
#import "iOS/____Eonil_MediaEngine_Controlling_UserGestureCapturingView_iOS.h"
namespace
{
	static inline auto
	init(Eonil::Improvisations::MediaEngine::Controlling::TouchGestureCapturing& touchCapturing) -> void
	{
		auto*	con1	=	[[____Eonil_MediaEngine_Controlling_UserGestureCapturingView_iOS alloc] init];
		con1.touchCpaturing						=	&touchCapturing;
		Eonil::Improvisations::MediaEngine::Application::Platform::current().setOverlayView(con1);
	}
	static inline auto
	term() -> void
	{
		Eonil::Improvisations::MediaEngine::Application::Platform::current().unsetOverlayView();
	}
}
#undef	CURRENT_PLATFORM_IS_OK
#define	CURRENT_PLATFORM_IS_OK		1
#endif



#if	EONIL_MEDIA_ENGINE_TARGET_OSX
//#include <Eonil/Improvisations/MediaEngine/Application/Platform.h>
#include "../Application/Platform.h"
#import "OSX/____Eonil_MediaEngine_Controlling_UserGestureCapturingView_OSX.h"
namespace
{
	static inline auto
	init(TouchGestureCapturing& touchCapturing) -> void
	{
		auto*	con1	=	[[____Eonil_MediaEngine_Controlling_UserGestureCapturingView_OSX alloc] init];
		con1.touchCpaturing						=	&touchCapturing;
		Eonil::Improvisations::MediaEngine::Application::Platform::current().setOverlayView(con1);
	}
	static inline auto
	term() -> void
	{
		Eonil::Improvisations::MediaEngine::Application::Platform::current().unsetOverlayView();
	}
}
#undef	CURRENT_PLATFORM_IS_OK
#define	CURRENT_PLATFORM_IS_OK		1
#endif



#if not CURRENT_PLATFORM_IS_OK
@interface	AAOverlayController : NSObject
@end
@implementation AAOverlayController
@end
#endif






















EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_BEGIN

	

struct
OverlayAdapter::Core
{
	TouchGestureCapturing		_touch_gest_capt	{};
	DraggingGesture				_dragging			{};
};



OverlayAdapter::OverlayAdapter() : _core(new Core())
{
	init(_core->_touch_gest_capt);
}
OverlayAdapter::~OverlayAdapter()
{
	term();
}


auto
OverlayAdapter::dragging() const -> DraggingGesture const&
{
	return	_core->_dragging;
}
auto
OverlayAdapter::step(const Eonil::Improvisations::MediaEngine::Application::Stepping &s) -> void
{
	_core->_touch_gest_capt.step(0);
	
	////

	if (_core->_dragging.phase() == DraggingGesture::PHASE::BEGIN)
	{
		_core->_dragging.setContinue(_core->_dragging.origination());
	}
	if (_core->_dragging.phase() == DraggingGesture::PHASE::END or _core->_dragging.phase() == DraggingGesture::PHASE::CANCEL)
	{
		_core->_dragging.setNone();
	}
	
	////
	
	for (auto const& t: _core->_touch_gest_capt.touches())
	{
		EONIL_DEBUG_ASSERT(t.code != Touch::CODE::NONE);
		switch (t.code)
		{
			case
			Touch::CODE::NONE:
			{
				break;
			}
			case
			Touch::CODE::BEGIN:
			{
				EONIL_DEBUG_ASSERT(_core->_dragging.phase() == DraggingGesture::PHASE::NONE or _core->_dragging.phase() == DraggingGesture::PHASE::END or _core->_dragging.phase() == DraggingGesture::PHASE::CANCEL);
				_core->_dragging.setBegin(t.coordinate);
				break;
			}
			case
			Touch::CODE::CONTINUE:
			{
				EONIL_DEBUG_ASSERT(_core->_dragging.phase() == DraggingGesture::PHASE::BEGIN or _core->_dragging.phase() == DraggingGesture::PHASE::CONTINUE);
				_core->_dragging.setContinue(t.coordinate);
				break;
			}
			case
			Touch::CODE::END:
			{
				EONIL_DEBUG_ASSERT(_core->_dragging.phase() == DraggingGesture::PHASE::BEGIN or _core->_dragging.phase() == DraggingGesture::PHASE::CONTINUE);
				_core->_dragging.setEnd(t.coordinate);
				break;
			}
			case
			Touch::CODE::CANCEL:
			{
				EONIL_DEBUG_ASSERT(_core->_dragging.phase() == DraggingGesture::PHASE::CONTINUE);
				_core->_dragging.setCancel();
				break;
			}
		}
	}
}







EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_END
