//
//  Platform_OSX.cpp
//  Application
//
//  Created by Hoon H. on 4/16/14.
//
//

#include "Platform_OSX.h"
#import "____EonilImprovisationsMediaEngineMainWindowController.h"

#if	EONIL_MEDIA_ENGINE_TARGET_OSX

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Application {
	
	
	
	
	namespace
	{
		__strong static	____EonilImprovisationsMediaEngineMainWindowController*		_main_win_con		=	nil;
		
		static Platform*			_p			{nullptr};
	}
	
	
	
	
	auto Platform::
	_init(id mainWindowController) -> void
	{
		NSCAssert([mainWindowController isKindOfClass:[____EonilImprovisationsMediaEngineMainWindowController class]], @"The parameter `mainWindowController` must be an instance of `____EonilImprovisationsMediaEngineMainWindowController` class.");

		_main_win_con	=	mainWindowController;
		_p				=	new Platform();
	}
	auto Platform::
	_term() -> void
	{
		delete	_p;
		_p				=	nullptr;
		
		_main_win_con	=	nil;
	}
	
	
	
	
	
	auto Platform::
	setOverlayView(NSView* view) -> void
	{
		EONIL_DEBUG_ASSERT_WITH_MESSAGE([_main_win_con overlayView] == nil, "Cannot set because there's already an overlay-view currently set. Unset it first.");
		EONIL_DEBUG_ASSERT_WITH_MESSAGE(view != nil, "The `view` non-`nil` value.");
		EONIL_DEBUG_ASSERT_WITH_MESSAGE([view isKindOfClass:[NSView class]], "The `view` must be an `NSView` instance.");
		
		[_main_win_con setOverlayView:view];
	}
	auto Platform::
	unsetOverlayView() -> void
	{
		EONIL_DEBUG_ASSERT_WITH_MESSAGE([_main_win_con overlayView] != nil, "Cannot unset because there's no overlay-view currently set.");
		
		[_main_win_con setOverlayView:nil];
	}
	
	
	
	
	auto Platform::
	current() -> Platform&
	{
		EONIL_DEBUG_ASSERT_WITH_MESSAGE(_p != nullptr, "The platform object is not available now. Call this method only when the application system is up.");
		return	*_p;
	}
	
	
	
	
	
	
}}}}

#endif	//	EONIL_MEDIA_ENGINE_TARGET_OSX
