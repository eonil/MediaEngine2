//
//  Machine.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "Machine.h"

#include "../Stub/GL.h"

#include "Symbols.h"
#include "Query.h"
#include "Program.h"
#include "Shader.h"
#include "Texture.h"
#include "Buffer.h"
#include "Framebuffer.h"

#include "Machinery/VertexAttributeChannel.h"
#include "Machinery/IndexUnitChannel.h"
#include "Machinery/TextureSampler.h"

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
			return	current();
		}
		auto
		Machine::current() -> Machine&
		{
			static	Machine	m{};
			return	m;
		}
		
		Machine::Machine() : _idxch_ptr(new IndexUnitChannel())
		{
			_query	=	uptr<Query>{new Query{}};
			
			GLint	maxc	=	eeglGetInteger(GL_MAX_VERTEX_ATTRIBS);
			
			EONIL_MEDIA_ENGINE_DEBUG_LOG("OpenGL system vendor: " + str((char const*)eeglGetString(GL_VENDOR)));
			EONIL_MEDIA_ENGINE_DEBUG_LOG("`Server::Machine`'s vertex-attribute-channel count: " + std::to_string(maxc));
			
			for (GLuint i=0; i<maxc; i++)
			{
				_chs.push_back(VertexAttributeChannel(this, i));
			}
			
			GLint	maxctu	=	eeglGetInteger(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
			for (GLuint i=0; i<maxctu; i++)
			{
				_tus.push_back(TextureSampler(i));		//	Texture unit number is guaranteed to be sequential by GL spec.
			}
		}
		Machine::
		~Machine()
		{
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		std::vector<VertexAttributeChannel> const&
		Machine::vertexAttributeChannelsV1() const
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
			return	*_idxch_ptr;
		}
		IndexUnitChannel&
		Machine::indexUnitChannel()
		{
			return	*_idxch_ptr;
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
		vertexAttributeChannels() const -> VertexAttributeChannelList const&
		{
			return	_vert_ch_list;
		}
		auto Machine::
		vertexAttributeChannels() -> VertexAttributeChannelList&
		{
			return	_vert_ch_list;
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
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		auto Machine::
		compositionMode() const -> CompositionMode const&
		{
			return	_comp_mode;
		}
		auto Machine::
		compositionMode() -> CompositionMode&
		{
			return	_comp_mode;
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
		Machine::drawArrays(const DrawingMode mode, const Size index, const Size count)
		{
			EONIL_DEBUG_ASSERT_WITH_MESSAGE((mode != DrawingMode::TRIANGLES) or (count % 3 == 0), "If the drawing-mode is TRIANGLES, then selected vertex count must be multiplication of 3.");
			EONIL_DEBUG_ASSERT_WITH_MESSAGE((mode != DrawingMode::TRIANGLE_STRIP) or (count > 3), "If the drawing-mode is TRIANGLE_STRIP, then selected vertex count must be equal or larger then 3.");
			EONIL_DEBUG_ASSERT_WITH_MESSAGE((mode != DrawingMode::LINES) or (count % 2 == 0), "If the drawing-mode is LINES, then selected vertex count must be even number.");
			
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
			
			EONIL_DEBUG_ASSERT(index <= std::numeric_limits<GLint>::max());
			
			GLint const		index2	=	GLint(index);
			GLsizei const	count2	=	toGLsizei(count);
			
			eeglDrawArrays(GLenum(mode), index2, count2);
		}
		
		
		
		void
		Machine::drawElements(const DrawingMode mode, const Size index, const Size count)
		{
			EONIL_DEBUG_ASSERT_WITH_MESSAGE((mode != DrawingMode::TRIANGLES) or (count % 3 == 0), "If the drawing-mode is TRIANGLES, then selected vertex count must be multiplication of 3.");
			EONIL_DEBUG_ASSERT_WITH_MESSAGE((mode != DrawingMode::TRIANGLE_STRIP) or (count > 3), "If the drawing-mode is TRIANGLE_STRIP, then selected vertex count must be equal or larger then 3.");
			EONIL_DEBUG_ASSERT_WITH_MESSAGE((mode != DrawingMode::LINES) or (count % 2 == 0), "If the drawing-mode is LINES, then selected vertex count must be even number.");

			Doctor::assertForUnsignedNumericRange<Size, GLuint>(count);
			EEGL_ASSERT_WITH_REASON(_validity_of_viewport == true, "Viewport must be set before perform any drawing.");
			EEGL_ASSERT(_idxch_ptr->_is_ready_for_drawing());
			
			GLenum const		tcode	=	_idxch_ptr->_unitTypeForDrawingParameter();
			EEGL_ASSERT_WITH_REASON(tcode == IndexUnitChannel::UnitType::CODE::UINT8 or tcode == IndexUnitChannel::UnitType::CODE::UINT16, "Currently, only UINT8 and UIN16 is considered. Otherwise code review is required.");
			
			Size const			usz		=	tcode == IndexUnitChannel::UnitType::CODE::UINT8 ? 1 : 2;
			Size const			offset	=	usz * index;
			GLvoid const* const	ptr		=	_idxch_ptr->_pointerForDrawingParameter();
			GLvoid const* const	ptr2	=	CONVPTR(CONVPTR(ptr).uint + offset).ptr;
			
			if (Doctor::useStateValidation())
			{
				Size const		reqlen	=	usz * count;
				Size const		reqrun	=	offset + reqlen;
				Size const		curlen	=	_idxch_ptr->_lengthOfData();
				
				std::string const	errdesc	=	Doctor::stringWithCFormat("Currently bound index-data does not have enough data to draw specified range of indexes. (required: offset + length = %llu + %llu = %llu bytes, current data: length = %llu bytes)", uint64_t(offset), uint64_t(reqlen), uint64_t(reqrun), uint64_t(curlen));
				EEGL_ASSERT_WITH_REASON(curlen >= reqrun, errdesc);
			}
			
			////
			
			GLsizei const	count2	=	GLsizei(count);
			
			eeglDrawElement(GLenum(mode), count2, tcode, ptr2);
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		auto Machine::
		query() const -> Query const&
		{
			return	*_query;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
#pragma mark	-	Deprecated Methods
		
		
		void
		Machine::setScissor(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Bounds2 bounds)
		{
			EEGL_ASSERT(not bounds.isNaN());
			EEGL_ASSERT(bounds != Bounds2::Utility::infinity());
			EEGL_ASSERT(not _dbg_has_scissor);
			Vector2	sz	=	bounds.size();
			eeglEnable(GL_SCISSOR_TEST);
			eeglScissor(bounds.minimum.x, bounds.minimum.y, sz.x, sz.y);
			
			if (Doctor::useStateValidation())
			{
				_dbg_has_scissor	=	true;
			}
		}
		void
		Machine::unsetScissor()
		{
			if (Doctor::useStateValidation())
			{
				EEGL_ASSERT(_dbg_has_scissor);
				_dbg_has_scissor	=	false;
			}
			
			eeglDisable(GL_SCISSOR_TEST);
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