////
////  Range.h
////  CommonRealtimeGameAlgorithms
////
////  Created by Hoon H. on 14/4/29.
////
////
//
//#pragma once
//
//#include "../CommonRealtimeGameAlgorithmsCommon.h"
//
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_GENERIC_UTILITIES_BEGIN
//
//
//
//
//
//
///*!
// Two iterator pairs to represent range of object.
// 
// @discussion
// Generalizes begin/end pair to represent a range of objects.
// 
// @discussion
// Default initialization will create default initialized iterator pairs.
// 
// @templatefield
// IT
// Must be an iterator type. Not value or container type.
// */
//template <typename IT>
//class
//Range final
//{
//public:
//	Range() = default;
//	Range(IT begin, IT end);
//	
//	/*!
//	 Any classes which has `begin/end` (of standard C++11 concepts) method pairs can be used.
//	 Or proper `std::begin/std::end` pairs are also supported.
//	 */
//	template <typename C>
//	Range(C& container) : Range(std::begin(container), std::end(container))
//	{
//	}
//	
//	auto	begin() -> IT;
//	auto	end() -> IT;
//	
//private:
//	IT	_begin	{};
//	IT	_end	{};
//};
//
//
//
//
//template <typename IT>
//Range<IT>::
//Range(IT begin, IT end) : _begin(begin), _end(end)
//{
//}
//
//template <typename IT> auto
//Range<IT>::
//begin() -> IT
//{
//	return	_begin;
//}
//template <typename IT> auto
//Range<IT>::
//end() -> IT
//{
//	return	_end;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_GENERIC_UTILITIES_END
