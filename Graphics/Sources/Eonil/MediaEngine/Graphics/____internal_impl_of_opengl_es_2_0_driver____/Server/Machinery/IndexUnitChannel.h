//
//  IndexUnitChannel.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/18/13.
//
//

#pragma once
#include "../Declarations.h"
#include "../Buffer.h"
#include "../LEGACY_Legacy2013Compat.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Server
{
	class
	Machine;
	
	
	
	namespace
	Machinery
	{
		
		/*!
		 @discussion
		 Same with data-source management of `VertexAttributeChannel`.
		 
		 Linked data source (regardless of client or server) will be used while drawing something
		 with GL API. And the data required while drawing. Anyway this object doesn't keep the data
		 sources alive, so it's your responsibility to keep them alive while drawing.
		 */
		class
		IndexUnitChannel
		{
		public:
			struct
			UnitType
			{
				UnitType() = delete;
				
				enum
				CODE : GLenum
				{
					NONE	=	0,
					UINT8	=	GL_UNSIGNED_BYTE,
					UINT16	=	GL_UNSIGNED_SHORT,
				};
			};
			
//				EONIL_MEDIA_ENGINE_DEPRECATE() void			linkWithClientMemory(_Legacy2013::SharedMemory const memory, UnitType::CODE const type);
			
			void			linkWithClientMemory(GenericMemoryRange<void const> memory, UnitType::CODE const type);
			void			linkWithServerBuffer(ElementArrayBuffer const& buffer, sz const offset, UnitType::CODE const type);
			void			unlink();
			
			
			
		private:
			friend class	Server::Machine;
			
			struct
			ClientMemoryLinkState
			{
//					_Legacy2013::SharedMemory 				memory;
				GenericMemoryRange<void const>	memory	=	{};
				
				ClientMemoryLinkState() {}
				ClientMemoryLinkState(GenericMemoryRange<void const> memory) : memory(memory) {}
				
				auto
				empty() const -> bool
				{
					return	memory.empty();
				}
			};
			struct
			ServerBufferLinkState
			{
				ptr<ElementArrayBuffer const>	buffer	=	nullptr;
				sz								offset	=	0;
				
				sz const						length() const;
				
				////
				
				ServerBufferLinkState() {}
				ServerBufferLinkState(ptr<ElementArrayBuffer const> buffer, sz const offset) : buffer(buffer), offset(offset) {}
				
				auto
				empty() const -> bool
				{
					return	buffer == nullptr;
				}
			};
			
			UnitType::CODE			_type					=	UnitType::CODE::NONE;
			ClientMemoryLinkState	_client_side_binding	=	{};
			ServerBufferLinkState	_server_side_biding		=	{};
			
			sz const				_lengthOfData() const;
			GLenum const			_unitTypeForDrawingParameter() const;
			GLvoid const* const		_pointerForDrawingParameter() const;
			bool const				_is_ready_for_drawing() const;
		};
	}
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END
