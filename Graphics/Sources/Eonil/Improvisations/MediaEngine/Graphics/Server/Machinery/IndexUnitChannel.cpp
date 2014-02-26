//
//  IndexUnitChannel.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/18/13.
//
//

#include "IndexUnitChannel.h"
#include "../../Debugging/Doctor.h"
#include "../../Stub/GL.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Server
	{
		namespace
		Machinery
		{
			using namespace	Debugging;
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
			IndexUnitChannel::linkWithClientMemory(Legacy2013SharedMemory const memory, const Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::IndexUnitChannel::UnitType::CODE type)
			{				
//					EEGL_ASSERT(_idx_ch_linkage._idx_type == UnitType::CODE::NONE);
//					EEGL_ASSERT(_idx_ch_linkage._offset_or_memptr == nullptr);
//					EEGL_ASSERT(_validity == false);
//					
//					_idx_ch_linkage._idx_type			=	type;
//					_idx_ch_linkage._offset_or_memptr	=	memory;
//					
//					_validity	=	true;
				
				EEGL_ASSERT(_server_side_biding == nullptr);
				_type					=	type;
				_client_side_binding	=	new ClientMemoryLinkState {memory};
			}
			
			auto
			IndexUnitChannel::linkWithServerBuffer(const Eonil::Improvisations::MediaEngine::Graphics::Server::ElementArrayBuffer &buffer, const Size offset, const UnitType::CODE type) -> void
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
				
				EEGL_ASSERT(_client_side_binding == nullptr);
				_type					=	type;
				_server_side_biding		=	new ServerBufferLinkState {&buffer, offset};
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
				
				
				
				EEGL_ASSERT(_client_side_binding != nullptr or _server_side_biding != nullptr);
				
				if (_server_side_biding != nullptr)
				{
					eeglUnbindBufer(GL_ELEMENT_ARRAY_BUFFER);
					delete	_server_side_biding;
					_server_side_biding		=	nullptr;
				}
				
				if (_client_side_binding != nullptr)
				{
					delete	_client_side_binding;
					_client_side_binding	=	nullptr;
				}
				
				_type	=	UnitType::CODE::NONE;
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
#pragma mark	-	Privates
			
			Size const
			IndexUnitChannel::ServerBufferLinkState::length() const
			{
				return	buffer->_hotfix_length_of_data;
//				return	buffer._cptr->examination().source->length();
			}
			
			Size const
			IndexUnitChannel::_lengthOfData() const
			{
				EEGL_ASSERT(_is_ready_for_drawing());
				return	_client_side_binding != nullptr ? _client_side_binding->memory.length() : _server_side_biding->length();
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
				return	_client_side_binding != nullptr ? _client_side_binding->memory.address() : CONVPTR(_server_side_biding->offset).ptr;
			}
			
			bool const
			IndexUnitChannel::_is_ready_for_drawing() const
			{
				return	_type != UnitType::CODE::NONE and (_client_side_binding != nullptr or _server_side_biding != nullptr);
			}
			
			
			
			
						
		
		}
	}

	
	
	
	
	
	
}}}}
