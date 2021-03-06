//
//  Platform_OSX.h
//  Application
//
//  Created by Hoon H. on 4/16/14.
//
//

#pragma once

#include "../../Stepping.h"
#include "../../run.h"

#if	EONIL_MEDIA_ENGINE_TARGET_OSX

#if		! EE_LANG_OBJC
#error	"This header must be imported only in an Objective-C++ program."
#endif

EONIL_MEDIA_ENGINE_APPLICATION_NAMESPACE_BEGIN







/*!
 This is an interface for OSX specific features.
 
 @classdesign
 Interface is designed to be declarative to avoid any accidental behavior breaking.
 
 @note
 The singleton instance is currently being initialized in `____EonilImprovisationsMediaEngineMainWindowController` class.
 */
class
Platform
{
	friend auto	run(int argc, char const *argv[], PROC const& prepare, PROC const& cleanup, STEP const& step) -> int;
	
	static auto	_init(id mainWindowController) -> void;
	static auto	_term() -> void;
	
public:
	Platform() = default;
	virtual ~Platform() = default;
	
	/*!
	 An overlay view is a plain `NSView` which will be laid over the GL rendering view.
	 Its size will be adjusted to be same with GL rendering view.
	 You can push only one overlay-view.
	 */
	auto	setOverlayView(NSView* view) -> void;
	auto	unsetOverlayView() -> void;
	
//		virtual auto	presentModalViewController(UIViewController* vc) -> void;
//		virtual auto	dismissModalViewController(UIViewController* vc) -> void;
//
//		virtual auto	pushViewController(UIViewController* vc) -> void;
//		virtual auto	popViewController(UIViewController* vc) -> void;
	
	
	/*!
	 Gets the singleton instance of the platform class.
	 This is accessible only while application is running.
	 It's safe to access this object within user-supplied system class.
	 */
	static auto	current() -> Platform&;
};














EONIL_MEDIA_ENGINE_APPLICATION_NAMESPACE_END
#endif // EONIL_MEDIA_ENGINE_TARGET_OSX
