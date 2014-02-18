//
//  Machine.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "../Stub/GL.h"
#include "Machine.h"
#include "../Value/Conversion/GLNumbers.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Server
	{
		using namespace Stub;
		using namespace Eonil::Improvisations::MediaEngine::Graphics::Value::Conversion;
		
		
		
		namespace
		{
			union
			CONVPTR
			{
				void const*	ptr;
				uintptr_t	uint;
				
				CONVPTR(void const* const ptr) : ptr(ptr) {}
				CONVPTR(uintptr_t const uint) : uint(uint) {}
			};
			
			static_assert(sizeof(void*) == sizeof(uintptr_t), "");
			static_assert(sizeof(CONVPTR) == sizeof(void const* const), "");
		}
		
		
		
		
		
		
		////

		Machine&
		Machine::machine()
		{
			static	Machine	m;
			return	m;
		}
		
		Machine::Machine()
		{
			GLint	maxc	=	eeglGetInteger(GL_MAX_VERTEX_ATTRIBS);
			
			for (GLuint i=0; i<maxc; i++)
			{
				_chs.push_back(VertexAttributeChannel(i));
			}
			
			GLint	maxctu	=	eeglGetInteger(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
			for (GLuint i=0; i<maxctu; i++)
			{
				_tus.push_back(TextureSampler(i));		//	Texture unit number is guaranteed to be sequential by GL spec.
			}
		}
		Machine::Machine(Machine const& origin)
		{
			EEGL_ASSERT(false);
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		std::vector<VertexAttributeChannel> const&
		Machine::vertexAttributeChannels() const
		{
			return	_chs;
		}
		std::string const
		Machine::description() const
		{
			return	"<MACHINE>";
//				String		vchsdesc	=	Foundation::Array<VertexAttributeChannel>(_chs).description();
//				return	Doctor::stringWithCFormat("<Machine: 0x%llx, vertex channels = \n%s\n>", (uint64_t)(uintptr_t)this, vchsdesc.cString());
		}
		
		VertexAttributeChannel const&
		Machine::vertexAttributeChannelAtIndex(const Size index) const
		{
			EEGL_ASSERT(index < _chs.size());
			return	_chs[index];
		}
		VertexAttributeChannel&
		Machine::vertexAttributeChannelAtIndex(const Size index)
		{
			EEGL_ASSERT(index < _chs.size());
			return	_chs[index];
		}

		
		
		
		
		
		
		IndexUnitChannel const&
		Machine::indexUnitChannel() const
		{
			return	_idxch;
		}
		IndexUnitChannel&
		Machine::indexUnitChannel()
		{
			return	_idxch;
		}
		
		
		TextureSampler const&
		Machine::textureUnitAtIndex(const Size index) const
		{
			return 	_tus.at(index);
		}
		TextureSampler&
		Machine::textureUnitAtIndex(const Size index)
		{
			return	_tus.at(index);
		}
		
		
		
		
		
		
					
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		auto Machine::
		setFramebuffer(const Eonil::Improvisations::MediaEngine::Graphics::Server::Framebuffer &framebuffer) -> void
		{
			eeglBindFramebuffer(GL_FRAMEBUFFER, framebuffer.name());
		}
		auto Machine::
		unsetFramebuffer() -> void
		{
			eeglUnbindFramebuffer(GL_FRAMEBUFFER);
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		auto Machine::
		useProgram(const Eonil::Improvisations::MediaEngine::Graphics::Server::Program &program) -> void
		{
			EEGL_ASSERT(_validity_program_designation == false);
			_validity_program_designation	=	true;
			eeglUseProgram(program.name());
		}
		auto Machine::
		unuseProgram() -> void
		{
			EEGL_ASSERT(_validity_program_designation == true);
			eeglUnuseProgram();
			_validity_program_designation	=	false;
		}
		auto Machine::
		executeBlockWithProgram(const Eonil::Improvisations::MediaEngine::Graphics::Server::Program &program, std::function<void ()> block) -> void
		{
			useProgram(program);
			block();
			unuseProgram();
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		void
		Machine::setViewport(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Bounds2 bounds)
		{
			EEGL_ASSERT(not bounds.isNaN());
			EEGL_ASSERT(bounds != Bounds2::Utility::infinity());
			EEGL_ASSERT(not _validity_of_viewport);
			
			Vector2	sz	=	bounds.size();
			eeglViewport(bounds.minimum.x, bounds.minimum.y, sz.x, sz.y);
			
			if (Doctor::useStateValidation())
			{
				_validity_of_viewport	=	true;
			}
		}
		
		void
		Machine::unsetViewport()
		{
			EEGL_ASSERT(_validity_of_viewport);
			if (Doctor::useStateValidation())
			{
				_validity_of_viewport	=	false;
			}
		}
		
		void
		Machine::setScissor(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Bounds2 bounds)
		{
			EEGL_ASSERT(not bounds.isNaN());
			EEGL_ASSERT(bounds != Bounds2::Utility::infinity());
			EEGL_ASSERT(not _has_scissor);
			Vector2	sz	=	bounds.size();
			eeglEnable(GL_SCISSOR_TEST);
			eeglScissor(bounds.minimum.x, bounds.minimum.y, sz.x, sz.y);
			
			if (Doctor::useStateValidation())
			{
				_has_scissor	=	true;
			}
		}
		void
		Machine::unsetScissor()
		{
			if (Doctor::useStateValidation())
			{
				EEGL_ASSERT(_has_scissor);
				_has_scissor	=	false;
			}
			
			eeglDisable(GL_SCISSOR_TEST);
		}
		
		
		
		
		
		void
		Machine::drawArrays(const DrawingMode mode, const Size index, const Size count)
		{
			Doctor::assertForUnsignedNumericRange<Size, GLint>(index);
			Doctor::assertForUnsignedNumericRange<Size, GLsizei>(count);
			EEGL_ASSERT_WITH_REASON(_validity_of_viewport == true, "Viewport must be set before perform any drawing.");
			
			if ((Doctor::useStateValidation()))
			{
				for (GLuint i=0; i<_chs.size(); i++)
				{
					GLuint				_idx	=	i;
					
					bool const			enabled	=	eeglGetVertexAttribi(_idx, GL_VERTEX_ATTRIB_ARRAY_ENABLED) != 0;
					uint				size	=	eeglGetVertexAttribi(_idx, GL_VERTEX_ATTRIB_ARRAY_SIZE);
					uint				bufname	=	eeglGetVertexAttribi(_idx, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);
					GLvoid*				memptr	=	eeglGetVertexAttribPointerv(_idx, GL_VERTEX_ATTRIB_ARRAY_POINTER);
					EEGL_ASSERT_WITH_REASON(not enabled or size != 0, "A vertex channel should be not-enabled or should have specified size if enabled.");
					EEGL_ASSERT_WITH_REASON(not enabled or bufname != 0 or memptr != NULL, "A vertex channel should be not-enabled. If enabled, it should have specified buffer name or non-`NULL` client memory address.");
				}
			}
			
			
			////
			
			GLint const		index2	=	GLintFromSize(index);
			GLsizei const	count2	=	GLsizeiFromSize(count);
			
			eeglDrawArrays(GLenum(mode), index2, count2);
		}
		
		
		
		void
		Machine::drawElements(const DrawingMode mode, const Size index, const Size count)
		{
			Doctor::assertForUnsignedNumericRange<Size, GLuint>(count);
			EEGL_ASSERT_WITH_REASON(_validity_of_viewport == true, "Viewport must be set before perform any drawing.");
			EEGL_ASSERT(_idxch._is_ready_for_drawing());
			
			GLenum const		tcode	=	_idxch._unitTypeForDrawingParameter();
			EEGL_ASSERT_WITH_REASON(tcode == IndexUnitChannel::UnitType::CODE::UINT8 or tcode == IndexUnitChannel::UnitType::CODE::UINT16, "Currently, only UINT8 and UIN16 is considered. Otherwise code review is required.");
			
			Size const			usz		=	tcode == IndexUnitChannel::UnitType::CODE::UINT8 ? 1 : 2;
			Size const			offset	=	usz * index;
			GLvoid const* const	ptr		=	_idxch._pointerForDrawingParameter();
			GLvoid const* const	ptr2	=	CONVPTR(CONVPTR(ptr).uint + offset).ptr;
			
			if (Doctor::useStateValidation())
			{
				Size const		reqlen	=	usz * count;
				Size const		reqrun	=	offset + reqlen;
				Size const		curlen	=	_idxch._lengthOfData();
				
				std::string const	errdesc	=	Doctor::stringWithCFormat("Currently bound index-data does not have enough data to draw specified range of indexes. (required: offset + length = %llu + %llu = %llu bytes, current data: length = %llu bytes)", uint64_t(offset), uint64_t(reqlen), uint64_t(reqrun), uint64_t(curlen));
				EEGL_ASSERT_WITH_REASON(curlen >= reqrun, errdesc);
			}
			
			////
			
			GLsizei const	count2	=	GLsizei(count);
			
			eeglDrawElement(GLenum(mode), count2, tcode, ptr2);
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
//			bool const
//			Machine::validityOfVertexSourcing() const
//			{
//				return	_validity_vertex_sourcing;
//			}
//			bool const
//			Machine::validityOfProgramDesignation() const
//			{
//				return	_validity_program_designation;
//			}
	}

}}}}