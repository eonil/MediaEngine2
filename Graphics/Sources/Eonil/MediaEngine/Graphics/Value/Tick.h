//
//  Tick.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/15/13.
//
//

#ifndef __EonilGraphics__Tick__
#define __EonilGraphics__Tick__

#include "../Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Value
	{
		/*!
		 A time unit which is 1/60 second.
		 This is distance from basis 0 point in time-span manner.
		 */
		class
		Tick
		{
		private:
			Int32			number;
		};
	}
	
}}}}

#endif /* defined(__EonilGraphics__Tick__) */
