//
//  ObjectSlot.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 2014/05/11.
//
//

#pragma once
#include "../CommonRealtimeGameAlgorithmsCommon.h"
#include "MemoryStorage.h"
EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_BEGIN













/*!
 A `MemoryStorage` with explicit occupation flag and copy/move support.
 
 @discussion
 This is designed independent sole instance.
 
 @exception
 All methods guarantees strong exception safety as long as the type `T` provides strong exception
 safety for all of these methods. (no state change if there's an exception thrown)
 
 -	constructors
 -	destructors
 -	copy assignment
 -	move assignment
 
 @note
 The only difference with the `T` itself is, init/term operation is fully manual, and
 there's a dedicated extra boolean flag to check initialization status.
 If you delete this object without calling `terminate` method, the destructor of `T`
 will not be called. That's a wrong program, and you're responsible to call the
 `terminate` method. Even for types with no destructor code, you must call `terminate`
 always.
 
 @warning
 Do not use this class for usual object management. This class is designed specially
 for specific classes. You should subclass to ensure some guarantee.
 
 @templatefield
 ALIGNMENT
 You can try forcing memory packing by overriding this to `false`.
 Anyway packing is not guaranteed, and may not be supported in some compilers. Also,
 packing may decrease performance A LOT if misused. So be careful when you use packing.
 */
template <typename T, bool const ALIGNMENT = true>
class
ObjectSlot : private ExceptionSupportTools
{
public:
	class
	Exception : public std::logic_error
	{
	public:
		using	logic_error::logic_error;
	};
	
public:
	ObjectSlot() = default;
	ObjectSlot(ObjectSlot const&);
	ObjectSlot(ObjectSlot&&);
	~ObjectSlot();
	
	auto	operator=(ObjectSlot const&) -> ObjectSlot&;
	auto	operator=(ObjectSlot&&) -> ObjectSlot&;
	
	////
	
	auto	occupation() const -> bool;
	
//	auto	data() const -> T const*;				//!	Returns just address of the value memory regardless of occupancy. This is not appropriate method.
//	auto	data() -> T*;							//!	Returns just address of the value memory regardless of occupancy. This is not appropriate method.
	
	auto	value() const -> T const&;
	auto	value() -> T&;
	
	template <typename... ARGS>
	auto	initialize(ARGS&&... args) -> void;
	auto	initialize(T&&) -> void;
	auto	terminate() -> void;
	
public:
	/*!
	 Gets proper pointer address to a `ObjectSlot` from given pointer address to `T`
	 by assuming the `T` object is placed in an `ObjectSlot` object.
	 
	 @discussion
	 The memory for the object (`_mem`) is expected to be at offset `0`.
	 But I am not sure that whether that is guaranteed by the standard,
	 so this function is provided.
	 
	 This is all about address calculation, and does not check object validity.
	 */
	static auto		addressOfSlotForValuePointer(T const*) -> ObjectSlot const*;
//	static auto		resolveAddressOfValue(ObjectSlot const*) -> T const*;		//	Just use `value` method instead of this indirection.
	
	
private:
	friend class	ObjectSlotDebugginSupport;
	
	struct
	State
	{
		MemoryStorage<T>	memory			=	{};
		bool				occupation		=	false;
	};
	struct
	PackedState : State
	{
	}
	__attribute__((packed));
	
	using	STATE	=	typename std::conditional<ALIGNMENT, State, PackedState>::type;
	
	////
	
	STATE	_state	=	{};
	
	auto	_halt_if_memory_layout_is_bad() const -> void;
};





















template <typename T, bool const A>
ObjectSlot<T,A>::
ObjectSlot(ObjectSlot const& o)
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
ObjectSlot<T,A>::
ObjectSlot(ObjectSlot&& o)
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
ObjectSlot<T,A>::
~ObjectSlot()
{
	/*
	 This assertion is only for debugging convenience.
	 */
	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(not _state.occupation, "This slot is going to be destroyed, but still being occupied.");
}


template <typename T, bool const A>
auto
ObjectSlot<T,A>::
operator=(const ObjectSlot<T,A> &o) -> ObjectSlot&
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
		if (_state.occupation)
		{
			terminate();
		}
		if (o._state.occupation)
		{
			initialize(o.value());
		}
	}
	return	*this;
}
template <typename T, bool const A>
auto
ObjectSlot<T,A>::
operator=(ObjectSlot<T,A> &&o) -> ObjectSlot&
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
		if (_state.occupation)
		{
			terminate();
		}
		if (o._state.occupation)
		{
			initialize(std::move(o.value()));
		}
	}
	return	*this;
}
template <typename T, bool const A>
auto
ObjectSlot<T,A>::
occupation() const -> bool
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
	}
	
	////
	
	return	_state.occupation;
}
//template <typename T, bool const A>
//auto
//ObjectSlot<T,A>::data() const -> T const*
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
//template <typename T, bool const A>
//auto
//ObjectSlot<T,A>::data() -> T*
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
template <typename T, bool const A>
auto
ObjectSlot<T,A>::
value() const -> T const&
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(not _state.occupation, "This object-slot is not occupied yet.");
	}
	
	////
	
	return	_state.memory.value();
}
template <typename T, bool const A>
auto
ObjectSlot<T,A>::
value() -> T&
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(not _state.occupation, "This object-slot is not occupied yet.");
	}
	
	////
	
	return	_state.memory.value();
}

template <typename T, bool const A>
template <typename ...ARGS>
auto
ObjectSlot<T,A>::
initialize(ARGS&&... args) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(_state.occupation, "This object-slot is already occupied.");
	}
	
	////
	
	_state.memory.initialize(std::forward<ARGS>(args)...);
	_state.occupation	=	true;
}
template <typename T, bool const A>
auto
ObjectSlot<T,A>::
initialize(T&& o) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(_state.occupation, "This object-slot is already occupied.");
	}
	
	////
	
	_state.memory.initialize(std::move(o));
	_state.occupation	=	true;
}
template <typename T, bool const A>
auto
ObjectSlot<T,A>::
terminate() -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		error_if(not _state.occupation, "This object-slot is not occupied yet.");
	}
	
	////
	
	_state.occupation	=	false;
	_state.memory.terminate();
}



template <typename T, bool const A>
auto
ObjectSlot<T,A>::
addressOfSlotForValuePointer(const T *o) -> ObjectSlot const*
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		error_if(o == nullptr, "`nullptr` is not supported.");
	}
	
	////
	
	return	reinterpret_cast<ObjectSlot const*>(o);
	
	/*
	 Trick to get slot pointer from value pointer.
	 Kept for legacy archive purpose.
	 */
	//	static constexpr Size const		byte_offset		=	offsetof(ObjectSlot, _mem);
	//	uint8_t const*					target_ptr		=	reinterpret_cast<uint8_t const*>(o);
	//	uint8_t const*					slot_ptr1		=	target_ptr - byte_offset;
	//	ObjectSlot const*				slot_ptr2		=	reinterpret_cast<ObjectSlot const*>(slot_ptr1);
	//
	//	if (USE_EXCEPTION_CHECKINGS)
	//	{
	//		halt_if(target_ptr != slot_ptr1);
	//	}
	//
	//	return	slot_ptr2;
}




















template <typename T, bool const A>
auto
ObjectSlot<T,A>::
_halt_if_memory_layout_is_bad() const -> void
{
	halt_if(uintptr_t(this) != uintptr_t(&_state.memory), "Bad memory layout.");
}





//#if EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_MODE
//struct
//ObjectSlotDebugginSupport
//{
//	template <typename T, bool const A>
//	static inline auto
//	get_value_ptr_without_check(ObjectSlot<T,A>& o) -> T&
// 	{
//		return	o._mem.value();
//	}
//};
//#endif










EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END

