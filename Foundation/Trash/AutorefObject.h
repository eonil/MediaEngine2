////
////  AutorefObject.h
////  EonilFoundation
////
////  Created by Hoon Hwangbo on 7/29/13.
////
////
//
//#ifndef __EonilFoundation__AutorefObject__
//#define __EonilFoundation__AutorefObject__
//
//
//#include <vector>
//#include <iostream>
//#include <utility>
//
//
//namespace
//Eonil
//{
//	namespace
//	Foundation
//	{
//		/*!
//		 Sharable object.
//		 
//		 `std::shared_ptr` has serious problem that we lose reference-count
//		 information if we get the object with bare pointer or reference.
//		 
//		 This object internalizes the reference-count so it's safe to pass
//		 the object using bare pointer or reference.
//		 
//		 */
//		class
//		AutorefObject
//		{
//			friend class	Doctor;
//			
//		public:
//			static size_t const	TOTAL_LIVE_OBJECT_COUNT();		//!	For debugging only. Not thread-safe.
//			
//			template<typename T>
//			class
//			Refbase
//			{
//			public:
//				Refbase();
//				Refbase(Refbase<T> const& ref);										//!	Copy ctor.
//				Refbase(Refbase<typename std::remove_const<T>::type>& refbase);		//!	Copy ctor from mutable form.
//				Refbase(T* const pointer);
////				template<typename T1>
////				Refbase(T1 const value);
//				virtual ~Refbase();
//				
//				Refbase const&		operator=(Refbase other);				//!	Copy-assign op.
//				
//				bool const			operator==(Refbase const& ref) const;	//!	Equality comparison.
//				bool const			operator!=(Refbase const& ref) const;	//!	Inequality comparison.
//				T const* const		operator->() const;
//				T* const			operator->();
//				T const&			operator*() const;
//				T&					operator*();
//				
//				T const* const		pointer() const;
//				T* const			pointer();
//				
//				T const&			value() const;
//				T&					value();
//				
//				T*		 			_ptr;
//			};
//			
////			/*!
////			 Lightweight immutable list of immutable references.
////			 Mainly designed to allow single value initialization 
////			 to vector.
////			 */
////			template<typename T>
////			class
////			RefListbase final
////			{
////			public:
////				RefListbase();											//!	Empty list. No atom.
////				RefListbase(Refbase<T> const ref);						//!	Single atom.
////				RefListbase(T* const ptr);								//!	Single atom..
////				RefListbase(std::vector<Refbase<T>> const refs);		//!	Multiple atoms.
////				
////				std::vector<Refbase<T>> const&	references() const;
////				
////			private:
////				std::vector<Refbase<T>>	_refs;
////			};
//			
//		public:
//			AutorefObject();
//			AutorefObject(AutorefObject const& obj);
//			virtual ~AutorefObject();
//			
//		private:
//			mutable size_t			_refc;
//			void	_addref() const;
//			void	_removeref() const;
//		};
//		
//		
//		template<typename T>
//		using Ref		=	AutorefObject::Refbase<T>;
//		
////		template<typename T>
////		using Reflist	=	AutorefObject::RefListbase<T>;
//	}
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//#pragma mark	-	Template Implementations
//
//
//namespace
//Eonil
//{
//	namespace
//	Foundation
//	{
//		
//		template<typename T>
//		AutorefObject::Refbase<T>::Refbase() : _ptr(nullptr)
//		{
//			static_assert(std::is_base_of<AutorefObject, T>::value, "");
//		}
//		
//		template<typename T>
//		AutorefObject::Refbase<T>::Refbase(Refbase<T> const& ref) : _ptr(ref._ptr)
//		{
//			static_assert(std::is_base_of<AutorefObject, T>::value, "");
//			
//			if (_ptr != nullptr)
//			{
//				_ptr->_addref();
//			}
//		}
//		
//		template<typename T>
//		AutorefObject::Refbase<T>::Refbase(Refbase<typename std::remove_const<T>::type>& ref) : _ptr(ref._ptr)
//		{
//			static_assert(std::is_base_of<AutorefObject, T>::value, "");
//			
//			if (_ptr != nullptr)
//			{
//				_ptr->_addref();
//			}
//		}
//		
//		template<typename T>
//		AutorefObject::Refbase<T>::Refbase(T* const pointer) : _ptr(pointer)
//		{
//			static_assert(std::is_base_of<AutorefObject, T>::value, "");
//			
//			if (_ptr)
//			{
//				_ptr->_addref();
//			}
//		}
//		//		template<typename T>
//		//		template<typename T1>
//		//		AutorefObject::Refbase<T>::Refbase(T1 const value) : _ptr(new T1(value))
//		//		{
//		//			static_assert(std::is_base_of<T, T1>::value, "The type `T1` must be a subclass of `T`.");
//		//			if (_ptr)
//		//			{
//		//				_ptr->_addref();
//		//			}
//		//		}
//		
//		template<typename T>
//		AutorefObject::Refbase<T>::~Refbase()
//		{
//			if (_ptr)
//			{
//				_ptr->_removeref();
//			}
//		}
//		
//		
//		
//		
//		
//		
//		
//		
//		
////		
////		template<typename T>
////		AutorefObject::RefListbase<T>::RefListbase() : _refs()
////		{
////		}
////		template<typename T>
////		AutorefObject::RefListbase<T>::RefListbase(T* const ptr) : _refs({Ref<T>(ptr)})
////		{
////		}
////		template<typename T>
////		AutorefObject::RefListbase<T>::RefListbase(Ref<T> const ref) : _refs({ref})
////		{
////		}
////		template<typename T>
////		AutorefObject::RefListbase<T>::RefListbase(std::vector<Ref<T>> const refs) : _refs(refs)
////		{
////		}
////		
////		template<typename T>
////		std::vector<Ref<T>> const&
////		AutorefObject::RefListbase<T>::references() const
////		{
////			return	_refs;
////		}
//		
//		
//		
//		
//		
//		
//		
//		
//		
//		
//		
//		
//		
//		template<typename T>
//		AutorefObject::Refbase<T> const&
//		AutorefObject::Refbase<T>::operator=(Refbase other)	//	Argument is copied implicitly.
//		{
//			std::swap(_ptr, other._ptr);
//			return	*this;
//		}
//		
//		template<typename T>
//		bool const
//		AutorefObject::Refbase<T>::operator==(Refbase const& ref) const
//		{
//			return	_ptr == ref._ptr;
//		}
//		
//		template<typename T>
//		bool const
//		AutorefObject::Refbase<T>::operator!=(Refbase const& ref) const
//		{
//			return	_ptr != ref._ptr;
//		}
//		
//		template<typename T>
//		T const* const
//		AutorefObject::Refbase<T>::operator->() const
//		{
//			return	_ptr;
//		}
//		template<typename T>
//		T* const
//		AutorefObject::Refbase<T>::operator->()
//		{
//			return	_ptr;
//		}
//		
//		template<typename T>
//		T const&
//		AutorefObject::Refbase<T>::operator*() const
//		{
//			return	*_ptr;
//		}
//		template<typename T>
//		T&
//		AutorefObject::Refbase<T>::operator*()
//		{
//			return	*_ptr;
//		}
//		
//		
//		
//		
//		template<typename T>
//		T const* const
//		AutorefObject::Refbase<T>::pointer() const
//		{
//			return	_ptr;
//		}
//		template<typename T>
//		T* const
//		AutorefObject::Refbase<T>::pointer()
//		{
//			return	_ptr;
//		}
//		
//		template<typename T>
//		T const&
//		AutorefObject::Refbase<T>::value() const
//		{
//			return	*(T*)_ptr;
//		}
//		
//		template<typename T>
//		T&
//		AutorefObject::Refbase<T>::value()
//		{
//			return	*(T*)_ptr;
//		}
//	}
//}
//
//
//#endif /* defined(__EonilFoundation__AutorefObject__) */
