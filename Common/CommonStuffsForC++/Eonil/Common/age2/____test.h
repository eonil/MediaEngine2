
//  TestInfrastructures.h
//  EonilScript2
//
//  Created by Hoon H. on 2014/06/17.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#pragma once
#include <functional>
#include <stdexcept>
#include <typeinfo>
#include "common.h"
EONIL_COMMONUTILITY_AGE2_NAMESPACE_BEGIN













namespace
test
{
	class
	failure_exception : public std::logic_error
	{
		using	std::logic_error::logic_error;
	};
	
	////
	
	inline auto
	expect_true(bool condition_expression) -> void
	{
		if (not condition_expression)
		{
			throw	failure_exception("Test failed!");
		}
	}
	
	inline auto
	expect_no_exception(std::function<auto()->void> const& block) -> void
	{
		bool	exc_discovered	=	false;
		try
		{
			block();
		}
		catch(...)
		{
			exc_discovered	=	true;
		}
		
		expect_true(not exc_discovered);
	}
	inline auto
	expect_exception(std::function<auto()->void> const& block) -> void
	{
		bool	exc_discovered	=	false;
		try
		{
			block();
		}
		catch(...)
		{
			exc_discovered	=	true;
		}
		
		expect_true(exc_discovered);
	}
}










EONIL_COMMONUTILITY_AGE2_NAMESPACE_END
