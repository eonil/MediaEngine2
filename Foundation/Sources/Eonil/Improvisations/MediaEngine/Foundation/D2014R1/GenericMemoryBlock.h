//
//  GenericMemoryBlock.h
//  Foundation
//
//  Created by Hoon H. on 2/6/14.
//
//

#ifndef __Foundation__GenericMemoryBlock__
#define __Foundation__GenericMemoryBlock__

#include "../Common.h"
#include "../Numerics.h"
#include "GenericMemoryRange.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Foundation {
	
	inline namespace
	D2014R1			//	Distribution 2014, revision 1.
	{
				
		
		
		
		
		
		
		
		
		/*!
		 @brief				A uniquely owned memory range.
		 
		 @classdesign		This is a proxy editor around memory of value strip. This class
							owns the memory range, and deallocates it when dies.
		 
		 @discussion		User always use this for existing - already initialized - value strip.
							This class does not allocate any memory.
		 */
		template <typename T>
		class
		GenericMemoryBlock
		{
			static_assert(std::is_standard_layout<T>::value, "This class performs memory-copy instead of re-initialization of each values. So only standard layout classes will work properly.");
			
			GenericMemoryRange<T>		_range{};
			
		public:
			GenericMemoryBlock() = default;													//!	Creates an empty block. (invalid state)
			GenericMemoryBlock(GenericMemoryRange<T> const& range) : _range(range)
			{
				size_t	num	=	_range.end() - _range.begin();
				GenericMemoryRange<T>	r2{};
				r2.begin	=	new T[num]();
				r2.end		=	r2.begin + num;
				
				std::swap(r2, _range);
			}
			~GenericMemoryBlock()
			{
				delete[]	_range.begin();
			}
			
			auto	range() const -> GenericMemoryRange<T> const&;
			auto	range() -> GenericMemoryRange<T>&;
		};
		
		template <typename T> auto GenericMemoryBlock<T>::
		range() const -> GenericMemoryRange<T> const&
		{
			return	_range;
		}
		template <typename T> auto GenericMemoryBlock<T>::
		range() -> GenericMemoryRange<T>&
		{
			return	_range;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
//		
//		/*
//		 Classes for unknown type memory block. Usually `void*` passed from C functions.
//		 */
//		using	UnknownMemoryRange					=	GenericMemoryRange<void>;
//		using	UnknownMemoryBlock					=	GenericMemoryBlock<void>;
//		
//		/*!
//		 Use this for binary memory block.
//		 */
//		using	ByteMemoryRange						=	GenericMemoryRange<uint8_t>;
//		using	ByteMemoryBlock						=	GenericMemoryBlock<uint8_t>;
//		
//		
		
				
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
	
}}}}





#endif /* defined(__Foundation__GenericMemoryBlock__) */
