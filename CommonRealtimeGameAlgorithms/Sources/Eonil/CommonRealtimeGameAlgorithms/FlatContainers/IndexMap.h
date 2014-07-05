////
////  IndexMap.h
////  TheMagnetismGame
////
////  Created by Hoon H. on 4/28/14.
////  Copyright (c) 2014 Eonil Company. All rights reserved.
////
//
//#pragma once
//
//#include "../CommonRealtimeGameAlgorithmsCommon.h"
//
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
//
//
//
///*!
// A map which uses integer index as key.
// 
// @classdesign
// Archives O(1) search by sacrificing memory.
// 
// @param
// C
// Maximum capacity.
// */
//template <typename T, Size const C>
//class
//IndexMap
//{
//	static Size const CAPACITY	=	C;
//	using	KEY		=	Size;
//	using	VALUE	=	T;
//	
//	
//	
//public:
//	IndexMap();
//	~IndexMap();
//	
//	auto	size() const -> Size;
//	
//	auto	at(Size const&) const -> T const&;
//	auto	at(Size const&) -> T&;
//	
//	auto	insert(KEY const&, VALUE&&) -> void;
//	auto	erase(KEY const&) -> void;
//	
//
//
//private:
//	/*!
//	 @ref	http://stackoverflow.com/questions/12304629/prevent-calls-to-default-constructor-for-an-array-inside-class
//	 */
//	class
//	Item
//	{
//		using	UT	=	typename std::aligned_storage<sizeof(T)>::type;
//		
//		UT		_value;			//	Initialization prevented.
//		bool	_occupation	{false};
//		
//	public:
//		auto
//		value() const -> T const&
//		{
//			EONIL_DEBUG_ASSERT(_occupation);
//			return	_value;
//		}
//		auto
//		value() -> T&
//		{
//			EONIL_DEBUG_ASSERT(_occupation);
//			return	_value;
//		}
//		auto
//		set(T&& o) -> void
//		{
//			EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(not _occupation);
//			new (&_value)T(std::move(o));
//			_occupation	=	true;
//		}
//		auto
//		unset() -> void
//		{
//			EONIL_DEBUG_ASSERT(_occupation);
//			_value.~T();
//			_occupation	=	false;
//		}
//		auto
//		unsetIfPossible() -> void
//		{
//			if (_occupation)
//			{
//				unset();
//			}
//		}
//	};
//	
//	Item	_slots[C]{};
//	Size	_count{0};
//};
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
//template <typename T, Size const C>
//IndexMap<T,C>::
//IndexMap()
//{
//}
//template <typename T, Size const C>
//IndexMap<T,C>::
//~IndexMap()
//{
//	for (Size i=0; i<C; i++)
//	{
//		_slots.unsetIfPossible();
//	}
//}
//
//template <typename T, Size const C> auto
//IndexMap<T,C>::
//size() const -> Size
//{
//	return	_count;
//}
//
//template <typename T, Size const C> auto
//IndexMap<T,C>::
//at(const Size &o) const -> T const&
//{
//	return	_slots[o].value();
//}
//template <typename T, Size const C> auto
//IndexMap<T,C>::
//at(const Size &o) -> T&
//{
//	return	_slots[o].value();
//}
//
//template <typename T, Size const C> auto
//IndexMap<T,C>::
//insert(KEY const& key, VALUE&& value) -> void
//{
//	EONIL_DEBUG_ASSERT(_count < C);
//	_slots[key].set(std::move(value));
//	_count++;
//}
//template <typename T, Size const C> auto
//IndexMap<T,C>::
//erase(KEY const& key) -> void
//{
//	EONIL_DEBUG_ASSERT(_count > 0);
//	_count--;
//	_slots[key].unset();
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
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END
//
//
//
//
//
//
//
