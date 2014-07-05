//
//  LocalCopyingAutomaticStorePointer.h
//  CommonUtility
//
//  Created by Hoon H. on 1/31/14.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#pragma once
#include <memory>
#include <limits>
#include <type_traits>
#include "Prelude.h"
EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_BEGIN

/*!
 Wraps type T as a pointer to itself to provide expression of const-
 correctness.
 
 @classdesign
 Usually we don't need to use this because just using local variable
 is far simpler. But that doesn't provide const-correctness. If you
 really need const-correctness for locally-copied variables, then use 
 this.
 
 @discussion
 If you copy this object, the internal data T will also be copied
 together. Actually the internal data T will be placed on stack.
 Anyway this has strictly pointer semantics, and all the operations
 are pointer behaviors.
 
 An instance of this class shouldn't be `nullptr` unless you force
 to make it with some dark magic.
 
 This provides const-correctness, but users still can copy the value
 itself. If you want to prevent arbitrary copying, privatize your copy
 constructor and set this class as a friend class.
 */
template <typename T>
class
LocalCopyingAutomaticStorePointer
{
	T	_local_copy_data	{};
	
//					typedef	typename std::conditional<std::is_const<T>::value, T const, T>::type	CCT;
	using	CONST_CORRECT_TYPE	=	typename std::conditional<std::is_const<T>::value, std::add_const<T>, T>::type;
	
public:
	LocalCopyingAutomaticStorePointer() = default;
	LocalCopyingAutomaticStorePointer(T const& value) : _local_copy_data(value)
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(&value != nullptr);
		}
	}
	LocalCopyingAutomaticStorePointer(T&& value) : _local_copy_data(value)
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(&value != nullptr);
		}
	}

	
	explicit
	operator
	T*() const
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(&_local_copy_data != nullptr);
		}
		
		////
		
		return	&_local_copy_data;
	}
	
	auto
	operator*() const -> T const&
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(&_local_copy_data != nullptr);
		}
		
		////
		
		return	_local_copy_data;
	}
	auto
	operator*() -> T&
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(&_local_copy_data != nullptr);
		}
		
		////
		
		return	_local_copy_data;
	}
	auto
	operator->() const -> T*
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(&_local_copy_data != nullptr);
		}
		
		////
		
		return	&_local_copy_data;
	}
	auto
	operator->() -> T*
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(&_local_copy_data != nullptr);
		}
		
		////
		
		return	&_local_copy_data;
	}
	
	/*!
	 Performs pointer equality.
	 If you need value comparison, compare dereferenced values.
	 */
	auto
	operator==(LocalCopyingAutomaticStorePointer const& p) const -> bool const
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(&_local_copy_data != nullptr);
		}
		
		////
		
		return	&_local_copy_data == &p;
	}
	auto
	operator!=(LocalCopyingAutomaticStorePointer const& p) const -> bool const
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(&_local_copy_data != nullptr);
		}
		
		////
		
		return	&_local_copy_data != &p;
	}
};

template <typename T>	using	local	=	LocalCopyingAutomaticStorePointer<T>;

EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_END