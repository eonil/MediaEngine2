//
//  MemoryStorage.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 14/4/29.
//
//

#pragma once

#include "../CommonRealtimeGameAlgorithmsCommon.h"
#include "../DebuggingTools/MemoryTracer.h"

EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_BEGIN






/*!
 A statically defined area of memory which does not perform initialization/cleanup automatically.
 You are responsible to do them.
 
 @discussion
 It is guaranteed that the pointer to this object is same to a pointer to content value.
 
 Where,
 
	MemoryStorage<T>	v1{};
 
 the given expression
 
	uintptr_t(&v1) == uintptr_t(&v1.value());

 is always true.
 
 This is checked by runtime assertion in debug build.
 
 Also, the size of this object will be exactly same with `T`.
 This class does not produce algined memory. Users are responsible to keep alignment.
 
 
 
 @discussion
 Copy and move cannot be defined by definition of this class because we cannot track current object
 aliveness state. So all copy/move related stuffs are prohibited by explicit delete.
 
 @discussion
 This class seems to be same with `std::aligned_union`, but using the class was harder than writing
 thi class to me due to desired behaviors.
 
 @exception
 All methods guarantees strong exception safety as long as the type `T` provides strong exception 
 safety for all of these methods. (no state change if there's an exception thrown)
 
 -	constructors
 -	destructors
 -	copy assignment
 -	move assignment
 
 @note
 In ARM processors, memory alignment is very sensitive issue because
 access to unaligned memory will cause an `EXC_ARM_DA_ALIGN` exception.
 
 In most cases, this won't be an issue because compiler handles alignment
 correctly. Compiler basically tries to align every structures to machine's
 native word size by padding empty space. If user specified explicit size
 (such as `char`), compiler will emit special instructions to access unaligned
 memory location. This costs more, but at least, the code will work correctly.
 
 The problem comes from direct memory accessing tricks. If compiler cannot
 determine the type of the object at compile-time, it's impossible to pad or
 emit special instructions. Unaligned memory access will happen eventually
 in this case. In this case, programmers are responsible to ensure the alignment
 because it's the programmers who hid the type information to compilers!
 
 It's hard to handle alignment manually and correctly. It's far better just letting
 the compiler do the job. The point is exposing the type to the compiler rather
 than erasing it.
 
 @warning
 This class is designed to be used in specially designed classes to manage object
 lifetime explicitly. This require explicit call of `terminate` function to trigger
 C++ destructor correctly, and it is very easy to forget. This effectively remove
 benefits of automatic resource management of RIIA.
 
 So **DO NOT USE this class** for daily coding. 
 */
template <typename T>
union
MemoryStorage
{
	friend class	MemoryStorageDebugginSupport;
	
	/*!
	 Default initializer of `unsigned char` will do nothing - memory will remain indeterminate values.
	 Value initialization will not be performed.
	 */
	using	MEM	=	std::array<unsigned char, sizeof(T)>;
	
	static_assert(sizeof(MEM) == sizeof(T), "MEM must be same sized with `T`.");
	
	MEM		_mem;		//	First member will be handled for ctor/dtor.
	T		_obj;		//	Second member will not be handled by ctor/dtor.
	
	/*
	 Second member is REQUIRED to provide type information to compiler at compile
	 time to gain proper memory alignment support by the compiler. This also removes
	 all `reinterpret_cast`.
	 */
	
public:
	MemoryStorage();
	MemoryStorage(MemoryStorage const&) = delete;
	MemoryStorage(MemoryStorage&&) = delete;
	~MemoryStorage();
	
	auto	operator=(MemoryStorage const&) -> MemoryStorage& = delete;
	auto	operator=(MemoryStorage&&) -> MemoryStorage& = delete;
	
	////
	
	auto	value() const -> T const&;
	auto	value() -> T&;
	
	template <typename... ARGS>
	auto	initialize(ARGS&&... args) -> void;
	auto	initialize(T const&) -> void;
	auto	initialize(T&&) -> void;
	auto	terminate() noexcept -> void;
	
private:
	auto	_halt_if_this_is_null() const -> void;
	auto	_halt_if_memory_layout_is_bad() const -> void;
};








template <typename T>
MemoryStorage<T>::MemoryStorage()
{
	/*
	 No initialization.
	 */
}
template <typename T>
MemoryStorage<T>::~MemoryStorage()
{
	/*
	 No cleanup.
	 */
}







template <typename T> auto
MemoryStorage<T>::value() const -> T const&
{
//	static_assert(sizeof(T) <= sizeof(MemoryStorage<T>), "Size of memory-storage must be equal to size of type `T`. If compiler does not support precise memory layout, it can't be used for this library. Some compiler may need using of some extra extensions.");
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		halt_if(uintptr_t(this) != uintptr_t(&_mem), "Bad memory layout.");
		halt_if(sizeof(MemoryStorage) != sizeof(T), "Bad memory layout.");
	}
	
	////
	
	return	_obj;
}
template <typename T> auto
MemoryStorage<T>::value() -> T&
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
		halt_if(uintptr_t(this) != uintptr_t(&_mem), "Bad memory layout.");
		halt_if(sizeof(MemoryStorage) != sizeof(T), "Bad memory layout.");
	}
	
	////
	
	return	_obj;
}

template <typename T>
template <typename ...ARGS> auto
MemoryStorage<T>::
initialize(ARGS&&... args) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
	}
	
	////
	
	new (&_obj) T(std::forward<ARGS>(args)...);
}
template <typename T> auto
MemoryStorage<T>::
initialize(T const& o) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
	}
	
	////
	
	new (&_obj) T(o);
}
template <typename T> auto
MemoryStorage<T>::
initialize(T&& o) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
	}
	
	////
	
	new (&_obj) T(std::move(o));
}
template <typename T> auto
MemoryStorage<T>::
terminate() noexcept -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_memory_layout_is_bad();
	}
	
	////
	
	_obj.~T();
}












template <typename T> auto
MemoryStorage<T>::
_halt_if_this_is_null() const -> void
{
	halt_if(this == nullptr, "You cannot call this method on `nullptr`.");
}
template <typename T> auto
MemoryStorage<T>::
_halt_if_memory_layout_is_bad() const -> void
{
	halt_if(uintptr_t(this) != uintptr_t(&_mem), "Bad memory layout.");
	halt_if(uintptr_t(this) != uintptr_t(&_obj), "Bad memory layout.");
}






























EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END

