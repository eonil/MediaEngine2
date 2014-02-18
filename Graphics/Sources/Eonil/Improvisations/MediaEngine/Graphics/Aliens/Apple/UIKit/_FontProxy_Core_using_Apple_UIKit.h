//
//  _FontProxy_Core_using_Apple_UIKit.h
//  Graphics
//
//  Created by Hoon H. on 2/17/14.
//
//

#ifndef __Graphics___FontProxy_Core_using_Apple_UIKit__
#define __Graphics___FontProxy_Core_using_Apple_UIKit__

#if EONIL_MEDIA_ENGINE_TARGET_IOS








#include "../../FontProxy.h"

#include	<CoreFoundation/CoreFoundation.h>
#include	<CoreGraphics/CoreGraphics.h>
#import		<UIKit/UIKit.h>

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Aliens
	{
		
		
		
		/*!
		 Core is implemented using UIKit UIFont class in iOS.
		 */
		class
		FontProxy::Core
		{
			__strong UIFont*	_font{nil};
			
		public:
			Core(UIFont* font) : _font(font)
			{
			}
			Core(str const& name, float size)
			{
				NSString*	n2	=	[NSString stringWithUTF8String:name.c_str()];
				CGFloat		s2	=	size;
			
				/*!
				 @todo
				 I am not sure the *font size* is in pixels. Check and fix if it's wrong.
				 */
				
				_font	=	[UIFont fontWithName:n2 size:s2];
			}
			~Core()
			{
				_font	=	nil;
			}
			
			auto
			rawPointer() -> UIFont*
			{
				return	_font;
			}
		};
		
		
		
		
		
		
	}
	
}}}}









#endif // EONIL_MEDIA_ENGINE_TARGET_IOS

#endif /* defined(__Graphics___FontProxy_Core_using_Apple_UIKit__) */
