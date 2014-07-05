//
//  ____test_all.h
//  CommonUtility
//
//  Created by Hoon H. on 2014/06/28.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#pragma once
#include "none____test.h"
#include "opt____test.h"
EONIL_COMMONUTILITY_AGE2_NAMESPACE_BEGIN









namespace
test_all
{
	inline auto
	run() -> void
	{
		none_test::run();
		opt_test::run();
	}
}














EONIL_COMMONUTILITY_AGE2_NAMESPACE_END