
//
//  opt.h
//  EonilScript2
//
//  Created by Hoon H. on 2014/06/17.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#pragma once
#include <array>
#include "common.h"
#include "error.h"
//#include "dbg.h"
EONIL_COMMONUTILITY_AGE2_NAMESPACE_BEGIN




/*!
 @classdesign
 If you move out the value, then the object will become null-state just like
 @c std::unique_ptr . Comparing null-state object with @c std::nullptr returns
 @c true . This is guaranteed behavior and you can safely rely on this.
 */
template <typename T>
class
OptionalValue final
{
	static_assert(std::is_convertible<T, std::nullptr_t>::value == false, "If the type `T` is implicitly convertible to `std::nullptr_t`, then it is not allowed.");
//	static_assert(std::is_convertible<T, bool>::value == false, "If the type `T` is implicitly convertible to `bool`, then it should use dedicated specialization.");

	////
	
	public:
	OptionalValue(std::nullptr_t const&);
	OptionalValue(T const&);
	OptionalValue(T&&);

	public:
	OptionalValue() = delete;
	OptionalValue(OptionalValue const&);
	OptionalValue(OptionalValue&&);
	~OptionalValue();
	
	public:
	auto	operator=(OptionalValue const&) -> OptionalValue&;
	auto	operator=(OptionalValue&&) -> OptionalValue&;
	auto	operator*() const -> T const&;
	auto	operator*() -> T&;
	
	public:
	auto	operator==(std::nullptr_t const&) const -> bool;
	auto	operator!=(std::nullptr_t const&) const -> bool;
	auto	ready() const -> bool;
	auto	value() const -> T const&;
	
	private:
	union
	container
	{
		std::array<uint8_t,sizeof(T)>	bytes;
		T								value;
		
		container()
		{
		}
		~container()
		{
		}
	};
	
	bool		_ready	=	false;
	container	_cont	=	{};
	
//	dbg			_dbg	=	{};
};


template <typename T>
inline
OptionalValue<T>::OptionalValue(std::nullptr_t const&)
{
	_ready	=	false;
}
template <typename T>
inline
OptionalValue<T>::OptionalValue(T const& v1)
{
	_ready	=	true;
	new (&_cont.value) T(v1);
}
template <typename T>
inline
OptionalValue<T>::OptionalValue(T&& v1)
{
	_ready		=	true;
	new (&_cont.value) T(std::move(v1));
}



template <typename T>
inline
OptionalValue<T>::OptionalValue(OptionalValue const& opt1)
{
	if (opt1._ready)
	{
		_ready		=	opt1._ready;
		new (&_cont.value) T(opt1._cont.value);
	}
}
template <typename T>
inline
OptionalValue<T>::OptionalValue(OptionalValue&& opt1)
{
	if (opt1._ready)
	{
		_ready		=	opt1._ready;
		new (&_cont.value) T(std::move(opt1._cont.value));
		
		opt1._ready	=	false;
		opt1._cont.value.~T();
	}
}
template <typename T>
inline
OptionalValue<T>::~OptionalValue()
{
	if (_ready)
	{
		_cont.value.~T();
	}
}
template <typename T>
inline auto
OptionalValue<T>::operator=(OptionalValue const& opt1) -> OptionalValue&
{
	if (this != &opt1)
	{
		if (_ready)
		{
			this->~OptionalValue();
		}
		if (opt1._ready)
		{
			new (this) OptionalValue(opt1);
		}
	}
	return	*this;
}
template <typename T>
inline auto
OptionalValue<T>::operator=(OptionalValue&& opt1) -> OptionalValue&
{
	if (this != &opt1)
	{
		if (_ready)
		{

		}
		if (opt1._ready)
		{
			new (this) OptionalValue(std::move(opt1));
		}
	}
	return	*this;
}




template <typename T>
inline auto
OptionalValue<T>::operator==(std::nullptr_t const&) const -> bool
{
	return	not _ready;
}
template <typename T>
inline auto
OptionalValue<T>::operator!=(std::nullptr_t const&) const -> bool
{
	return	_ready;
}
template <typename T>
inline auto
OptionalValue<T>::operator*() const -> T const&
{
	err2_recoverable_program_state_is_not_proper_for_this_command_if(not _ready);
	
	return	_cont.value;
}
template <typename T>
inline auto
OptionalValue<T>::operator*() -> T&
{
	err2_recoverable_program_state_is_not_proper_for_this_command_if(not _ready);
	
	return	_cont.value;
}




template <typename T>
inline auto
OptionalValue<T>::ready() const -> bool
{
	return	_ready;
}
template <typename T>
inline auto
OptionalValue<T>::value() const -> T const&
{
	err2_recoverable_program_state_is_not_proper_for_this_command_if(not _ready);
	
	return	_cont.value;
}






template <typename T>		using	opt	=	OptionalValue<T>;












EONIL_COMMONUTILITY_AGE2_NAMESPACE_END