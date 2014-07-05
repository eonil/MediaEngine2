//
//  StaticStableListMap.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 14/4/29.
//
//

#pragma once

#include "../CommonRealtimeGameAlgorithmsCommon.h"
#include "ListAtomSlot.h"
#include "ListAtomSlotIterator.h"

EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_BEGIN









/*!
 A map which maps an integer to a value slot.
 Capacity is statically fixed.
 
 @discussion
 The internal storage starts with uninitialize memory block, and will be
 initialized when you insert, and deinitialized when you erase.

 This object tracks and keeps occupation state of each slots, and this increases
 instance size of this object.
 
 @discussion
 This is very dense at full with a small padding for marking occupation of each slots.
 If map is not full, there can be many empty slots, and filled slots can be treated as sparse list.

 @exception
 All methods guarantees strong safety as far as the type `T` provides strong safety for all methods.
 Anyway those guarantees are applied only on debug build. There's no check, safety
 guarantee or throwing on release build. (data just be will corrupted.)
 */
template <typename T, Size const LEN>
class
StaticStableListMap : ExceptionSupportTools
{
	using	ITEM	=	ListAtomSlot<T>;					//!	Occupation marking is required for iteration. That's why this is `ListAtomSlot` instead of `MemoryStorage`.
	using	ITEMS	=	std::array<ITEM, LEN>;
	
	
	
public:
	using	ConstIterator		=	ListAtomSlotIterator<T const>;
	using	Iterator			=	ListAtomSlotIterator<T>;
	
	class
	Exception : std::logic_error
	{
	public:
		using	logic_error::logic_error;
	};
	
//	class
//	ItemSlot final : public ListAtomSlot<T>
//	{
//	public:
//		
//	private:
//		friend class	StaticStableListMap;
//		using			ListAtomSlot<T>::ListAtomSlot;
//	};
	
public:
	StaticStableListMap();
	StaticStableListMap(StaticStableListMap&&);
	StaticStableListMap(StaticStableListMap const&);
	~StaticStableListMap();
	
	auto	operator=(StaticStableListMap const& o) -> StaticStableListMap&;
	auto	operator=(StaticStableListMap&& o) -> StaticStableListMap&;
	
	////
	
	auto	empty() const -> bool;
	auto	capacity() const -> Size;
	auto	size() const -> Size;
	
	/*!
	 Resolves index from a pointer to a value.
	 
	 @note
	 This uses pointer address arithmetics to calculate offset.
	 */
	auto	index(T const*) const -> Size;
	auto	index(ConstIterator) const -> Size;
	
	auto	at(Size const& index) const -> T const&;
	auto	at(Size const& index) -> T&;
	
	auto	begin() const -> ConstIterator;
	auto	begin() -> Iterator;
	auto	end() const -> ConstIterator;
	auto	end() -> Iterator;
	
	auto	find(Size const index) const -> T const*;			//!	Returns `nullptr` if the value is not available at the index.
	auto	find(Size const index) -> T*;						//!	Returns `nullptr` if the value is not available at the index.
	
	template <typename... ARGS>
	auto	emplace(Size const index, ARGS&&... args) -> void;
	auto	insert(Size const index, T const& v) -> void;
	auto	insert(Size const index, T&& v) -> void;
	auto	erase(Size const index) -> void;
	auto	clear() -> void;

	
	
	
private:
	static_assert(LEN > 0, "Zero-length is not supported.");
	
	Size	_count		{0};					//	I think it would be better to place size at first.
	ITEMS	_items		{};
	
	inline auto			_begin_value_ptr() const -> T const*;
	inline auto			_end_value_ptr() const -> T const*;
};
































template <typename T, Size const LEN>
StaticStableListMap<T,LEN>::
StaticStableListMap()
{
	_items.at(LEN-1).sentinelize();
}
//template <typename T, Size const LEN>
//StaticStableListMap<T,LEN>::
//StaticStableListMap(StaticStableListMap const& o) : _count(o._count)
//{
//	for (Size i=0; i<LEN; i++)
//	{
//		if (o._items[i].occupation())
//		{
//			_items[i].initialize(o._items[i].value());				//	Copy-assignment.
//		}
//	}
//}
//template <typename T, Size const LEN>
//StaticStableListMap<T,LEN>::
//StaticStableListMap(StaticStableListMap&& o) : _count(std::move(o._count))
//{
//	for (Size i=0; i<LEN; i++)
//	{
//		if (o._items[i].occupation())
//		{
//			_items[i].initialize(std::move(o._items[i].value()));	//	Copy-assignment.
//		}
//	}
//}
template <typename T, Size const LEN>
StaticStableListMap<T,LEN>::
StaticStableListMap(StaticStableListMap const& o) : _count(o._count), _items(o._items)
{
}
template <typename T, Size const LEN>
StaticStableListMap<T,LEN>::
StaticStableListMap(StaticStableListMap&& o) : _count(std::move(o._count)), _items(std::move(o._items))
{
}

template <typename T, Size const LEN>
StaticStableListMap<T,LEN>::
~StaticStableListMap()
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
	}
	
	////
	
	clear();
}

template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
operator=(const StaticStableListMap &o) -> StaticStableListMap&
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_error_if_supplied_reference_is_dereference_of_null(o, "copy-assignment");
	}
	
	////
	
	if (&o != this)
	{
		StaticStableListMap	copy	=	o;
		std::swap(_count, copy._count);
		std::swap(_items, copy._items);
	}
	return	*this;
}
template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
operator=(StaticStableListMap &&o) -> StaticStableListMap&
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_error_if_supplied_reference_is_dereference_of_null(o, "move-assignment");
	}
	
	////

	if (&o != this)
	{
		_count	=	std::move(o._count);
		_items	=	std::move(o._items);
	}
	return	*this;
}
//template <typename T, Size const LEN> auto
//StaticStableListMap<T,LEN>::
//operator=(const StaticStableListMap &o) -> StaticStableListMap&
//{
//	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(&o != nullptr);
//	_except_if(&o == nullptr, "Cannot copy-assign from a value pointed by a `nullptr`.");
//	ASSERT_PROPER_INSTANCE();
//	
//	if (&o == this)
//	{
//		//	Do nothing.
//	}
//	else
//	{
//		for (Size i=0; i<LEN; i++)
//		{
//			if (o._items[i].occupation())
//			{
//				_items[i].initialize(o._items[i].value());
//			}
//		}
//	}
//	return	*this;
//}
//template <typename T, Size const LEN> auto
//StaticStableListMap<T,LEN>::
//operator=(StaticStableListMap &&o) -> StaticStableListMap&
//{
//	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(&o != nullptr);
//	_except_if(&o == nullptr, "Cannot move-assign from a value pointed by a `nullptr`.");
//	ASSERT_PROPER_INSTANCE();
//	
//	if (&o == this)
//	{
//		//	Do nothing.
//	}
//	else
//	{
//		for (Size i=0; i<LEN; i++)
//		{
//			if (o._items[i].occupation())
//			{
//				_items[i].initialize(std::move(o._items[i].value()));
//			}
//		}
//	}
//	
//	/*
//	 The source object is filled with objects with no guts. Anyway they will be destroyed by the source object itself.
//	 */
//	
//	return	*this;
//}











template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
empty() const -> bool
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
	}
	
	////
	
	return	_count == 0;
}
template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
capacity() const -> Size
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
	}
	
	////
	
	return	LEN;
}
template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
size() const -> Size
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
	}
	
	////
	
	return	_count;
}

template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
index(T const* o) const -> Size
{
	static_assert(sizeof(_items) == sizeof(ITEM) * LEN, "The ITEM array is not laid out as expected. If your compiler does not support precise/dense array layout, it can't be used for this library.");
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		halt_if(_items.data() == nullptr, "Slot was not allocated properly!");
		error_if(o == nullptr, "The pointer shouldn't be `nullptr`.");
		error_if(ITEM::addressOfSlotForValuePointer(o) < _items.data(), "The pointer is out of range.");
		error_if(ITEM::addressOfSlotForValuePointer(o) >= _items.data()+_items.size(), "The pointer is out of range.");
	}
	
	////
	
	ITEM const*	begin_item_ptr		=	_items.data();
	ITEM const*	target_item_ptr		=	ITEM::addressOfSlotForValuePointer(o);
	
	Size		count_offset	=	target_item_ptr - begin_item_ptr;
	return		count_offset;
}
template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
index(ConstIterator o) const -> Size
{
	return	index(&*o);
}
template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
at(Size const& index) const -> T const&
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(index >= LEN, "Specified index is out of range.");
	}
	
	////
	
	return	_items[index].value();
}
template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
at(Size const& index) -> T&
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(index >= LEN, "Specified index is out of range.");
	}
	
	////
	
	return	_items[index].value();
}

template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
begin() const -> ConstIterator
{
	return	_items.data();
}
template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
begin() -> Iterator
{
	return	_items.data();
}
template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
end() const -> ConstIterator
{
	return	nullptr;
}
template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
end() -> Iterator
{
	return	nullptr;
}



template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
find(Size const index) const -> T const*
{
	if (_items[index].occupation())
	{
		return	&_items[index].value();
	}
	else
	{
		return	nullptr;
	}
}
template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
find(Size const index) -> T*
{
	if (_items[index].occupation())
	{
		return	&_items[index].value();
	}
	else
	{
		return	nullptr;
	}
}




template <typename T, Size const LEN>
template <typename ...ARGS> auto
StaticStableListMap<T,LEN>::
emplace(Size const index, ARGS&&... args) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(index >= LEN, "The specified index is out of range.");
		error_if(_items[index].occupation(), "The slot at the index is already occupied.");
	}
	
	////
	
	_items[index].initialize(std::forward<ARGS>(args)...);
	_count++;
}
template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
insert(Size const index, const T &v) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(index >= LEN, "The specified index is out of range.");
		error_if(_items[index].occupation(), "The slot at the index is already occupied.");
	}
	
	////
	
	_items[index].initialize(v);
	_count++;
}
template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
insert(Size const index, T &&v) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(index >= LEN, "The specified index is out of range.");
		error_if(_items[index].occupation(), "The slot at the index is already occupied.");
	}
	
	////
	
	_items[index].initialize(std::move(v));
	_count++;
}
template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
erase(Size const index) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(index >= LEN, "The specified index is out of range.");
		error_if(not _items[index].occupation(), "The slot at the index is not occupied.");
	}
	
	////
	
	_count--;
	_items[index].terminate();
}
template <typename T, Size const LEN> auto
StaticStableListMap<T,LEN>::
clear() -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
	}
	
	////
	
//	if (std::is_trivially_destructible<T>::value)
//	{
//		//!	Type `T` destructor doesn't need to be called. Just do nothing.
//		//!	@ref http://www.cplusplus.com/reference/type_traits/is_trivially_destructible/
//	}
//	else
	{
		//	Deinitialize all existing instances.
		for (Size i=0; i<LEN; i++)
		{
			if (_items[i].occupation())
			{
				_items[i].terminate();
			}
		}
	}
	_count	=	0;
}



















































EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END

