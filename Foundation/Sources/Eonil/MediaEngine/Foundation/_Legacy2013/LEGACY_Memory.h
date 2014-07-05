////
////  Memory.h
////  Foundation
////
////  Created by Hoon H. on 2/5/14.
////
////
//
//#ifndef __Foundation__Memory__
//#define __Foundation__Memory__
//
//#include "../Common.h"
//#include "../Numerics.h"
//
//namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Foundation {
//	
//	namespace
//	_Legacy2013
//	{
//		
//
//		/*!
//		 Abstracts immutable region of memory.
//		 Target memory region also can be a part of file by memory-mapped file feature.
//		 
//		 @deprecated
//		 Shared management are all deprecated. Do not use shared memory block feature.
//		 You can consider using of `GenericMemoryBlock`.
//		 Use uniquely owned memory block.
//		 */
//		class
//		EONIL_MEDIA_ENGINE_DEPRECATE()
//		SharedMemory
//		{
//		public:
//			
//			struct
//			Factory
//			{
//				static SharedMemory const memoryByCopyingRange(void const* const address, Size const length);		//	Copy and own the memory.
//				static SharedMemory const memoryByProxyingRange(void const* const address, Size const length);		//	Just offer viwe on existing memory. Doesn't own the memory.
//				static SharedMemory const memoryByOwningRange(void const* const address, Size const length);		//	Own the memory without copying.
//			};
//			
//			SharedMemory();
//			SharedMemory(SharedMemory const& m);
//			SharedMemory(decltype(nullptr) const null);
//			
//			SharedMemory&					operator=(SharedMemory m);
//			
//			bool const				operator==(SharedMemory const& memory) const;									//!	Performs full-content comparison.
//			bool const				operator!=(SharedMemory const& memory) const;									//!	Performs full-content comparison.
//			
//			bool const				operator==(decltype(nullptr) const& memory) const;
//			bool const				operator!=(decltype(nullptr) const& memory) const;
//			
//			void const * const		address() const;
//			Size const				length() const;
//			
//		private:
//			struct
//			Core;
//			
//			std::shared_ptr<Core const>	core;
//			
//			SharedMemory(std::shared_ptr<Core const> const core);
//		};
//
//
//
//
//	}
//	
//}}}}
//
//
//#endif /* defined(__Foundation__Memory__) */
