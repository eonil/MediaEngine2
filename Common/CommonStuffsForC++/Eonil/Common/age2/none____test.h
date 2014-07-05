//
//  none____test.h
//  CommonUtility
//
//  Created by Hoon H. on 2014/06/28.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#pragma once
#include "none.h"
#include "____test.h"
EONIL_COMMONUTILITY_AGE2_NAMESPACE_BEGIN











namespace
none_test
{
	using namespace	test;
	
	inline auto
	run() -> void
	{
		struct
		AAA
		{
			auto
			operator==(none const&) const -> bool
			{
				return	true;
			}
			auto
			operator!=(none const&) const -> bool
			{
				return	false;
			}
		};
		
		{
			
			expect_true(AAA() == NONE);
		}
	}
}










EONIL_COMMONUTILITY_AGE2_NAMESPACE_END
