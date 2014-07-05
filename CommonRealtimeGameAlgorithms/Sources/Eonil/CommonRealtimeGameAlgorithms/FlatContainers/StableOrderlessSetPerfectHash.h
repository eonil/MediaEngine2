////
////  StableOrderlessSetPerfectHash.h
////  TheMagnetismGame
////
////  Created by Hoon H. on 4/28/14.
////  Copyright (c) 2014 Eonil Company. All rights reserved.
////
//
//#pragma once
//
//#include "../CommonRealtimeGameAlgorithmsCommon.h"
//#include "StableOrderlessSet.h"
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
//
//
//
//
//
//
///*!
// Resolves perfect-hash of an item in a `StableOrderlessSet`.
// 
// @classdesign
// Generates hash value in range of 0...(N-1) where N is number of items in the set.
// 
// @discussion
// Actually the returning hash value is just an offset from the internal memory slot.
// */
//template <typename T>
//class
//StableOrderlessSetPerfectHash
//{
//public:
//	StableOrderlessSetPerfectHash(StableOrderlessSet<T> const*);
//	
//	auto	operator()(T const& item) const -> Size;
//	
//private:
//	StableOrderlessSet<T> const*	_the_set_ptr	{nullptr};
//};
//
//template <typename T>
//StableOrderlessSetPerfectHash<T>::
//StableOrderlessSetPerfectHash(StableOrderlessSet<T> const* o) : _the_set_ptr(o)
//{
//}
//template <typename T> auto
//StableOrderlessSetPerfectHash<T>::
//operator()(const T &item) const -> Size
//{
//	T*		starting_ptr	=	_the_set_ptr->_items.data();
//	Size	offset			=	&item - starting_ptr;
//	return	offset;
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
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END
