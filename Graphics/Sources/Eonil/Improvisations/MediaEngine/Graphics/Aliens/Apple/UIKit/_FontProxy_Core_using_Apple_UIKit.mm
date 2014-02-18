//
//  _FontProxy_Core_using_Apple_UIKit.cpp
//  Graphics
//
//  Created by Hoon H. on 2/17/14.
//
//

#include "_FontProxy_Core_using_Apple_UIKit.h"

#if EONIL_MEDIA_ENGINE_TARGET_IOS








#include "../../FontProxy.h"

#include	<CoreFoundation/CoreFoundation.h>
#include	<CoreGraphics/CoreGraphics.h>
#import		<UIKit/UIKit.h>

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Aliens
	{
		
		
		FontProxy::FontProxy(Core* core) : _cptr(core)
		{
		}
		
		FontProxy::FontProxy(FontProxy&& o)
		{
			std::swap(o._cptr, _cptr);
		}
		FontProxy::~FontProxy()
		{
		}
		
		
		
		
		auto
		FontProxy::measure(const str &text, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector2 &constraintSize) const -> Vector2
		{
			NSString*	text2	=	[NSString stringWithUTF8String:text.c_str()];
			UIFont*		font2	=	_cptr->rawPointer();
			CGSize		consz2	=	CGSizeMake(constraintSize.x, constraintSize.y);
			
			////
			
			NSCAssert([text2 isKindOfClass:[NSString class]], @"");
			NSCAssert([font2 isKindOfClass:[UIFont class]], @"");
			NSCAssert(not isnan(consz2.width) && consz2.width >= 0.0f, @"");
			NSCAssert(not isnan(consz2.height) && consz2.height >= 0.0f, @"");
			
			NSArray*	lines	=	[text2 componentsSeparatedByString: @"\n"];
			CGSize		dim		=	CGSizeZero;
			
			for (NSString *s in lines)
			{
				CGSize tmp	=	[s sizeWithFont:font2 constrainedToSize:consz2];
				if (tmp.width	>	dim.width)
				{
					dim.width	=	tmp.width;
				}
				dim.height	+=	tmp.height;
			}
			
			////
			
			return	Vector2{dim.width, dim.height};
		}
		
		
		auto
		FontProxy::systemDefaultFont(const float &size) -> FontProxy
		{
			return	systemDefaultFont(size, false);
		}
		auto
		FontProxy::systemDefaultFont(const float &size, bool bold) -> FontProxy
		{
			CGFloat	s2	=	size;
			UIFont*	f	=	bold ? [UIFont boldSystemFontOfSize:s2] : [UIFont systemFontOfSize:s2];
			
			Core*	c	=	new Core(f);

			return	FontProxy{c};
		}
		
		
	}
	
}}}}









#endif // EONIL_MEDIA_ENGINE_TARGET_IOS