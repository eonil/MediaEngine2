//
//  assignment_helpers.h
//  CommonUtility
//
//  Created by Hoon H. on 2014/06/28.
//  Copyright (c) 2014 Eonil. All rights reserved.
//


#pragma once
#include "error.h"
EONIL_COMMONUTILITY_AGE2_NAMESPACE_BEGIN








template <typename T>
static inline auto
copy_assignment_impl(T* this_ptr, T const& new_value) -> T&
{
	if (this_ptr != &new_value)
	{
		this_ptr->~T();
		new (this_ptr) T(new_value);
	}
	return	*this_ptr;
}


template <typename T>
static inline auto
move_assignment_impl(T* this_ptr, T&& new_value) -> T&
{
	if (this_ptr != &new_value)
	{
		this_ptr->~T();
		new (this_ptr) T(std::move(new_value));
	}
	return	*this_ptr;
}


















EONIL_COMMONUTILITY_AGE2_NAMESPACE_END
