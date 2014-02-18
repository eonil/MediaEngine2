//
//  GenericDynamicArray.h
//  Foundation
//
//  Created by Hoon H. on 2/10/14.
//
//

#ifndef __Foundation__GenericDynamicArray__
#define __Foundation__GenericDynamicArray__


#include "../Common.h"
#include "../Numerics.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Foundation {
	
	inline namespace
	D2014R1			//	Distribution 2014, revision 1.
	{
		
		/*!
		 Fixed sized dynamic array.
		 */
		template <typename T>
		class
		GenericDynamicArray
		{
			std::unique_ptr<T>	_addr{nullptr};
			Size				_size{0};
			
		public:
			GenericDynamicArray() = default;
			/*!
			 This takes unique ownership of the array at the address.
			 */
			GenericDynamicArray(std::unique_ptr<T>&& address, Size const& count) : _addr(address), _size(count)
			{
			}
			~GenericDynamicArray()
			{
			}
			
			////
			
			auto
			size() const -> Size const&
			{
				return	_size;
			}
			auto
			at(Size const index) const -> T const&
			{
				EONIL_DEBUG_ASSERT(index < _size);
				return	_addr[index];
			}
			auto
			at(Size const index) -> T&
			{
				EONIL_DEBUG_ASSERT(index < _size);
				return	_addr[index];
			}
		};
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
	
}}}}



#endif /* defined(__Foundation__GenericDynamicArray__) */
