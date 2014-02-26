//
//  VertexAttributeChannel.cpp
//  EonilGraphics
//
//  Created by Eonil on 5/1/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "../../Common.h"
#include "../../Stub/GL.h"
#include "../../Debugging/Doctor.h"
#include "VertexAttributeChannel.h"



namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Server
	{
		namespace
		Machinery
		{
			using namespace Debugging;
			using namespace Stub;
			
			
			

			
			
						
			
			
			
			
			
			
			
			
			
			
			
			
			
						
			
			
			
			
			auto
			VertexAttributeChannel::linkWithClientMemory(const void *const memory, const Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::Format format) -> void
			{
				EONIL_DEBUG_ASSERT_WITH_MESSAGE(GLint(format.componentCount) >= 1, "Vertex channel's component count must be >=1.");
				EONIL_DEBUG_ASSERT_WITH_MESSAGE(GLint(format.componentCount) <= 4, "Vertex channel's component count must be <=4.");
				EEGL_ASSERT(memory != NULL);
				
				uint8_t const*	ptr		=	(uint8_t const* const)memory;
				uint8_t const*	ptr2	=	ptr + format.dataOffset;
				
				//					EEGL_ASSERT(format.dataLengthInBytes() == format.memoryLength);
				eeglEnableVertexAttribArray(_idx);
				eeglVertexAttribPointer(_idx, GLint(format.componentCount), GLenum(format.componentType), format.normalization, format.strideSizeInBytes, ptr2);
				
				_validity	=	true;
			}
			auto
			VertexAttributeChannel::linkWithServerBuffer(const Eonil::Improvisations::MediaEngine::Graphics::Server::ArrayBuffer &buffer, const Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::Format format) -> void
			{
				EONIL_DEBUG_ASSERT_WITH_MESSAGE(GLint(format.componentCount) >= 1, "Vertex channel's component count must be >=1.");
				EONIL_DEBUG_ASSERT_WITH_MESSAGE(GLint(format.componentCount) <= 4, "Vertex channel's component count must be <=4.");
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(_dbg_cur_ab_ptr = &buffer);
				
				/*!
				 @todo
				 This needs review because we currently alway unbind the buffer.
				 There should be an approach to avoid this undinging cost.
				 
				 >	Consider using VBO.
				 
				 */
				
				EEGL_ASSERT(not buffer.empty());
				
				uint8_t const*	ptr		=	nullptr;
				uint8_t const*	ptr2	=	ptr + format.dataOffset;
				
				eeglBindBuffer(GL_ARRAY_BUFFER, buffer.name());
				eeglVertexAttribPointer(_idx, GLint(format.componentCount), GLenum(format.componentType), format.normalization, format.strideSizeInBytes, ptr2);
				eeglEnableVertexAttribArray(_idx);
				eeglUnbindBufer(GL_ARRAY_BUFFER);
				
				_validity	=	true;
			}
			void
			VertexAttributeChannel::unlink()
			{
				EEGL_ASSERT_WITH_REASON(eeglGetInteger(GL_ARRAY_BUFFER_BINDING) == 0, "No array-buffer should be bound currently.");
				
				if (Doctor::useResourceCleansing())
				{
					eeglVertexAttribPointer(_idx, 4, GL_FLOAT, GL_FALSE, 0, NULL);
				}
				
				eeglDisableVertexAttribArray(_idx);
				
				_validity	=	false;
				
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(_dbg_cur_ab_ptr = nullptr);
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			VertexAttributeChannel::VertexAttributeChannel(GLuint const index)
			{
				_idx	=	index;
			}
			GLuint const
			VertexAttributeChannel::index() const
			{
				return	_idx;
			}
			
			
			
			
			
			
			auto
			VertexAttributeChannel::description() const -> str
			{
				bool const			enabled	=	eeglGetVertexAttribi(_idx, GL_VERTEX_ATTRIB_ARRAY_ENABLED) != 0;
				std::string const	enstr	=	enabled ? "enabled" : "disabled";
				GLint				size	=	eeglGetVertexAttribi(_idx, GL_VERTEX_ATTRIB_ARRAY_SIZE);
				GLint				bufname	=	eeglGetVertexAttribi(_idx, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);
				return	Doctor::stringWithCFormat("<VertexAttributeChannel: index = %u, %s, buffer name = %u, size = %u>", _idx, enstr.c_str(), bufname, size);
			}
			auto
			VertexAttributeChannel::validity() const -> bool
			{
				return	_validity;
			}
			
			
			

		}
	}
	
	
	
	
	
}}}}
