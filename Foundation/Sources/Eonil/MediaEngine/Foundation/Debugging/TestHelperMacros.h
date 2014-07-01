//
//  TestHelperMacros.h
//  CommonUtility
//
//  Created by Hoon H. on 12/21/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#pragma once
#include "../Prelude.h"
EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_BEGIN

namespace
{
	
	static inline void
	____test_assert(bool const cond, char const* const expr, long long line, char const* const file)
	{
		if (not cond)
		{
			err9_legacy_error_always("[TEST ASSERTION FAILURE]\n\nexpr = " + std::string(expr) + "\nline = #" + std::to_string(line) + "\nfile = " + std::string(file) + "\n");
		}
	}
	
}
#define		EONIL_MEDIA_ENGINE_TEST_ASSERT(condexpr)		Eonil::MediaEngine::Foundation::____test_assert((condexpr), #condexpr, __LINE__ , __FILE__ )

EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_END