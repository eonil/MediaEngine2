//
//  none.h
//  CommonUtility
//
//  Created by Hoon H. on 2014/06/28.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#pragma once
#include "common.h"
EONIL_COMMONUTILITY_AGE2_NAMESPACE_BEGIN








/*!
 A singleton object used to compare value-type's nillity.
 Used as a pronoun for any type.
 
 @discussion
 None is a singleton class.
 Most operations are prohibited.
 */
class
None final : no_copy, no_move
{
	std::nullptr_t		ptr{nullptr};
	
	
public:
	constexpr None()	{}
	
public:
	auto	operator==(None const& none) const -> bool = delete;
	auto	operator!=(None const& none) const -> bool = delete;
	auto	operator<(None const& none) const -> bool = delete;
	auto	operator>(None const& none) const -> bool = delete;
	auto	operator<=(None const& none) const -> bool = delete;
	auto	operator>=(None const& none) const -> bool = delete;
};

using	none	=	None;


constexpr None const	NONE{};							//	Safe to be static because zero value equals to instantiated value.
//static constexpr None const	NONE{None::none()};		//	Safe to be static because zero value equals to instantiated value.




















EONIL_COMMONUTILITY_AGE2_NAMESPACE_END

