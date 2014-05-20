//
//  DebugOnlyValidityFlagSlot.h
//  Graphics
//
//  Created by Hoon H. on 3/26/14.
//
//

#ifndef __Graphics__DebugOnlyValidityFlagSlot__
#define __Graphics__DebugOnlyValidityFlagSlot__

#include "../Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Debugging
	{
		
		
		
		class
		DebugOnlyValidityFlagSlotV1
		{
#if	EONIL_MEDIA_ENGINE_DEBUG_MODE
			bool	f	{false};
#endif
			
		public:
			auto
			should_be_on_now() const -> void
			{
				EONIL_DEBUG_ASSERT(f == true);
			}
			auto
			should_be_off_now() const -> void
			{
				EONIL_DEBUG_ASSERT(f == false);
			}
			auto
			set_on() -> void
			{
				EONIL_DEBUG_ASSERT(f == false);
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN
				({
					f	=	true;
				});
			}
			auto
			set_off() -> void
			{
				EONIL_DEBUG_ASSERT(f == true);
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN
				({
					f	=	false;
				});
			}
		};
		

	}
	
}}}}

#endif /* defined(__Graphics__DebugOnlyValidityFlagSlot__) */
