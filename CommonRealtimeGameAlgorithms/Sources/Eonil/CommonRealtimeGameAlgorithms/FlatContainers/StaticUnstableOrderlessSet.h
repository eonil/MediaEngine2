//
//  StaticUnstableOrderlessSet.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 14/4/29.
//
//

#pragma once

#include "../CommonRealtimeGameAlgorithmsCommon.h"
#include "ListAtomSlot.h"

EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_BEGIN









template <typename T, Size const LEN>
class
StaticUnstableOrderlessSet
{
public:
	class
	Exception : public std::logic_error
	{
	public:
		using	logic_error::logic_error;
	};
	
public:
	auto	empty() const -> bool;
	auto	size() const -> Size;
	
	auto	begin() const -> T const*;
	auto	begin() -> T*;
	auto	end() const -> T const*;
	auto	end() -> T*;
		
	auto	insert(T const&) -> void;
	auto	insert(T&&) -> void;
	auto	erase(T*) -> void;
	auto	clear() -> void;
	
private:
	using	ITEM	=	MemoryStorage<T>;
	using	ITEMS	=	std::array<ITEM, LEN>;
	
	Size	_count	{};
	ITEMS	_slots	{};
	
	auto	_last() -> MemoryStorage<T>&;
	
	
	
#if EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_MODE
private:
	friend class		StaticUnstableOrderlessSet_DebuggingSupport;
#endif
};


















template <typename T, Size const LEN> auto
StaticUnstableOrderlessSet<T,LEN>::
empty() const -> bool
{
	return	_count == 0;
}
template <typename T, Size const LEN> auto
StaticUnstableOrderlessSet<T,LEN>::
size() const -> Size
{
	return	_count;
}

template <typename T, Size const LEN> auto
StaticUnstableOrderlessSet<T,LEN>::
begin() const -> T const*
{
	return	&_slots.at(0).value();
}
template <typename T, Size const LEN> auto
StaticUnstableOrderlessSet<T,LEN>::
begin() -> T*
{
	return	&_slots.at(0).value();
}
template <typename T, Size const LEN> auto
StaticUnstableOrderlessSet<T,LEN>::
end() const -> T const*
{
	return	&(_slots.data() + _count)->value();
}
template <typename T, Size const LEN> auto
StaticUnstableOrderlessSet<T,LEN>::
end() -> T*
{
	return	&(_slots.data() + _count)->value();
}



template <typename T, Size const LEN> auto
StaticUnstableOrderlessSet<T,LEN>::
insert(T const &o) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		error_if(_count == LEN, "This set is full.");
	}
	
	_slots.at(_count).initialize(o);
	_count++;
}
template <typename T, Size const LEN> auto
StaticUnstableOrderlessSet<T,LEN>::
insert(T &&o) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		error_if(_count == LEN, "This set is full.");
	}
	
	_slots.at(_count).initialize(std::move(o));
	_count++;
}
template <typename T, Size const LEN> auto
StaticUnstableOrderlessSet<T,LEN>::
erase(T *ptr1) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		error_if(_count == 0, "This set is empty.");
	}
	
	if (ptr1 != &_last().value())
	{
		/*
		 Pull last to here.
		 */
		ITEM*	ptr2	=	reinterpret_cast<ITEM*>(ptr1);
		ptr2->terminate();
		ptr2->initialize(std::move(_last().value()));
	}
	
	_count--;
	_slots.at(_count).terminate();
}
template <typename T, Size const LEN> auto
StaticUnstableOrderlessSet<T,LEN>::
clear() -> void
{
	for (Size i=0; i<_count; i++)
	{
		_slots.at(i).terminate();
	}
	_count	=	0;
}














template <typename T, Size const LEN> auto
StaticUnstableOrderlessSet<T,LEN>::
_last() -> MemoryStorage<T>&
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		error_if(_count == 0, "No items, no last item.");
	}
	return	_slots.at(_count-1);
}










#if EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_MODE
struct
StaticUnstableOrderlessSet_DebuggingSupport
{
	template<typename T, Size const LEN>
	static auto
	get_item_slot_at(StaticUnstableOrderlessSet<T,LEN>& set, Size const index) -> typename StaticUnstableOrderlessSet<T,LEN>::ITEM&
	{
		return	set._slots.at(index);
	}
};
#endif











EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END


