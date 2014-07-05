//
//  IndexUnitChannel.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/18/13.
//
//

#include "IndexUnitChannel.h"
#include "../../Stub/GL.h"

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Server
{
	namespace
	Machinery
	{
		using namespace	Stub;
		
		namespace
		{
			union
			CONVPTR
			{
				void*		ptr;
				uintptr_t	uint;
				
				CONVPTR(void* const ptr) : ptr(ptr) {}
				CONVPTR(uintptr_t const uint) : uint(uint) {}
			};
			
			static_assert(sizeof(void*) == sizeof(uintptr_t), "");
			static_assert(sizeof(CONVPTR) == sizeof(void const* const), "");
		}
		
		
		
		
		

		void
		IndexUnitChannel::linkWithClientMemory(GenericMemoryRange<void const> memory, const Server::Machinery::IndexUnitChannel::UnitType::CODE type)
		{				
//					EEGL_ASSERT(_idx_ch_linkage._idx_type == UnitType::CODE::NONE);
//					EEGL_ASSERT(_idx_ch_linkage._offset_or_memptr == nullptr);
//					EEGL_ASSERT(_validity == false);
//					
//					_idx_ch_linkage._idx_type			=	type;
//					_idx_ch_linkage._offset_or_memptr	=	memory;
//					
//					_validity	=	true;
			
			EEGL_ASSERT(_server_side_biding.empty());
			_type					=	type;
			_client_side_binding	=	{memory};
		}

		
		auto
		IndexUnitChannel::linkWithServerBuffer(const Server::ElementArrayBuffer &buffer, const sz offset, const UnitType::CODE type) -> void
		{
//					EEGL_ASSERT(_idx_ch_linkage._idx_type == UnitType::CODE::NONE);
//					EEGL_ASSERT(_idx_ch_linkage._offset_or_memptr == nullptr);
//					EEGL_ASSERT(_validity == false);
//					
//					CONVPTR	conv(offset);
//										
//					_idx_ch_linkage._idx_type			=	type;
//					_idx_ch_linkage._offset_or_memptr	=	conv.ptr;
//					
//					eeglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.name());
//					
//					_validity	=	true;
			
			EEGL_ASSERT(_client_side_binding.empty());
			_type					=	type;
			_server_side_biding		=	ServerBufferLinkState{&buffer, offset};
			eeglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.name());
		}
		
		void
		IndexUnitChannel::unlink()
		{
//					eeglUnbindBufer(GL_ELEMENT_ARRAY_BUFFER);
//
//					_idx_ch_linkage._idx_type			=	UnitType::CODE::NONE;
//					_idx_ch_linkage._offset_or_memptr	=	nullptr;
//					_idx_ch_linkage._len				=	0;
//					
//					_validity	=	false;
			
			
			
			EEGL_ASSERT(not _client_side_binding.empty() or not _server_side_biding.empty());
			
			if (not _server_side_biding.empty())
			{
				eeglUnbindBufer(GL_ELEMENT_ARRAY_BUFFER);
				_server_side_biding	=	{};
			}
			
			if (not _client_side_binding.empty())
			{
				_client_side_binding	=	{};
			}
			
			_type	=	UnitType::CODE::NONE;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
#pragma mark	-	Privates
		
		sz const
		IndexUnitChannel::ServerBufferLinkState::length() const
		{
			return	buffer->_hotfix_length_of_data;
//				return	buffer._cptr->examination().source->length();
		}
		
		sz const
		IndexUnitChannel::_lengthOfData() const
		{
			EEGL_ASSERT(_is_ready_for_drawing());
			EEGL_ASSERT(_client_side_binding.empty() or _client_side_binding.memory.reinterpretAs<uint8_t const>().size() > 0);
			return	_server_side_biding.empty() ? _client_side_binding.memory.reinterpretAs<uint8_t const>().size() : _server_side_biding.length();
		}
		GLenum const
		IndexUnitChannel::_unitTypeForDrawingParameter() const
		{
			EEGL_ASSERT(_is_ready_for_drawing());
			return	_type;
		}
		
		GLvoid const* const
		IndexUnitChannel::_pointerForDrawingParameter() const
		{
			EEGL_ASSERT(_is_ready_for_drawing());
			EEGL_ASSERT(_client_side_binding.empty() or _client_side_binding.memory.reinterpretAs<uint8_t const>().size() > 0);
			return	_server_side_biding.empty() ? _client_side_binding.memory.begin() : CONVPTR(_server_side_biding.offset).ptr;
		}
		
		bool const
		IndexUnitChannel::_is_ready_for_drawing() const
		{
			return	_type != UnitType::CODE::NONE and (not _client_side_binding.empty() or not _server_side_biding.empty());
		}
		
		
		
		
					
	
	}
}





INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END

