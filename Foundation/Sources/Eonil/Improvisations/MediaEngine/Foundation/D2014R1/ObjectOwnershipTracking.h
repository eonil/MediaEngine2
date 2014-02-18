//
//  ObjectOwnershipTracking.h
//  Foundation
//
//  Created by Hoon H. on 2/6/14.
//
//

#ifndef __Foundation__ObjectOwnershipTracking__
#define __Foundation__ObjectOwnershipTracking__


#include "../Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Foundation {
	
	inline namespace
	D2014R1			//	Distribution 2014, revision 1.
	{
		
#if	EONIL_MEDIA_ENGINE_DEBUG_MODE

		class
		TrackableObject
		{
			friend class			ReferencingPointer;
			friend class			UnknownTypeObjectTrackingPointerSlot;
			
			mutable std::multiset<void const*>	_dbg_virtual_ownership_list{};
			
			////
			
			auto	_dbg_virtual_retain_ownership_by(void const* owner) const -> void;
			auto	_dbg_virtual_release_ownership_by(void const* owner) const -> void;
			
		protected:
			TrackableObject() = default;
			
		public:
			~TrackableObject();
		};


		
		
		
		
		
		
		
		/*
		 With unique ownership object management, we need to make it alive
		 until all the client objects gone. Sometimes it's hard because;
		 
		 1.	The dereferencing to a dangling pointer happens very later then the
			object freed.
		 
		 2.	If a new object may take in the freed address, and then it may not
			crash! This is worst case because computation can go wrong without 
			sensible error.
		 
		 This class developed to get easier with this kind of error.
		 This behaves just like a bare pointer slot, but performs automatic 
		 retaining/releasing of ownership on the target object. This ownership 
		 management is virtual, so it doesn not trigger actual lifecycle management,
		 but the target object can track all the vitual owners, so it can notify
		 an error if it is going to be freed with active owners.
		 
		 Behaviors of this class are struct subset of a bare pointer.
		 It can be replaced with bare pointer without any modification. 
		 Anyway some operations which are not required to point remote object 
		 are not supported. (e.g. arithmetics)
		 */
		class
		UnknownTypeObjectTrackingPointerSlot
		{
			TrackableObject const*	_ptr{nullptr};
			
			auto	_retain_target_ptr_if_non_null() const -> void;
			auto	_release_target_ptr_if_non_null() const -> void;
			
		protected:
			UnknownTypeObjectTrackingPointerSlot(TrackableObject const* pointer);
			
			auto	operator=(UnknownTypeObjectTrackingPointerSlot copy) -> UnknownTypeObjectTrackingPointerSlot&;
			
			auto	operator==(UnknownTypeObjectTrackingPointerSlot const& slot) const -> bool;		//!	Performs pointer equality test.
			auto	operator!=(UnknownTypeObjectTrackingPointerSlot const& slot) const -> bool;		//!	Performs pointer inequality test.
			
			auto	operator*() const -> TrackableObject const&;
			auto	operator->() const -> TrackableObject const*;
			
		public:
			UnknownTypeObjectTrackingPointerSlot() = default;
			UnknownTypeObjectTrackingPointerSlot(UnknownTypeObjectTrackingPointerSlot const& origin);
			UnknownTypeObjectTrackingPointerSlot(UnknownTypeObjectTrackingPointerSlot&& origin);
			virtual ~UnknownTypeObjectTrackingPointerSlot();
		};

		
		
		
		
		
		
		
		
		/*!
		 A static type-chckable version of `UnknownTypeObjectTrackingPointerSlot` class.
		 */
		template <typename T>
		class
		GenericObjectTrackingPointerSlot final : public UnknownTypeObjectTrackingPointerSlot
		{
			
		public:
			GenericObjectTrackingPointerSlot() : UnknownTypeObjectTrackingPointerSlot()
			{
			}
			GenericObjectTrackingPointerSlot(T* pointer) : UnknownTypeObjectTrackingPointerSlot(pointer)
			{
				static_assert(std::is_base_of<TrackableObject, T>::value, "The pointing target must be a subclass of `TrackableObject`.");
			}
			GenericObjectTrackingPointerSlot(GenericObjectTrackingPointerSlot const& origin) : UnknownTypeObjectTrackingPointerSlot(origin)
			{
			}
			GenericObjectTrackingPointerSlot(GenericObjectTrackingPointerSlot&& origin) : UnknownTypeObjectTrackingPointerSlot(origin)
			{

			}
			virtual ~GenericObjectTrackingPointerSlot()
			{
			}
			
			auto
			operator=(GenericObjectTrackingPointerSlot const& copy) -> GenericObjectTrackingPointerSlot&
			{
				return	static_cast<GenericObjectTrackingPointerSlot&>(UnknownTypeObjectTrackingPointerSlot::operator=(copy));
			}
			
			auto
			operator==(GenericObjectTrackingPointerSlot const& slot) const -> bool
			{
				return	UnknownTypeObjectTrackingPointerSlot::operator==(slot);
			}
			auto
			operator!=(GenericObjectTrackingPointerSlot const& slot) const -> bool
			{
				return	UnknownTypeObjectTrackingPointerSlot::operator!=(slot);
			}
			
			auto
			operator*() const -> T const&
			{
				return	static_cast<T const&>(UnknownTypeObjectTrackingPointerSlot::operator*());
			}
			auto
			operator*() -> T&
			{
				return	static_cast<T&>(UnknownTypeObjectTrackingPointerSlot::operator*());
			}
			
			auto
			operator->() const -> T const*
			{
				return	static_cast<T const*>(UnknownTypeObjectTrackingPointerSlot::operator->());
			}
			auto
			operator->() -> T*
			{
				return	static_cast<T*>(UnknownTypeObjectTrackingPointerSlot::operator->());
			}
		};





		template <typename T> using	ptr	=	GenericObjectTrackingPointerSlot<T>;






		
#else



		class
		TrackableObject
		{
		protected:
			TrackableObject() = default;
		};



		template <typename T> using	ptr	=	T*;






		
		
#endif

	}
	
}}}}

#endif /* defined(__Foundation__ObjectOwnershipTracking__) */
