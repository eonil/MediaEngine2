//
//  DebugOnlyValidityFlagSlot.h
//  Graphics
//
//  Created by Hoon H. on 3/26/14.
//
//

#pragma once
#include "../Common.h"
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

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
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion(f == true);
			}
		}
		auto
		should_be_off_now() const -> void
		{
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion(f == false);
			}
		}
		auto
		set_on() -> void
		{
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion(f == false);
				f	=	true;
			}
		}
		auto
		set_off() -> void
		{
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion(f == true);
				f	=	false;
			}
		}
	};
	

}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END
