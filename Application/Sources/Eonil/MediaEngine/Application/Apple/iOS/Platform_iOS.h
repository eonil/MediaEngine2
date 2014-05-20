//
//  Platform_iOS.h
//  Application
//
//  Created by Hoon H. on 3/11/14.
//
//

#ifndef __Application__Platform_iOS__
#define __Application__Platform_iOS__

#include "../../Stepping.h"
#include "../../run.h"

#if	EONIL_MEDIA_ENGINE_TARGET_IOS

#if		! EE_LANG_OBJC
#error	"This header must be imported only in an Objective-C++ program."
#endif

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Application {
	
	
	
	
	
	
	
	/*!
	 This is an interface for iOS specific features.
	 
	 @classdesign
	 Interface is designed to be declarative to avoid any accidental behavior breaking.
	 */
	class
	Platform
	{
		friend auto	run(int argc, char const *argv[], PROC const& prepare, PROC const& cleanup, STEP const& step) -> int;
		
		static auto	_init(UIViewController* mainViewController) -> void;
		static auto	_term() -> void;
		
	public:
		Platform() = default;
		virtual ~Platform() = default;
		
		/*!
		 An overlay view is a plain `UIView` which will be laid over the GL rendering view.
		 Its size will be adjusted to be same with GL rendering view.
		 You can push only one overlay-view.
		 */
		auto	setOverlayView(UIView* view) -> void;
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}}}}

#endif	//	EONIL_MEDIA_ENGINE_TARGET_IOS

#endif /* defined(__Application__Platform_iOS__) */
