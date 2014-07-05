//
//  ObjectInstanceAddressTracker.h
//  CommonUtility
//
//  Created by Hoon H. on 12/9/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#pragma once
#include "../Prelude.h"
EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_BEGIN








/*!
 Global space debugging helper.
 */
template<typename T>
class
ObjectInstanceAddressTracker
{
	static std::list<T const*>& _ptrs()
	{
		static std::list<T const*>*	_ptr_to_ptrs	=	nullptr;
		
		if (_ptr_to_ptrs == nullptr)
		{
			_ptr_to_ptrs	=	new std::list<T const*>();
		}
		return	*_ptr_to_ptrs;
	}
	
public:
	static void
	registerObjectAddress(T const* const addressOfObject)
	{
		if (containsObjectAddress(addressOfObject))
		{
			fail("The address is already registered.");
		}
		_ptrs().push_back(addressOfObject);
	}
	
	static void
	unregisterObjectAddress(T const* const addressOfObject)
	{
		auto	it	=	std::find(_ptrs().begin(), _ptrs().end(), addressOfObject);
		if (it == _ptrs().end())
		{
			fail("The address of the object is not registered.");
		}
		_ptrs().erase(it);
	}
	static bool const
	containsObjectAddress(T const* const addressOfObject)
	{
		auto	it	=	std::find(_ptrs().begin(), _ptrs().end(), addressOfObject);
		bool	ok	=	it != _ptrs().end();
		return	ok;
	}
	static list<T const*> const
	allObjectAddresses()
	{
		return	_ptrs();
	}
};


















EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_END
