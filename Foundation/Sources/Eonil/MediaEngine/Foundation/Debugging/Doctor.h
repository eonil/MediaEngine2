//
//  Doctor.h
//  Foundation
//
//  Created by Hoon H. on 2/5/14.
//
//

#pragma once
#include "../Prelude.h"
EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_BEGIN
namespace
Debugging
{
//	/*!
//	 @discussion			You must use this method to log.
//	 @note					On Apportable platform, C++ stream output doesn't work, and this is the only way to log properly.
//	 */
//	void	logMessage(std::string const message);
//	
//	void	exceptWithReason(std::string const reason, std::string const category = "EXCEPTION", std::string const domain = "EonilFoundation") __attribute__((noreturn));
//	
//	void	assertWithReason(bool const condition, std::string const reason = "", std::string const domain = "EonilFoundation");
	
	/*!
	 @discussion			Limit stack size for easier debugging at stack-overflow case.
	 @param	size			1024 * 1024 is recommended.
	 */
	void	limitMaximumStackSize(size_t const size);
}
EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_END