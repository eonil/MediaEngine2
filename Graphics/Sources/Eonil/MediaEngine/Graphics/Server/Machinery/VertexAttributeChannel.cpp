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
#include "../../Debugging/DebugOnlyValidityFlagSlot.h"

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
			
			namespace
			{
#if	EONIL_MEDIA_ENGINE_DEBUG_MODE
				using	DEBUG_FLAG_SLOT				=	DebugOnlyValidityFlagSlotV1;
				using	DATA_BINDNIG_STATE_MAP		=	umap<Machine const*, umap<GLuint, DEBUG_FLAG_SLOT>>;
				
//				using	ARRAY_BUFFER_RETAINER		=	umap<Machine const*, umap<GLuint, ptr<ArrayBuffer const>>>;
				
				static auto
				_data_binding_state_of(Machine const* m, GLint idx) -> DEBUG_FLAG_SLOT&
				{
					static DATA_BINDNIG_STATE_MAP*	_map_ptr	{nullptr};
					if (_map_ptr == nullptr)
					{
						_map_ptr	=	new DATA_BINDNIG_STATE_MAP();
					}
					DATA_BINDNIG_STATE_MAP&	_map	=	*_map_ptr;
					
					////
					
					if (_map.find(m) == _map.end())
					{
						_map.insert({m,{}});
					}
					auto&	submap	=	_map.at(m);
					if (submap.find(idx) == submap.end())
					{
						submap.insert({idx,{}});
					}
					auto&	slot	=	submap.at(idx);
					return	slot;
				}
				
				static auto
				SET_READY_FOR_RENDERING(Machine const* m, GLint const index) -> void
				{
					_data_binding_state_of(m, index).set_on();
				}
				static auto
				UNSET_READY_FOR_RENDERING(Machine const* m, GLint const index) -> void
				{
					_data_binding_state_of(m, index).set_off();
				}
				static auto
				ASSERT_READINESS_FOR_RENDERING(Machine const* m, GLint const index) -> void
				{
					_data_binding_state_of(m, index).should_be_on_now();
				}
#else
				
				static auto inline
				SET_READY_FOR_RENDERING(Machine const* m, GLint const index) -> void
				{
				}
				static auto inline
				UNSET_READY_FOR_RENDERING(Machine const* m, GLint const index) -> void
				{
				}
				static auto inline
				ASSERT_READINESS_FOR_RENDERING(Machine const* m, GLint const index) -> void
				{
				}
#endif
	
			}
			

			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			auto
			VertexAttributeChannel::_assert_ready_for_drawing() const -> void
			{
				ASSERT_READINESS_FOR_RENDERING(_machine, _idx);
			}
			
			
			
			
			
			
			
			
			
			
						
			
			
			
			
			VertexAttributeChannel::VertexAttributeChannel(Machine* machine, GLuint const& index) : _machine(machine), _idx(index)
			{
			}
			VertexAttributeChannel::VertexAttributeChannel(Machine* machine, Size const& index) : VertexAttributeChannel(machine, toGLuint(index))
			{
			}
			
			
			auto
			VertexAttributeChannel::operator==(VertexAttributeChannel const& ch) const -> bool
			{
				return	_idx == ch._idx and _machine == ch._machine;
			}
			auto
			VertexAttributeChannel::operator!=(VertexAttributeChannel const& ch) const -> bool
			{
				return	not (_idx == ch._idx and _machine == ch._machine);
			}
			
			auto
			VertexAttributeChannel::index() const -> GLuint
			{
				return	_idx;
			}

			
			
			
			
			
			
			
			
			
			
						
			
			
			
			
			auto
			VertexAttributeChannel::linkWithClientMemory(const void *const memory, const Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::Format format) -> void
			{
				EONIL_DEBUG_ASSERT_WITH_MESSAGE(GLint(format.componentCount) >= 1, "Vertex channel's component count must be >=1.");
				EONIL_DEBUG_ASSERT_WITH_MESSAGE(GLint(format.componentCount) <= 4, "Vertex channel's component count must be <=4.");
				EEGL_ASSERT(memory != NULL);
				
				uint8_t const*	ptr		=	(uint8_t const* const)memory;
				uint8_t const*	ptr2	=	ptr + format.dataOffset;
				
//				EEGL_ASSERT(format.dataLengthInBytes() == format.memoryLength);
				eeglEnableVertexAttribArray(_idx);
				eeglVertexAttribPointer(_idx, GLint(format.componentCount), GLenum(format.componentType), format.normalization, format.strideSizeInBytes, ptr2);
				
				SET_READY_FOR_RENDERING(_machine, _idx);
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
				
				SET_READY_FOR_RENDERING(_machine, _idx);
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
				
				
				UNSET_READY_FOR_RENDERING(_machine, _idx);
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(_dbg_cur_ab_ptr = nullptr);
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
						
			
			
			
			
			
			auto
			VertexAttributeChannel::description() const -> str
			{
				bool const			enabled	=	eeglGetVertexAttribi(_idx, GL_VERTEX_ATTRIB_ARRAY_ENABLED) != 0;
				std::string const	enstr	=	enabled ? "enabled" : "disabled";
				GLint				size	=	eeglGetVertexAttribi(_idx, GL_VERTEX_ATTRIB_ARRAY_SIZE);
				GLint				bufname	=	eeglGetVertexAttribi(_idx, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);
				
				return	Doctor::stringWithCFormat("<VertexAttributeChannel: index = %u, %s, buffer name = %u, size = %u>", GLuint(_idx), enstr.c_str(), bufname, size);
			}
			
			
			

		}
	}
	
	
	
	
	
}}}}
