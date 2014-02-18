////
////  Maybe.h
////  EonilFoundation
////
////  Created by Hoon Hwangbo on 6/3/13.
////
////
//
//#ifndef __EonilFoundation__Maybe__
//#define __EonilFoundation__Maybe__
//
//#include <memory>
//#include <utility>
//
//namespace
//Eonil
//{
//	namespace
//	Foundation
//	{
//		
//		/*!
//		 Immutable optional value container.
//		 */
//		template<typename T>
//		class
//		Maybe
//		{
//			
//		public:
//			
//			struct
//			Factory
//			{
//				static Maybe<T> const	null();
////				static Maybe<T> const	valueByCopyingValue(T const value);
//				static Maybe<T> const	valueByCopyingValue(T const& reference);
//				static Maybe<T> const	valueByCopyingValue(T const* const pointer);
//				static Maybe<T> const	valueByReferencingValue(T const& reference);
//				static Maybe<T> const	valueByReferencingValue(T const* const pointer);
//				
//				Factory()	=	delete;
//			};
//			
//			Maybe(std::nullptr_t const null) : _ptr(nullptr)
//			{
//			}
//			Maybe(T const value) : _ptr(new T(value))
//			{
//			}
////			Maybe(Maybe<T> const& m) : _ptr(new T(m.value()))
////			{
////			}
////			
////			Maybe<T>&
////			operator=(Maybe<T> m)
////			{
////				std::swap(_ptr, m._ptr);
////				return	*this;
////			}
//			
//			bool const
//			operator==(decltype(nullptr) null)
//			{
//				return	_ptr == nullptr;
//			}
//			bool const
//			operator!=(decltype(nullptr) null)
//			{
//				return	_ptr != nullptr;
//			}
//			
//			T const&
//			value() const
//			{
//				EE_ASSERT(_ptr != nullptr);
//				return	*_ptr;
//			}
//			
//		private:
//			std::shared_ptr<T>	_ptr	=	nullptr;
//		};
//	}
//}
//namespace
//Eonil
//{
//	namespace
//	Foundation
//	{
//		template<typename T>
//		Maybe<T> const
//		Maybe<T>::Factory::null()
//		{
//			return	nullptr;
//		}
////		template<typename T>
////		Maybe<T> const
////		Maybe<T>::Factory::valueByCopyingValue(const T value)
////		{
////			return	Maybe<T>(value);
////		}
//		template<typename T>
//		Maybe<T> const
//		Maybe<T>::Factory::valueByCopyingValue(const T &reference)
//		{
//			return	Maybe<T>(reference);
//		}
//		template<typename T>
//		Maybe<T> const
//		Maybe<T>::Factory::valueByCopyingValue(const T *const pointer)
//		{
//			return	valueByCopyingValue(*pointer);
//		}
//		
//		template<typename T>
//		Maybe<T> const
//		Maybe<T>::Factory::valueByReferencingValue(const T &reference)
//		{
//			return	valueByReferencingValue(&reference);
//		}
//		template<typename T>
//		Maybe<T> const
//		Maybe<T>::Factory::valueByReferencingValue(const T *const pointer)
//		{
//			return	Maybe<T>(pointer);
//		}
//	}
//}
//
//
//
//#endif /* defined(__EonilFoundation__Maybe__) */
