////
////  _Legacy2013Compat.h
////  Graphics
////
////  Created by Hoon H. on 2/7/14.
////
////
//
//#ifndef __Graphics___Legacy2013Compat__
//#define __Graphics___Legacy2013Compat__
//
//#include "../Common.h"
//#include "ServerObjectProxy.h"
//
//INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN
//	
//	namespace
//	Server
//	{
//		
//		/*!
//		 Legacy 2013 code uses shared ownership, and all of its client code also does.
//		 It's hard to change all the codebase at once to unique ownership base, so this
//		 class will aid this by adapting shared ownership on unique server-side object
//		 proxy object.
//		 */
//		
//		
//		
//		template <typename T>
//		class
//		_Legacy2013_SharingBox
//		{
////			static_assert(std::is_base_of<ServerObjectProxy, T>::value, "The target type `T` must be a subclass of `ServerObjectProxy` class.");
//			
//			sptr<T>	_sptr{nullptr};
//			
//		public:
//			_Legacy2013_SharingBox() = default;
//			_Legacy2013_SharingBox(T* pointerToObject) : _sptr(pointerToObject)
//			{
//			}
//			
//			auto
//			operator==(std::nullptr_t const& null) const -> bool
//			{
//				return	_sptr == null;
//			}
//			auto
//			operator!=(std::nullptr_t const& null) const -> bool
//			{
//				return	_sptr != null;
//			}
//			auto
//			operator*() const -> T const&
//			{
//				return	*_sptr;
//			}
//			auto
//			operator*() -> T&
//			{
//				return	*_sptr;
//			}
//			
//			auto
//			operator->() const -> T const*
//			{
//				return	_sptr.get();
//			}
//			auto
//			operator->() -> T*
//			{
//				return	_sptr.get();
//			}
//		};
//		
//		
//	}
//	
//}}}}
//
//#endif /* defined(__Graphics___Legacy2013Compat__) */
