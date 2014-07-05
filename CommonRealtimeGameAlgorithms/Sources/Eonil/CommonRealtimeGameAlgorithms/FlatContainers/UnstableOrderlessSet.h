////
////  UnstableOrderlessSet.h
////  TheFluxGame
////
////  Created by Hoon H. on 3/10/14.
////
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
//
//
//
///*!
// @classdesign
// This is just a plain vector but with *swap & pop* for removing an existing 
// value. Consequently, pointer stability is not guaranteed.
// 
// @discussion
// If you don't need to reference each values, then you can use this for maximum
// performance. This always keeps perfectly dense array, and you can get same 
// performance with just a raw value array. This performs O(1) for insert/erase.
// 
// @param	REALLOCATABLE
// If this is true, this class will allow reallocation of the back buffer, and
// your program may be suffer from sudden dynamic allocation lag. If this is
// false and you insert more then the initial capacity, then this will throw
// an exception, and program will crash.
// 
// */
//template <typename T, bool const REALLOCATABLE>
//class
//UnstableOrderlessSet
//{
//	vec<T>	_slots	{0};
//	
////			public:
////				using	ConstIterator	=	T const*;
////				using	Iterator		=	T*;
//	
//public:
//	UnstableOrderlessSet() = default;
//	UnstableOrderlessSet(Size const& capacity);
//
//	auto	capacity() const -> Size;
//	auto	size() const -> Size;
//	
//	auto	begin() const -> T const*;
//	auto	end() const -> T const*;
//	
//	auto	begin() -> T*;
//	auto	end() -> T*;
//	
//	auto	search(T const& v) const -> T const*;	//!	Searches for the first equal value. O(n) in worst case.
//	auto	search(T const& v) -> T*;				//!	Searches for the first equal value. O(n) in worst case.
//	
//	auto	insert(T const& v) -> void;				//!	Inserts a new entry by copying the value. This is O(1).
//	auto	erase(T* v) -> void;					//!	Erases an existing entry at the pointer. This is O(1).
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
//
//
//
//
//template <typename T, bool const REALLOCATABLE> UnstableOrderlessSet<T,REALLOCATABLE>::
//UnstableOrderlessSet(Size const& capacity)
//{
//	_slots.reserve(capacity);
//}
//
//
//template <typename T, bool const REALLOCATABLE> auto UnstableOrderlessSet<T,REALLOCATABLE>::
//capacity() const -> Size
//{
//	return	_slots.capacity();
//}
//template <typename T, bool const REALLOCATABLE> auto UnstableOrderlessSet<T,REALLOCATABLE>::
//size() const -> Size
//{
//	return	_slots.size();
//}
//
//
//
//template <typename T, bool const REALLOCATABLE> auto UnstableOrderlessSet<T,REALLOCATABLE>::
//begin() const -> T const*
//{
//	return	&_slots.front();
//}
//template <typename T, bool const REALLOCATABLE> auto UnstableOrderlessSet<T,REALLOCATABLE>::
//end() const -> T const*
//{
//	return	&_slots.back();
//}
//
//template <typename T, bool const REALLOCATABLE> auto UnstableOrderlessSet<T,REALLOCATABLE>::
//begin() -> T*
//{
//	return	size() == 0 ? nullptr : &_slots.front();
//}
//template <typename T, bool const REALLOCATABLE> auto UnstableOrderlessSet<T,REALLOCATABLE>::
//end() -> T*
//{
//	return	size() == 0 ? nullptr : &_slots.back();
//}
//
//
//template <typename T, bool const REALLOCATABLE> auto UnstableOrderlessSet<T,REALLOCATABLE>::
//search(T const& v) const -> T const*
//{
//	return	((std::remove_const<decltype(this)>)this)->search(v);
//}
//template <typename T, bool const REALLOCATABLE> auto UnstableOrderlessSet<T,REALLOCATABLE>::
//search(T const& v) -> T*
//{
//	auto		it1		=	std::find(_slots.begin(), _slots.end(), v);
//	T*			ptr2	=	&*it1;
//	return		ptr2;
//}
//
//
//template <typename T, bool const REALLOCATABLE> auto UnstableOrderlessSet<T,REALLOCATABLE>::
//insert(T const& v) -> void
//{
//	EONIL_DEBUG_ASSERT(REALLOCATABLE or (_slots.size() < _slots.capacity()));
//	_slots.push_back(v);
//}
//template <typename T, bool const REALLOCATABLE> auto UnstableOrderlessSet<T,REALLOCATABLE>::
//erase(T* v) -> void
//{
//	EONIL_DEBUG_ASSERT(v >= &_slots.front());
//	EONIL_DEBUG_ASSERT(v < &_slots.back());
//	std::swap(*v, _slots.back());
//	_slots.pop_back();
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
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END
//
//
