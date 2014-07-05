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

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Server
{
	using namespace Stub;
	
	
	
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
		
		////
		if (USE_DEBUGGING_ASSERTIONS)
		{
			log9_just_print_line("OpenGL system vendor: " + str((char const*)eeglGetString(GL_VENDOR)));
			log9_just_print_line("`Server::Machine`'s vertex-attribute-channel count: " + std::to_string(maxc));
		}
		////
		
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
	Machine::vertexAttributeChannelAtIndex(const sz index) const
	{
		EEGL_ASSERT(index < _chs.size());
		return	_chs[index];
	}
	VertexAttributeChannel&
	Machine::vertexAttributeChannelAtIndex(const sz index)
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
	Machine::textureUnitAtIndex(const sz index) const
	{
		return 	_tus.at(index);
	}
	TextureSampler&
	Machine::textureUnitAtIndex(const sz index)
	{
		return	_tus.at(index);
	}
	
	
	
	
	
	
				
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	auto Machine::
	setFramebuffer(const Server::Framebuffer &framebuffer) -> void
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
	useProgram(const Server::Program &program) -> void
	{
		/*
		 `glUseProgram` is quiet expensive.
		 Redundant call to the function can be eliminated by shadowing states.
		 */
		
		EEGL_ASSERT(_validity_program_designation == false);
		_validity_program_designation	=	true;
		eeglUseProgram(program.name());
	}
	auto Machine::
	unuseProgram() -> void
	{
		/*
		 This call is actually not required, but exosts to ensure state management.
		 Can be optionally removed by shadowing state.
		 */
		
		EEGL_ASSERT(_validity_program_designation == true);
		eeglUnuseProgram();
		_validity_program_designation	=	false;
	}
	auto Machine::
	executeBlockWithProgram(const Server::Program &program, std::function<void ()> block) -> void
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
	Machine::setViewport(const Bounds2 bounds)
	{
		EEGL_ASSERT(not bounds.isNaN());
		EEGL_ASSERT(bounds != Bounds2::Utility::infinity());
		EEGL_ASSERT(not _validity_of_viewport);
		
		Vector2	sz	=	bounds.size();
		eeglViewport(bounds.minimum.x, bounds.minimum.y, sz.x, sz.y);
		
		if (USE_DEBUGGING_ASSERTIONS)
		{
			_validity_of_viewport	=	true;
		}
	}
	
	void
	Machine::unsetViewport()
	{
		EEGL_ASSERT(_validity_of_viewport);
		if (USE_DEBUGGING_ASSERTIONS)
		{
			_validity_of_viewport	=	false;
		}
	}
	
	
	
	
	
	
	void
	Machine::drawArrays(const DrawingMode mode, const sz index, const sz count)
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion((mode != DrawingMode::TRIANGLES) or (count % 3 == 0), "If the drawing-mode is TRIANGLES, then selected vertex count must be multiplication of 3.");
			err9_converted_legacy_assertion((mode != DrawingMode::TRIANGLE_STRIP) or (count > 3), "If the drawing-mode is TRIANGLE_STRIP, then selected vertex count must be equal or larger then 3.");
			err9_converted_legacy_assertion((mode != DrawingMode::LINES) or (count % 2 == 0), "If the drawing-mode is LINES, then selected vertex count must be even number.");
			
			assertForUnsignedNumericRange<sz, GLint>(index);
			assertForUnsignedNumericRange<sz, GLsizei>(count);
			err9_converted_legacy_assertion(_validity_of_viewport == true, "Viewport must be set before perform any drawing.");
			
			if (USE_DEBUGGING_ASSERTIONS)
			{
				for (GLuint i=0; i<_chs.size(); i++)
				{
					GLuint				_idx	=	i;
					
					bool const			enabled	=	eeglGetVertexAttribi(_idx, GL_VERTEX_ATTRIB_ARRAY_ENABLED) != 0;
					GLint				size	=	eeglGetVertexAttribi(_idx, GL_VERTEX_ATTRIB_ARRAY_SIZE);
					GLint				bufname	=	eeglGetVertexAttribi(_idx, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);
					GLvoid*				memptr	=	eeglGetVertexAttribPointerv(_idx, GL_VERTEX_ATTRIB_ARRAY_POINTER);
					EEGL_ASSERT_WITH_REASON(not enabled or size != 0, "A vertex channel should be not-enabled or should have specified size if enabled.");
					EEGL_ASSERT_WITH_REASON(not enabled or bufname != 0 or memptr != NULL, "A vertex channel should be not-enabled. If enabled, it should have specified buffer name or non-`NULL` client memory address.");
				}
			}
			
			err9_converted_legacy_assertion(index <= std::numeric_limits<GLint>::max());
		}
		
		////
		
		GLint const		index2	=	GLint(index);
		GLsizei const	count2	=	toGLsizei(count);
		
		eeglDrawArrays(GLenum(mode), index2, count2);
	}
	
	
	
	void
	Machine::drawElements(const DrawingMode mode, const sz index, const sz count)
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion((mode != DrawingMode::TRIANGLES) or (count % 3 == 0), "If the drawing-mode is TRIANGLES, then selected vertex count must be multiplication of 3.");
			err9_converted_legacy_assertion((mode != DrawingMode::TRIANGLE_STRIP) or (count >= 3), "If the drawing-mode is TRIANGLE_STRIP, then selected vertex count must be equal or larger then 3.");
			err9_converted_legacy_assertion((mode != DrawingMode::LINES) or (count % 2 == 0), "If the drawing-mode is LINES, then selected vertex count must be even number.");
			
			assertForUnsignedNumericRange<sz, GLuint>(count);
			err9_converted_legacy_assertion(_validity_of_viewport == true, "Viewport must be set before perform any drawing.");
			err9_converted_legacy_assertion(_idxch_ptr->_is_ready_for_drawing());
			
		}
		
		////
		
		GLenum const		tcode	=	_idxch_ptr->_unitTypeForDrawingParameter();
		
		////
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(tcode == IndexUnitChannel::UnitType::CODE::UINT8 or tcode == IndexUnitChannel::UnitType::CODE::UINT16, "Currently, only UINT8 and UIN16 is considered. Otherwise code review is required.");
		}
		////
		
		sz const			usz		=	tcode == IndexUnitChannel::UnitType::CODE::UINT8 ? 1 : 2;
		sz const			offset	=	usz * index;
		GLvoid const* const	ptr		=	_idxch_ptr->_pointerForDrawingParameter();
		GLvoid const* const	ptr2	=	CONVPTR(CONVPTR(ptr).uint + offset).ptr;
		
		////
		if (USE_DEBUGGING_ASSERTIONS)
		{
			sz const		reqlen	=	usz * count;
			sz const		reqrun	=	offset + reqlen;
			sz const		curlen	=	_idxch_ptr->_lengthOfData();
			str const		errdesc	=	"Currently bound index-data does not have enough data to draw specified range of indexes. (required: offset + length = " + std::to_string(offset) + " + " + std::to_string(reqlen) + " = " + std::to_string(reqrun) + " bytes, current data: length = " + std::to_string(curlen) + " bytes)";

			err9_converted_legacy_assertion(curlen >= reqrun, errdesc);
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
	Machine::setScissor(const Bounds2 bounds)
	{
		EEGL_ASSERT(not bounds.isNaN());
		EEGL_ASSERT(bounds != Bounds2::Utility::infinity());
		EEGL_ASSERT(not _dbg_has_scissor);
		Vector2	sz	=	bounds.size();
		eeglEnable(GL_SCISSOR_TEST);
		eeglScissor(bounds.minimum.x, bounds.minimum.y, sz.x, sz.y);
		
		if (USE_DEBUGGING_ASSERTIONS)
		{
			_dbg_has_scissor	=	true;
		}
	}
	void
	Machine::unsetScissor()
	{
		if (USE_DEBUGGING_ASSERTIONS)
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

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END
