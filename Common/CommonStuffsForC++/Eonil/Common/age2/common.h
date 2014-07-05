//
//  age2_common.h
//  CommonUtility
//
//  Created by Hoon H. on 2014/06/28.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#pragma once

/*!
 @header
 With Clang, system headers are expected to be imported as modules.
 Then it will not degrade build speed.
 */

#include <memory>
#include <string>
#include <vector>
#include <list>
#include <set>

#define	EONIL_COMMONUTILITY_AGE2_NAMESPACE_BEGIN				namespace Eonil { namespace Common {  inline namespace age2 {
#define	EONIL_COMMONUTILITY_AGE2_NAMESPACE_END					} } }

EONIL_COMMONUTILITY_AGE2_NAMESPACE_BEGIN


	


//template <typename T>	using	ptr		=	T*;		//	It's better to let each applications to define thier own `ptr` name.

template <typename T>	using	uptr	=	std::unique_ptr<T>;

template <typename T>	using	vec		=	std::vector<T>;
template <typename T>	using	set		=	std::set<T>;
template <typename T>	using	list	=	std::list<T>;


using	sz	=	std::size_t;
using	str	=	std::string;




/*!
 There's complex rule on implicit copying/moving stuffs.
 I put everything explicitly to ensure them.
 */
struct
no_copy
{
	no_copy() = default;
	no_copy(no_copy const&) = delete;
	no_copy(no_copy&&) = default;
	auto	operator=(no_copy const&) -> no_copy& = delete;
	auto	operator=(no_copy&&) -> no_copy& = default;
};


struct
no_move
{
	no_move() = default;
	no_move(no_move const&) = default;
	no_move(no_move&&) = delete;
	auto	operator=(no_move const&) -> no_move& = default;
	auto	operator=(no_move&&) -> no_move& = delete;
};












EONIL_COMMONUTILITY_AGE2_NAMESPACE_END
