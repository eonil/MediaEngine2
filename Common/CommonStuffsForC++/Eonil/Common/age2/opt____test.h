//
//  opt_test.h
//  EonilScript2
//
//  Created by Hoon H. on 2014/06/17.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#pragma once
#include "opt.h"
#include "____test.h"
EONIL_COMMONUTILITY_AGE2_NAMESPACE_BEGIN











namespace
opt_test
{
	using namespace	test;
	
	inline auto
	run() -> void
	{		
		{
			opt<int>	o1	=	nullptr;
			expect_true(o1.ready() == false);
		}
		{
			opt<int>	o1	=	123;
			expect_true(o1.ready() == true);
			expect_true(o1.value() == 123);
		}
		{
			opt<int>	o1	=	123;
			opt<int>	o2	=	o1;
			expect_true(o2.ready() == true);
			expect_true(o2.value() == 123);
		}
		{
			opt<int>	o1	=	123;
			opt<int>	o2	=	std::move(o1);
			expect_true(o2.ready() == true);
			expect_true(o2.value() == 123);
			expect_true(o1.ready() == false);
		}
		{
			opt<int>	o1	=	123;
			o1	=	std::move(o1);
			expect_true(o1.ready() == true);
		}
		{
			opt<int>	o1	=	nullptr;
			o1	=	std::move(o1);
			expect_true(o1 == nullptr);
			expect_true(o1.ready() == false);
		}
	}
}










EONIL_COMMONUTILITY_AGE2_NAMESPACE_END
