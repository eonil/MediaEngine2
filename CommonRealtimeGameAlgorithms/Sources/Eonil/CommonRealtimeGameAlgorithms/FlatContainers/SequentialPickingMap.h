////
////  SequentialPickingMap.h
////  TheMagnetismGame
////
////  Created by Hoon H. on 4/12/14.
////  Copyright (c) 2014 Eonil Company. All rights reserved.
////
//
//#pragma once
//
//#include "../CommonRealtimeGameAlgorithmsCommon.h"
//
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_BEGIN
//
//
//
//
//
//
//
//
//
///*!
// An ordered map provides O(1) complexity for seach-by-key operation if users access all pairs sequentially.
// 
// @discussion
// Searching in map is very frequent operation, and must be fast as much as possible.
// Usually the best generic map search complexity is known as *armortized O(1)*, but the exceptional worst
// case cost is not acceptable for us. And also, we don't want to calculate hash-code for each values.
// If we can limit access pattern to strictly sequential, we can archive strict O(1) access for search,
// and this class provides that.
// 
// @classdesign
// This is read-only container for simplicity.
// 
// @param	STRICT
// If this is `true`, this class will *force* sequential access. If user tries to access key-value
// pairs in non-sequential order, this will throw an exception in debug mode. (result undefined in release mode)
// If this is `false`, non-sequential access will return a correct value, but the operation complexity
// can be increased up to O(n) in worst case.
// 
// @thread
// This class is thread-unsafe.
// */
//template <typename K, typename V, bool const STRICT = true>
//class
//SequentialPickingMap
//{
//	using	PAIR	=	std::pair<K, V>;
//	
//	vec<PAIR>			_pairs		{};
//	mutable Size		_next_idx	{};
//	
//public:
//	SequentialPickingMap() = default;
//	SequentialPickingMap(vec<PAIR> const& pairs);
//	SequentialPickingMap(vec<PAIR>&& pairs);
//	
//	auto	empty() const -> bool;
//	auto	size() const -> Size;
//	auto	at(K const& k) const -> V const&;
//};
//
//
//
//template <typename K, typename V, bool const STRICT>
//SequentialPickingMap<K,V,STRICT>::
//SequentialPickingMap(vec<PAIR> const& pairs) : _pairs(pairs), _next_idx(0)
//{
//}
//template <typename K, typename V, bool const STRICT>
//SequentialPickingMap<K,V,STRICT>::
//SequentialPickingMap(vec<PAIR>&& pairs) : _pairs(std::move(pairs)), _next_idx(0)
//{
//}
//template <typename K, typename V, bool const STRICT> auto
//SequentialPickingMap<K,V,STRICT>::
//empty() const -> bool
//{
//	return	_pairs.empty();
//}
//template <typename K, typename V, bool const STRICT> auto
//SequentialPickingMap<K,V,STRICT>::
//size() const -> Size
//{
//	return	_pairs.size();
//}
//template <typename K, typename V, bool const STRICT> auto
//SequentialPickingMap<K,V,STRICT>::
//at(K const& k) const -> V const&
//{
//	EONIL_DEBUG_ASSERT(not empty());
//	
//	PAIR const&	p1	=	_pairs.at(_next_idx);
//	
//	if (STRICT)
//	{
//		EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(p1.first == k, "You must pick a value in sequential order. Current expected key doesn't match with supplied key.");
//		goto	OK;
//	}
//	else
//	{
//		if (p1.first == k)
//		{
//			goto	OK;
//		}
//		else
//		{
//			Size	s1	=	size();
//			for (Size i=0; i<s1; i++)
//			{
//				auto const&	p2	=	_pairs.at(i);
//				if (p2.first == k)
//				{
//					_next_idx	=	i-1;		//	Underflowing is fine because it will be overflown again immediately.
//					goto	OK;
//				}
//			}
//			EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(false, "Cannot find a value for the key.");
//		}
//	}
//
//OK:
//	_next_idx++;
//	if (_next_idx == size())
//	{
//		_next_idx	=	0;
//	}
//	return	p1.second;
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
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END
//
