//
//  GenericIndexingRange.h
//  CommonUtility
//
//  Created by Hoon H. on 3/27/14.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#pragma once
#include "../Prelude.h"
EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_BEGIN




/*!
 
 Where example data is:
 
	0 1 2 3 4 5 6 7 8
	----+-------+----
	| | |v|v|v|v| | |
	-----------------
 
 
 Range of v is defined like this.
 
 -	location	=	2
 -	length		=	6 - 2	=	4
 -	begin index	=	2
 -	end index	=	6
 
 The index is distance from origin, not the number of cell.
 
 @deprecated
 Because it's ambiguous with memory-range concept. Do not use, and remove any existing references.
 Use `GenericNumericRange` class for newer code.
 */
template<typename T>
class
EONIL_MEDIA_ENGINE_DEPRECATE()
GenericIndexingRange
{
	static_assert(std::numeric_limits<T>::is_integer, "The type `T` must be an integer type.");
	
	T	_begin	{};
	T	_end	{};
	
public:
	GenericIndexingRange() = default;
	GenericIndexingRange(T const begin, T const end);
	GenericIndexingRange(T const size);
	
	auto	operator==(GenericIndexingRange const& range) const -> bool;
	auto	operator!=(GenericIndexingRange const& range) const -> bool;
	
	auto	operator+(T const amount) const -> GenericIndexingRange;
	auto	operator-(T const amount) const -> GenericIndexingRange;
	
	auto	empty() const -> bool;
	auto	begin() const -> T;
	auto	end() const -> T;
	auto	size() const -> T;
};

template <typename T>
GenericIndexingRange<T>::
GenericIndexingRange(T const begin, T const end) : _begin(begin), _end(end)
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		err9_converted_legacy_assertion(end >= begin);
	}
	
}
template <typename T>
GenericIndexingRange<T>::
GenericIndexingRange(T const size) : _begin(0), _end(size)
{
}

template <typename T> auto
GenericIndexingRange<T>::
operator==(GenericIndexingRange const& range) const -> bool
{
	return	_begin == range._begin and _end == range._end;
}
template <typename T> auto
GenericIndexingRange<T>::
operator!=(GenericIndexingRange const& range) const -> bool
{
	return	not (_begin == range._begin and _end == range._end);
}
template <typename T> auto
GenericIndexingRange<T>::
operator+(T const amount) const -> GenericIndexingRange
{
	return	{_begin + amount, _end + amount};
}
template <typename T> auto
GenericIndexingRange<T>::
operator-(T const amount) const -> GenericIndexingRange
{
	return	{_begin - amount, _end - amount};
}

template <typename T> auto
GenericIndexingRange<T>::
empty() const -> bool
{
	return	size() == 0;
}
template <typename T> auto
GenericIndexingRange<T>::
begin() const -> T
{
	return	_begin;
}
template <typename T> auto
GenericIndexingRange<T>::
end() const -> T
{
	return	_end;
}
template <typename T> auto
GenericIndexingRange<T>::
size() const -> T
{
	return	_end - _begin;
}
























/*!
 Maximum state is preserved to represent none-state. (positive and negative in signed value).
 So keep valid range not to use the state.
 */
template<typename T>
class
OptionalGenericIndexingRange : public GenericIndexingRange<T>
{
	static constexpr T const	INVALID_INDEX	=	std::numeric_limits<T>::max();
	
public:
	OptionalGenericIndexingRange();
	OptionalGenericIndexingRange(T const size);
	OptionalGenericIndexingRange(T const begin, T const end);
	
	/*!
	 Both of location and length value are not a specific value.
	 Always perform whole value comparison, and do not rely on both of location and length.
	 */
	static auto		none() -> OptionalGenericIndexingRange;
};











template <typename T>
OptionalGenericIndexingRange<T>::
OptionalGenericIndexingRange() : GenericIndexingRange<T>(INVALID_INDEX)
{
	
}
template <typename T>
OptionalGenericIndexingRange<T>::
OptionalGenericIndexingRange(T const size) : GenericIndexingRange<T>(size)
{
	EONIL_DEBUG_ASSERT(size < INVALID_INDEX);
}
template <typename T>
OptionalGenericIndexingRange<T>::
OptionalGenericIndexingRange(T const begin, T const end) : GenericIndexingRange<T>(begin, end)
{
	EONIL_DEBUG_ASSERT(begin < INVALID_INDEX);
	EONIL_DEBUG_ASSERT(end < INVALID_INDEX);
}

template <typename T> auto
OptionalGenericIndexingRange<T>::
none() -> OptionalGenericIndexingRange
{
	return	OptionalGenericIndexingRange();
}







using	IndexingRange			=	GenericIndexingRange<size_t>;
using	OptionalIndexingRange	=	OptionalGenericIndexingRange<size_t>;









EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_END
