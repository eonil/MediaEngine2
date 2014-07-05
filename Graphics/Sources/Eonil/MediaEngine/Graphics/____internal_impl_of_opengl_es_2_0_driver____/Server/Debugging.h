////
////  Debugging.h
////  Graphics
////
////  Created by Hoon H. on 2/7/14.
////
////
//
//#pragma once
//#include "../Declarations.h"
//INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN
//
//namespace
//Server
//{
//	
//	
//	namespace
//	Debugging
//	{
//		template <typename T>
//		class
//		InstanceCounter
//		{
//			std::set<T const*>	_ptrs{};
//			
//		public:
//			auto
//			numberOfInstances() const -> sz
//			{
//				return	_ptrs.size();
//			}
//			auto
//			registerInstanceByPointer(T const* ptr) -> void
//			{
//				EONIL_DEBUG_ASSERT(_ptrs.find(ptr) == _ptrs.end());
//				_ptrs.insert(ptr);
//			}
//			auto
//			unregisterInstanceByPointer(T const* ptr) -> void
//			{
//				EONIL_DEBUG_ASSERT(_ptrs.find(ptr) != _ptrs.end());
//				_ptrs.erase(ptr);
//			}
//		};
//	}
//	
//	
//	
//	
//	
//}
//
//INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END
