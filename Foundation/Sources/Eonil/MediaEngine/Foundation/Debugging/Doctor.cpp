//
//  Doctor.cpp
//  Foundation
//
//  Created by Hoon H. on 2/5/14.
//
//

#include "Doctor.h"

#include <cstdlib>
#include <unistd.h>
#include <iostream>

#include "../Platform/Targets.h"
EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_BEGIN


namespace
Debugging
{
	
	
	void
	limitMaximumStackSize(const size_t size)
	{
#if	EONIL_MEDIA_ENGINE_TARGET_APPORTABLE
		exceptWithReason("This feature is not supported in Apportable platform.");
#else
		long	sslim	=	size;
		struct rlimit	rlim;
		rlim.rlim_cur	=	sslim;
		rlim.rlim_max	=	sslim;
		setrlimit(RLIMIT_STACK, &rlim);
#endif
	}
	
	
//	void
//	assertWithReason(const bool condition, const std::string reason, const std::string domain)
//	{
//		if (isDebugMode() and not condition)
//		{
//			exceptWithReason(reason == "" ? "(no reason specified, see stack trace for more informations)" : reason, domain);
//		}
//	}
//	
//	void
//	exceptWithReason(const std::string reason, const std::string category, const std::string domain)
//	{
//		std::string		reason1		=	reason == "" ? "(unknown reason)" : reason;
//		std::string		domain1		=	domain == "" ? "(unknown domain)" :domain;
//		std::string		category1	=	category == "" ? "(\?\?\?\?)" : category;
//		std::string		str1		=	"(" + category1 + ") " + reason1;
//					
//		logMessage(str1, domain1, true);
//
//#if EONIL_MEDIA_ENGINE_TARGET_APPORTABLE
//		//!	@todo	Remove C `abort` and throw C++ exception as Apportable supports C++ exception backtrace.
//		logMessage("Currently exception is routed to C `abort()` function. Change this to C++ exception.", "EonilFoundation", true);
//		abort();
////			panic(reason);
//#else
//
//		panic(reason);
//#endif
//	}
//	
//	
//	
//	
//	
//	
//	
//	void
//	logMessage(const std::string message)
//	{
//		std::string	str1	=	message + "\n";
//#if EONIL_MEDIA_ENGINE_TARGET_APPORTABLE
//		__android_log_print(ANDROID_LOG_DEBUG, "APPORTABLE", "%s", str1.c_str());
////				define printf(...) __android_log_print(ANDROID_LOG_DEBUG, "TAG", __VA_ARGS__);
//#else
//		std::cout <<	str1;
//		std::cout.flush();
//#endif
//	}
	
	
	
	
	
	
}



EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_END