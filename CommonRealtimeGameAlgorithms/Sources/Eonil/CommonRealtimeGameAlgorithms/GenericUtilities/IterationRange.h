//
//  IterationRange.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 14/7/6.
//
//

#pragma once
#include "../CommonRealtimeGameAlgorithmsCommon.h"
EONIL_COMMON_REALTIME_GAME_ALGORITHMS_GENERIC_UTILITIES_BEGIN






/*!
 Two iterator pairs to represent range of object.
 
 @discussion
 Generalizes begin/end pair to represent a range of objects.
 
 @discussion
 Default initialization will create default initialized iterator pairs.
 
 @templatefield
 IT
 Must be an iterator type. Not value or container type.
 
 @note
 Putting iterator type parameter doesn't fit to generic-range concept.
 Use this only for limited context.
 */
template <typename IT>
class
IterationRange final
{
public:
	IterationRange() = default;
	IterationRange(IT begin, IT end);
	
	/*!
	 Any classes which has `begin/end` (of standard C++11 concepts) method pairs can be used.
	 Or proper `std::begin/std::end` pairs are also supported.
	 */
	template <typename C>
	IterationRange(C& container) : IterationRange(std::begin(container), std::end(container))
	{
	}
	
	auto	begin() -> IT;
	auto	end() -> IT;
	
private:
	IT	_begin	{};
	IT	_end	{};
};




template <typename IT>
IterationRange<IT>::
IterationRange(IT begin, IT end) : _begin(begin), _end(end)
{
}

template <typename IT> auto
IterationRange<IT>::
begin() -> IT
{
	return	_begin;
}
template <typename IT> auto
IterationRange<IT>::
end() -> IT
{
	return	_end;
}























EONIL_COMMON_REALTIME_GAME_ALGORITHMS_GENERIC_UTILITIES_END
