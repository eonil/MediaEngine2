//
//  ObjectOwnershipTracking.cpp
//  Foundation
//
//  Created by Hoon H. on 2/6/14.
//
//

#include "ObjectOwnershipTracking.h"
#include <iostream>
EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_BEGIN
inline namespace
D2014R1			//	Distribution 2014, revision 1.
{

#if	EONIL_MEDIA_ENGINE_DEBUG_MODE
	
	
	
	auto TrackableObject::
	_dbg_virtual_retain_ownership_by(void const* owner) const -> void
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(owner != nullptr);
		}
		
		////
		
		_dbg_virtual_ownership_list.insert(owner);
//			std::cout << "_dbg_virtual_retain_ownership_by, refs = " << std::to_string(_dbg_virtual_ownership_list.size()) << "\n";
	}
	auto TrackableObject::
	_dbg_virtual_release_ownership_by(void const* owner) const -> void
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(owner != nullptr);
			err9_converted_legacy_assertion(_dbg_virtual_ownership_list.count(owner) > 0);
		}
		
		////
		
		_dbg_virtual_ownership_list.erase(owner);
//			std::cout << "_dbg_virtual_release_ownership_by, refs = " << std::to_string(_dbg_virtual_ownership_list.size()) << "\n";
	}
	
	TrackableObject::~TrackableObject()
	{
		std::cout << "trackable object is dying, refs = " << std::to_string(_dbg_virtual_ownership_list.size()) << "\n";
		if (_dbg_virtual_ownership_list.size() > 0)
		{
			err9_legacy_error_always("There're active virtual owners tracked by `GenericObjectTrackingPointerSlot<T>`. This means current object is being freed too early.");
		}
	}
	

	
	
	
	
	
	
	
	UnknownTypeObjectTrackingPointerSlot::
	UnknownTypeObjectTrackingPointerSlot(TrackableObject const* pointer) : _ptr(pointer)
	{
		_retain_target_ptr_if_non_null();
	}
	UnknownTypeObjectTrackingPointerSlot::
	UnknownTypeObjectTrackingPointerSlot(UnknownTypeObjectTrackingPointerSlot const& origin) : _ptr(origin._ptr)
	{
		_retain_target_ptr_if_non_null();
	}
	UnknownTypeObjectTrackingPointerSlot::
	UnknownTypeObjectTrackingPointerSlot(UnknownTypeObjectTrackingPointerSlot&& origin)
	{
		origin._release_target_ptr_if_non_null();
		std::swap(_ptr, origin._ptr);
		_retain_target_ptr_if_non_null();
	}

	UnknownTypeObjectTrackingPointerSlot::
	~UnknownTypeObjectTrackingPointerSlot()
	{
		_release_target_ptr_if_non_null();
	}
		
		
	
	
	
	
	
	
	auto UnknownTypeObjectTrackingPointerSlot::
	_retain_target_ptr_if_non_null() const -> void
	{
		if (_ptr != nullptr)
		{
			_ptr->_dbg_virtual_retain_ownership_by(this);
		}
	}
	auto UnknownTypeObjectTrackingPointerSlot::
	_release_target_ptr_if_non_null() const -> void
	{
		if (_ptr != nullptr)
		{
			_ptr->_dbg_virtual_release_ownership_by(this);
		}
	}

	
	
	
		
		
		
		
		
	auto UnknownTypeObjectTrackingPointerSlot::
	operator=(UnknownTypeObjectTrackingPointerSlot copy) -> UnknownTypeObjectTrackingPointerSlot&
	{
		copy._release_target_ptr_if_non_null();
		_release_target_ptr_if_non_null();
		
		std::swap(_ptr, copy._ptr);
		
		copy._retain_target_ptr_if_non_null();
		_retain_target_ptr_if_non_null();
		
		return	*this;
	}
	
	auto UnknownTypeObjectTrackingPointerSlot::
	operator==(const UnknownTypeObjectTrackingPointerSlot &slot) const -> bool
	{
		return	_ptr == slot._ptr;
	}
	auto UnknownTypeObjectTrackingPointerSlot::
	operator!=(const UnknownTypeObjectTrackingPointerSlot &slot) const -> bool
	{
		return	_ptr != slot._ptr;
	}
	
	
	
	auto UnknownTypeObjectTrackingPointerSlot::
	operator*() const -> TrackableObject const&
	{
		return	*_ptr;
	}
	auto UnknownTypeObjectTrackingPointerSlot::
	operator->() const -> TrackableObject const*
	{
		return	_ptr;
	}
	
		
	
	
#endif

}
EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_END
