//
//  ListAtomSlot.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 14/4/29.
//
//

#pragma once
#include "../CommonRealtimeGameAlgorithmsCommon.h"
#include "ObjectSlot.h"
EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_BEGIN













/*!
 A `MemoryStorage` with explicit occupation flag and copy/move support.
 
 @discussion
 This is designed to be laid out consecutively. Iterating is provided by `ListAtomSlotIterator`.
 Last slot must be a sential by being marked with sentinel flag to provide iteration properly.
 
 @exception
 All methods guarantees strong exception safety as long as the type `T` provides strong exception
 safety for all of these methods. (no state change if there's an exception thrown)
 
 -	constructors
 -	destructors
 -	copy assignment
 -	move assignment
 
 @note
 The only difference with the `T` itself is, init/term operation is fully manual.
 If you delete this object without calling `terminate` method, the destructor of `T`
 will not be called. That's usually wrong program, and you're responsible to call the
 `terminate` method.
 
 @warning
 Do not use this class for usual object management. This class is designed specially
 for specific classes.
 
 @templatefield
 ALIGNMENT
 You can force memory packing by setting this to `false`.
 */
template <typename T, bool const ALIGNMENT = true>
class
ListAtomSlot
{
public:
	class
	Exception : public std::logic_error
	{
	public:
		using	logic_error::logic_error;
	};
	
public:
	ListAtomSlot() = default;
	ListAtomSlot(ListAtomSlot const&);
	ListAtomSlot(ListAtomSlot&&);
	~ListAtomSlot();
	
	auto	operator=(ListAtomSlot const&) -> ListAtomSlot&;
	auto	operator=(ListAtomSlot&&) -> ListAtomSlot&;
	
	////
	
	auto	occupation() const -> bool;
	
	auto	value() const -> T const&;
	auto	value() -> T&;
	
	template <typename... ARGS>
	auto	initialize(ARGS&&... args) -> void;
	auto	initialize(T&&) -> void;
	auto	terminate() -> void;
	
	auto	sentinel() const -> bool;
	auto	sentinelize() -> void;
	
public:
	/*!
	 Gets proper pointer address to a `ListAtomSlot` from given pointer address to `T`
	 by assuming the `T` object is placed in an `ListAtomSlot` object.
	 
	 @discussion
	 The memory for the object (`_mem`) is expected to be at offset `0`.
	 But I am not sure that whether that is guaranteed by the standard,
	 so this function is provided. 
	 
	 This is all about address calculation, and does not check object validity.
	 */
	static auto		addressOfSlotForValuePointer(T const*) -> ListAtomSlot const*;
//	static auto		resolveAddressOfValue(ListAtomSlot const*) -> T const*;		//	Just use `value` method instead of this indirection.
	
	
private:
	friend class	ListAtomSlotDebugginSupport;
	
	using	SLOT	=	ObjectSlot<T,false>;
	struct
	State
	{
		SLOT	slot	=	{};
		bool	last	=	false;
		
		State() = default;
		State(bool const last) : last(last) {}
	}
	__attribute__((aligned(alignof(typename std::aligned_storage<sizeof(SLOT)>::type))));
	
	struct
	PackedState : State
	{
	}
	__attribute__((packed));
	
	using	STATE	=	typename std::conditional<ALIGNMENT, State, PackedState>::type;
	
	////
	
	STATE	_state	=	{};
	
	auto	_halt_if_memory_layout_is_bad() const -> void;
	auto
	_halt_if_this_is_null() const -> void
	{
		halt_if(this == nullptr, "This object pointer is null.");
	}
};





















template <typename T, bool const A>
ListAtomSlot<T,A>::
ListAtomSlot(ListAtomSlot const& o) : _state(o._state.last)
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(&o == nullptr, "The supplied pointer shouldn't be `nullptr`.");
	}
	
	////
	
	if (o.occupation())
	{
		initialize(o.value());
	}
}
template <typename T, bool const A>
ListAtomSlot<T,A>::
ListAtomSlot(ListAtomSlot&& o) : _state(std::move(o._state.last))
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(&o == nullptr, "The supplied pointer shouldn't be `nullptr`.");
	}
	
	////
	
	if (o.occupation())
	{
		initialize(std::move(o.value()));
	}
	
	/*
	 The `o` will be left as occupied and live state with no guts.
	 Somewhere else in the program will `terminate` the `o` eventually.
	 */
}
template <typename T, bool const A>
ListAtomSlot<T,A>::
~ListAtomSlot()
{
	/*
	 This assertion is only for debugging convenience.
	 */
	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(not _state.slot.occupation(), "This slot is going to be destroyed, but still being occupied.");
}


template <typename T, bool const A>
auto
ListAtomSlot<T,A>::operator=(const ListAtomSlot<T,A> &o) -> ListAtomSlot&
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(&o == nullptr, "Cannot copy-assign from a value pointed by a `nullptr`.");
	}
	
	////
	
	if (&o == this)
	{
		//	Nothing to do.
	}
	else
	{
		if (_state.slot.occupation())
		{
			terminate();
		}
		if (o._state.slot.occupation())
		{
			initialize(o.value());
		}
		
		_state.last	=	o._state.last;
	}
	return	*this;
}
template <typename T, bool const A>
auto
ListAtomSlot<T,A>::operator=(ListAtomSlot<T,A> &&o) -> ListAtomSlot&
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(&o == nullptr, "Cannot move-assign from a value pointed by a `nullptr`.");
	}
	
	////
	
	if (&o == this)
	{
		//	Nothing to do.
	}
	else
	{
		if (_state.slot.occupation())
		{
			terminate();
		}
		if (o._state.slot.occupation())
		{
			initialize(std::move(o.value()));
		}
		
		_state.last		=	std::move(o._state.last);
	}
	return	*this;
}
template <typename T, bool const A> auto
ListAtomSlot<T,A>::occupation() const -> bool
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
	}
	
	////
	
	return	_state.slot.occupation();
}
//template <typename T, bool const A> auto
//ListAtomSlot<T,A>::data() const -> T const*
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//	}
//	
//	////
//	
//	return	&_mem.value();
//}
//template <typename T, bool const A> auto
//ListAtomSlot<T,A>::data() -> T*
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//	}
//	
//	////
//	
//	return	&_mem.value();
//}
template <typename T, bool const A> auto
ListAtomSlot<T,A>::value() const -> T const&
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(not _state.slot.occupation(), "This list-atom-slot is not occupied yet.");
	}
	
	////
	
	return	_state.slot.value();
}
template <typename T, bool const A> auto
ListAtomSlot<T,A>::value() -> T&
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(not _state.slot.occupation(), "This list-atom-slot is not occupied yet.");
	}
	
	////
	
	return	_state.slot.value();
}

template <typename T, bool const A>
template <typename ...ARGS> auto
ListAtomSlot<T,A>::
initialize(ARGS&&... args) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(_state.slot.occupation(), "This list-atom-slot is already occupied.");
	}
	
	////
	
	_state.slot.initialize(std::forward<ARGS>(args)...);
}
template <typename T, bool const A> auto
ListAtomSlot<T,A>::
initialize(T&& o) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(_state.slot.occupation(), "This list-atom-slot is already occupied.");
	}
	
	////
	
	_state.slot.initialize(std::move(o));
}
template <typename T, bool const A> auto
ListAtomSlot<T,A>::
terminate() -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(not _state.slot.occupation(), "This list-atom-slot is not occupied yet.");
	}
	
	////
	
	_state.slot.terminate();
}
template <typename T, bool const A> auto
ListAtomSlot<T,A>::
sentinel() const -> bool
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
	}
	
	////
	
	return	_state.last;
}

template <typename T, bool const A> auto
ListAtomSlot<T,A>::
sentinelize() -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(_state.last, "This list-atom-slot is alreday a sentinel.");
	}
	
	////
	
	_state.last	=	true;
}


template <typename T, bool const A> auto
ListAtomSlot<T,A>::
addressOfSlotForValuePointer(const T *o) -> ListAtomSlot const*
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		error_if(o == nullptr, "`nullptr` is not supported.");
	}
	
	////
	
	return	reinterpret_cast<ListAtomSlot const*>(o);
	
	/*
	 Trick to get slot pointer from value pointer.
	 Kept for legacy archive purpose.
	 */
//	static constexpr Size const		byte_offset		=	offsetof(ListAtomSlot, _mem);
//	uint8_t const*					target_ptr		=	reinterpret_cast<uint8_t const*>(o);
//	uint8_t const*					slot_ptr1		=	target_ptr - byte_offset;
//	ListAtomSlot const*				slot_ptr2		=	reinterpret_cast<ListAtomSlot const*>(slot_ptr1);
//	
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		halt_if(target_ptr != slot_ptr1);
//	}
//
//	return	slot_ptr2;
}




















template <typename T, bool const A> auto
ListAtomSlot<T,A>::
_halt_if_memory_layout_is_bad() const -> void
{
	halt_if(uintptr_t(this) != uintptr_t(&_state.slot), "Bad memory layout.");
}





//#if EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_MODE
//struct
//ListAtomSlotDebugginSupport
//{
//	template <typename T, bool const A>
//	static inline auto
//	get_value_ptr_without_check(ListAtomSlot<T,A>& o) -> T&
// 	{
//		return	o._mem.value();
//	}
//};
//#endif










EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END

