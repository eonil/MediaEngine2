//
//  IndexUnitChannel.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/18/13.
//
//

#ifndef __EonilGraphics__IndexUnitChannel__
#define __EonilGraphics__IndexUnitChannel__

#include "../../Common.h"
#include "../Buffer.h"
#include "../_Legacy2013Compat.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

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
				
				void			linkWithClientMemory(Legacy2013SharedMemory const memory, UnitType::CODE const type);
				void			linkWithServerBuffer(ElementArrayBuffer const& buffer, Size const offset, UnitType::CODE const type);
				void			unlink();
				
				
				
			private:
				friend class	Eonil::Improvisations::MediaEngine::Graphics::Server::Machine;
				
				struct
				ClientMemoryLinkState
				{
					Legacy2013SharedMemory 				memory;
				};
				struct
				ServerBufferLinkState
				{
					ptr<ElementArrayBuffer const>	buffer;
					Size							offset;
					
					Size const			length() const;
				};
				
				UnitType::CODE			_type					=	UnitType::CODE::NONE;
				ClientMemoryLinkState*	_client_side_binding	=	nullptr;
				ServerBufferLinkState*	_server_side_biding		=	nullptr;
				
				Size const				_lengthOfData() const;
				GLenum const			_unitTypeForDrawingParameter() const;
				GLvoid const* const		_pointerForDrawingParameter() const;
				bool const				_is_ready_for_drawing() const;
			};
		}
	}
	
	
	
	
	
	
	
}}}}


#endif /* defined(__EonilGraphics__IndexUnitChannel__) */
