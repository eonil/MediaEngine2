//
//  Doctor.h
//  Foundation
//
//  Created by Hoon H. on 2/5/14.
//
//

#ifndef __Foundation__Doctor__
#define __Foundation__Doctor__

#include "../Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Foundation {

	namespace
	Debugging
	{
		class
		Doctor
		{
		public:
			constexpr static inline auto
			isDebugMode() -> bool
			{
#if		EONIL_MEDIA_ENGINE_DEBUG_MODE
				return	true;
#else
				return	false;
#endif
			}
			constexpr static inline auto
			useLogging() -> bool
			{
				return	isDebugMode();
			}
			
			/*!
			 @discussion			You must use this method to log.
			 @note					On Apportable platform, C++ stream output doesn't work, and this is the only way to log properly.
			 */
			static void				logMessage(std::string const message, std::string const domain = "EonilFoundation", bool const forceToLogAlwaysRegardlessOfUseLoggingFlag = false);
			static void				exceptWithReason(std::string const reason, std::string const category = "EXCEPTION", std::string const domain = "EonilFoundation") __attribute__((noreturn));
			
			static void				assertWithReason(bool const condition, std::string const reason = "", std::string const domain = "EonilFoundation");
			
			/*!
			 @discussion			Limit stack size for easier debugging at stack-overflow case.
			 @param	size			1024 * 1024 is recommended.
			 */
			static void				limitMaximumStackSize(size_t const size);							
		};
	}

}}}}

#endif /* defined(__Foundation__Doctor__) */
