//
//  FontProxy.h
//  Graphics
//
//  Created by Hoon H. on 2/17/14.
//
//

#ifndef __Graphics__FontProxy__
#define __Graphics__FontProxy__

#include "Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Aliens
	{
		
		
		
		class
		FontProxy
		{
			struct	Core;
			
			uptr<Core>	_cptr{nullptr};
			
			FontProxy(Core* core);
			
		public:
			FontProxy() = default;
			FontProxy(FontProxy&&);

			FontProxy(str const& name, float const& size);
			~FontProxy();
			
			auto	core() const -> Core const&;
			
			
			
			/*!
			 @param		constraintSize
			 
						If you don't want to put a constraint, use `INFINITE`.
						Any other than positive real number will be rejected by assertion.
			 
			 @note		Copied from Cocos2D-X source code and modified by Hoon H.
			 */
			auto	measure(str const& text, Vector2 const& constraintSize) const -> Vector2;
			
			
			
//			auto	draw(str const& text, Vector2)
			
			
		public:
			static auto	systemDefaultFont(float const& size) -> FontProxy;			
			static auto	systemDefaultFont(float const& size, bool bold) -> FontProxy;
		};
		
		
		
		
		
		
	}
	
}}}}

#endif /* defined(__Graphics__FontProxy__) */
