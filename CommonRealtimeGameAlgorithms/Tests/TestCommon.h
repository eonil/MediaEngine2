//
//  TestCommon.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 14/4/30.
//
//

#pragma once

#include <exception>
#include <array>
#include <vector>
#include <iostream>
//#include <Eonil/CommonRealtimeGameAlgorithms.h>
#include "CommonRealtimeGameAlgorithms.h"

using namespace	Eonil::CommonRealtimeGameAlgorithms::FlatContainers;



template <typename T>
inline auto
_test_log(T const& v) -> void
{
	std::cout << v << "\n";
}

#define	test_log(expr)	_test_log(std::string(#expr) + std::string(" = ") + std::to_string(expr))
	
inline auto
test_assert(bool const cond) -> void
{
	if (not cond)
	{
		std::terminate();
	}
}

inline auto
always_have_some_exception(std::function<auto()->void> const& f1) -> bool
{
	bool	any_exc	=	false;
	try
	{
		f1();
	}
	catch(...)
	{
		any_exc	=	true;
	}
	return	any_exc;
}
inline auto
never_have_any_exception(std::function<auto()->void> const& f1) -> bool
{
	return	not always_have_some_exception(f1);
}
inline auto
test_assert_always_exception(std::function<auto()->void> const& f1) -> void
{
	test_assert(always_have_some_exception(f1));
}
inline auto
test_assert_never_exception(std::function<auto()->void> const& f1) -> void
{
	test_assert(never_have_any_exception(f1));
}

