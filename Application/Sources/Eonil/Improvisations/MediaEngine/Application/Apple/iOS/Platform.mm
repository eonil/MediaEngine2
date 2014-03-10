//
//  Platform.cpp
//  Application
//
//  Created by Hoon H. on 3/11/14.
//
//

#include "Platform.h"

#if	EONIL_MEDIA_ENGINE_TARGET_IOS

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Application {
	
	
	
	
	namespace
	{
		__strong static UIViewController*	_mvc	=	NULL;
		__strong static UIView*				_ov		=	NULL;
		
		static Platform*					_p			{nullptr};
	}
	
	
	
	
	auto Platform::
	_init(UIViewController *mainViewController) -> void
	{
		_mvc	=	mainViewController;
		
		_p		=	new Platform();
	}
	auto Platform::
	_term() -> void
	{
		delete	_p;
		_p		=	nullptr;
		
		_mvc	=	NULL;
		_ov		=	NULL;
	}
	
	
	
	
	
	auto Platform::
	setOverlayView(UIView* view) -> void
	{
		EONIL_DEBUG_ASSERT_WITH_MESSAGE(_ov == NULL, "Cannot set because there's already an overlay-view currently set. Unset it first.");
		EONIL_DEBUG_ASSERT_WITH_MESSAGE(view != NULL, "The `view` non-`NULL` value.");
		EONIL_DEBUG_ASSERT_WITH_MESSAGE([view isKindOfClass:[UIView class]], "The `view` must be an `UIView` instance.");
		
		[view setFrame:_mvc.view.bounds];
		[_mvc.view addSubview:view];
		
		_ov	=	view;
	}
	auto Platform::
	unsetOverlayView() -> void
	{
		EONIL_DEBUG_ASSERT_WITH_MESSAGE(_ov != NULL, "Cannot unset because there's no overlay-view currently set.");
		
		[_ov removeFromSuperview];
		
		_ov	=	NULL;
	}
	
	
	
	
	auto Platform::
	current() -> Platform&
	{
		EONIL_DEBUG_ASSERT_WITH_MESSAGE(_p != nullptr, "The platform object is not available now. Call this method only when the application system is up.");
		return	*_p;
	}
	
	
	
	
	
	
}}}}

#endif	//	EONIL_MEDIA_ENGINE_TARGET_IOS
