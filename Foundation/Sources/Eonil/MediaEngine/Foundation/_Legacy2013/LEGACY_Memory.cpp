//
//  Memory.cpp
//  Foundation
//
//  Created by Hoon H. on 2/5/14.
//
//

#include "LEGACY_Memory.h"



#include <cstdlib>
#include <sys/mman.h>
#include "../Debugging/Doctor.h"


namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Foundation {
	
	namespace _Legacy2013
	{
	
		using namespace Debugging;
		
		
		
		struct
		SharedMemory::Core
		{
			void const*		address;
			Size			length;
			bool			own;
			
			Core(void const* const address, Size const length, bool const own) : address(address), length(length), own(own)
			{
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(Doctor::assertWithReason(address != NULL));
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(Doctor::assertWithReason(length > 0));
			}
			~Core()
			{
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(Doctor::assertWithReason(address != NULL));
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(Doctor::assertWithReason(length > 0));
				
				if (own)
				{
					free((void*)address);
				}
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(address = NULL);
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(length = 0);
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(own = false);
			}
			
		};
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		SharedMemory::SharedMemory() : core(nullptr)
		{
		}
		SharedMemory::SharedMemory(SharedMemory const& m) : core(m.core)
		{
		}
		SharedMemory::SharedMemory(std::shared_ptr<Core const> const core) : core(core)
		{
		}
		SharedMemory::SharedMemory(decltype(nullptr) const null) : core(nullptr)
		{
		}
		
		
		SharedMemory&
		SharedMemory::operator=(Eonil::Improvisations::MediaEngine::Foundation::_Legacy2013::SharedMemory m)
		{
			std::swap(core, m.core);
			return	*this;
		}
		
		
		
		
		
		
		
		
		
		
		namespace
		{
			bool const
			DataEquals(SharedMemory const m0, SharedMemory const m1)
			{
				return	(m0.length() == m1.length())
				and		((m0.address() == m1.address())
						 or (memcmp(m0.address(), m1.address(), m0.length()) == 0));
			};
		}
		
		bool const
		SharedMemory::operator==(SharedMemory const &memory) const
		{
			return	DataEquals(*this, memory);
		}
		bool const
		SharedMemory::operator!=(SharedMemory const &memory) const
		{
			return	not DataEquals(*this, memory);
		}
		
		bool const
		SharedMemory::operator==(const decltype(nullptr) &memory) const
		{
			return	core == nullptr;
		}
		bool const
		SharedMemory::operator!=(const decltype(nullptr) &memory) const
		{
			return	core != nullptr;
		}
		
		void const* const
		SharedMemory::address() const
		{
			EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(Doctor::assertWithReason(this != nullptr));
			return	core->address;
		}
		Size const
		SharedMemory::length() const
		{
			EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(Doctor::assertWithReason(this != nullptr));
			return	core->length;
		}
		
		
		
		
		
		SharedMemory const
		SharedMemory::Factory::memoryByCopyingRange(const void *const address, const Size length)
		{
			EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(Doctor::assertWithReason(address != NULL));
			EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(Doctor::assertWithReason(length > 0));
			
			void* const	ptr2	=	malloc(length);
			memcpy(ptr2, address, length);
			
			return	memoryByOwningRange(ptr2, length);
		}
		SharedMemory const
		SharedMemory::Factory::memoryByOwningRange(const void *const address, const Size length)
		{
			return	SharedMemory(std::shared_ptr<Core const>::make_shared(address, length, true));
		}
		SharedMemory const
		SharedMemory::Factory::memoryByProxyingRange(const void *const address, const Size length)
		{
			return	SharedMemory(std::shared_ptr<Core const>::make_shared(address, length, false));
		}
		
		//		Memory const
		//		Memory::Factory::memoryWithLength(const Size length)
		//		{
		//			void*	mem	=	malloc(length);
		//			return	memoryByOwningRange(mem, length);
		//		}
		
		
		
		
		
		
		
		
	
	
	
	}
	
}}}}
	
	
	
	
	
	
	
	
	
	
	
