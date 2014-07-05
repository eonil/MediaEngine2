//
//  StaticStableOrderlessSet.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 14/4/29.
//
//

#pragma once

#include "../CommonRealtimeGameAlgorithmsCommon.h"
#include "StaticStableListStack.h"
#include "StaticStableListMap.h"

EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_BEGIN








/*!
 Do not `erase` any object while iterating. It will invalidate all existing iterators which pointing the object.
 As a result, further iteration will fail. Anyway, any other iterators which are pointing other objects will not be
 affected. Calling `clear` has same effect on all objects.
 */
template <typename T, Size const LEN>
class
StaticStableOrderlessSet : ExceptionSupportTools
{
public:
	class
	Exception : public std::logic_error
	{
	public:
		using	logic_error::logic_error;
	};
	
	using	ConstIterator	=	ListAtomSlotIterator<T const>;
	using	Iterator		=	ListAtomSlotIterator<T>;
	
public:
	static constexpr auto	capacity() -> Size;
	
public:
	auto	empty() const -> bool;
	auto	size() const -> Size;
	
	auto	begin() const -> ConstIterator;
	auto	begin() -> Iterator;
	auto	end() const -> ConstIterator;
	auto	end() -> Iterator;
	
	template <typename... ARGS>
	auto	emplace(ARGS&&... args) -> T*;
	auto	insert(T const&) -> T*;
	auto	insert(T&&) -> T*;
	auto	erase(T*) -> void;		//!	This will invalidate all existing iterators which are pointing target object.
	auto	clear() -> void;		//!	This will invalidate all existing iterators.
	
	/*!
	 Returns an integer for the iterator as a concept of perfect-hash.
	 Value range N is:
	 
		0 <= N < size()

	 You can use this value as a perfect-hash key to link another object.
	 Retunring number is actually an index (memory offset).
	 */
	auto	hash(ConstIterator) const -> Size;
	auto	hash(T const*) const -> Size;
	auto	hash(T const&) const -> Size;
	
private:
	StaticStableListMap<T, LEN>			_items			{};
	StaticStableListStack<Size, LEN>	_free_slot_idxs	{};		//	Use circular queue as soon as ready.
	
	auto	_feed_available_slot_idx() -> Size;								//	You must consume fed index. If you don't use it, it will leak.
};










template <typename T, Size const LEN>
constexpr auto
StaticStableOrderlessSet<T,LEN>::
capacity() -> Size
{
	return	LEN;
}



template <typename T, Size const LEN>
auto
StaticStableOrderlessSet<T,LEN>::
size() const -> Size
{
	return	_items.size();
}
template <typename T, Size const LEN>
auto
StaticStableOrderlessSet<T,LEN>::
begin() const -> ConstIterator
{
	return	_items.begin();
}
template <typename T, Size const LEN>
auto
StaticStableOrderlessSet<T,LEN>::
begin() -> Iterator
{
	return	_items.begin();
}
template <typename T, Size const LEN>
auto
StaticStableOrderlessSet<T,LEN>::
end() const -> ConstIterator
{
	return	_items.end();
}
template <typename T, Size const LEN>
auto
StaticStableOrderlessSet<T,LEN>::
end() -> Iterator
{
	return	_items.end();
}

template <typename T, Size const LEN>
template <typename ...ARGS>
auto
StaticStableOrderlessSet<T,LEN>::
emplace(ARGS&&... args) -> T*
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(_items.size() == LEN, "This set is full.");
		halt_if(_items.size() > LEN, "Inconsistent internal array state. Serious bug!");
	}
	
	////
	
	Size	idx1	=	_feed_available_slot_idx();
	_items.emplace(idx1, std::forward<ARGS>(args)...);
	return	&_items.at(idx1);
}
template <typename T, Size const LEN>
auto
StaticStableOrderlessSet<T,LEN>::
insert(const T &o) -> T*
{
	return	insert(T(o));
}
template <typename T, Size const LEN>
auto
StaticStableOrderlessSet<T,LEN>::
insert(T &&o) -> T*
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(_items.size() == LEN, "This set is full.");
		halt_if(_items.size() > LEN, "Inconsistent internal array state. Serious bug!");
	}
	
	////
	
	Size	idx1	=	_feed_available_slot_idx();
	_items.insert(idx1, std::move(o));
	return	&_items.at(idx1);
}
template <typename T, Size const LEN>
auto
StaticStableOrderlessSet<T,LEN>::
erase(T* o) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(_items.size() == 0, "This set is empty.");
		error_if((char const*)o < (char const*)&_items, "The iterator is out of range.");
		error_if((char const*)o > ((char const*)&_items)+sizeof(_items), "The iterator is out of range.");
	}
	if (USE_HEAVY_EXCEPTION_CHECKINGS)
	{
		error_if(std::find(_free_slot_idxs.begin(), _free_slot_idxs.end(), _items.index(o)) != _free_slot_idxs.end(), "The object pointer is marked as empty. You're supplying wrong pointer.");
	}
	
	////
	
	Size		idx1	=	_items.index(o);
	_items.erase(idx1);
	_free_slot_idxs.push(idx1);
}
template <typename T, Size const LEN>
auto
StaticStableOrderlessSet<T,LEN>::
clear() -> void
{
	_items.clear();
	_free_slot_idxs.clear();
}

template <typename T, Size const LEN>
auto
StaticStableOrderlessSet<T,LEN>::
hash(ConstIterator o) const -> Size
{
	return	_items.index(o);
}
template <typename T, Size const LEN>
auto
StaticStableOrderlessSet<T,LEN>::
hash(T const* o) const -> Size
{
	return	_items.index(o);
}
template <typename T, Size const LEN>
auto
StaticStableOrderlessSet<T,LEN>::
hash(T const& o) const -> Size
{
	return	_items.index(&o);
}

















template <typename T, Size const LEN>
auto
StaticStableOrderlessSet<T,LEN>::
_feed_available_slot_idx() -> Size
{
	if (_free_slot_idxs.size() == 0)
	{
		return	_items.size();
	}
	else
	{
		Size	idx1	=	_free_slot_idxs.back();
		_free_slot_idxs.pop();
		return	idx1;
	}
}

















EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END
