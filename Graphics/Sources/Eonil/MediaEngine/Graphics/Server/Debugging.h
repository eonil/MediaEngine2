//
//  Debugging.h
//  Graphics
//
//  Created by Hoon H. on 2/7/14.
//
//

#ifndef __Graphics__Debugging__
#define __Graphics__Debugging__


#include "../Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		
		
		namespace
		Debugging
		{
			template <typename T>
			class
			InstanceCounter
			{
				std::set<T const*>	_ptrs{};
				
			public:
				auto
				numberOfInstances() const -> Size
				{
					return	_ptrs.size();
				}
				auto
				registerInstanceByPointer(T const* ptr) -> void
				{
					EONIL_DEBUG_ASSERT(_ptrs.find(ptr) == _ptrs.end());
					_ptrs.insert(ptr);
				}
				auto
				unregisterInstanceByPointer(T const* ptr) -> void
				{
					EONIL_DEBUG_ASSERT(_ptrs.find(ptr) != _ptrs.end());
					_ptrs.erase(ptr);
				}
			};
		}
		
		
		
		
		
	}
	
}}}}


#endif /* defined(__Graphics__Debugging__) */
