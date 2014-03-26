//
//  VertexAttributeChannel.h
//  EonilGraphics
//
//  Created by Eonil on 5/1/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__VertexAttributeChannel__
#define __EonilGraphics__VertexAttributeChannel__

#include "../../Common.h"
#include "../Declarations.h"
#include "../Buffer.h"
#include "../_Legacy2013Compat.h"
#include "../../Value/StronglyTypingNumericValue.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		namespace
		Machinery
		{
			
#if	EONIL_MEDIA_ENGINE_DEBUG_MODE
			class
			VertexAttributeChannelIndex final : public Value::StronglyTypingNumericValue<VertexAttributeChannelIndex, GLuint>
			{
			public:
				using	Value::StronglyTypingNumericValue<VertexAttributeChannelIndex, GLuint>::StronglyTypingNumericValue;
			};
#else
			using	VertexAttributeChannelIndex	=	GLuint;
#endif
			
			
			
			
			
			
			
			
			
			
			
			
			
			/*!
			 A pointer to a vertex-attribute channel of a machine.
			 
			 @discussion
			 Linked data source (regardless of client or server) will be used while drawing something
			 with GL API. And the data required while drawing. Anyway this object doesn't keep the data
			 sources alive, so it's your responsibility to keep them alive while drawing.
			 
			 @classdesign
			 This is a value object is a pointer to virtual channel for vertex attributes. Treat this 
			 just like any other pointer type. (prefere copy rather than referencing)
			 */
			class
			VertexAttributeChannel 
			{
				friend class	Server::Machine;
				
				////
				
				Machine*							_machine	=	nullptr;			//	GL API is strictly single-machine design. This variable is actually meaningless, but for validity check. This will likely to become debug-only variable.
				VertexAttributeChannelIndex			_idx		=	-1;
				
				////
				
				
				////
				
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_INLINE_FIELD(ptr<ArrayBuffer const>, _dbg_cur_ab_ptr{nullptr});
				auto	_assert_ready_for_drawing() const -> void;		//!	Checks whether this channel is established and can be used for rendering or not.
				
				
				
			public:
				
				enum class
				ComponentSize : GLint
				{
					ZERO	=	0,					//	Invalid state.
					ONE		=	1,
					TWO		=	2,
					THREE	=	3,
					FOUR	=	4,
				};
				enum class
				ComponentType : GLenum
				{
					NONE	=	0,					//	Invalid state.
					BYTE	=	GL_BYTE,
					UBYTE	=	GL_UNSIGNED_BYTE,
					SHORT	=	GL_SHORT,
					USHORT	=	GL_UNSIGNED_SHORT,
					FLOAT	=	GL_FLOAT,
#if	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
					FIXED	=	GL_FIXED,
#endif
				};
				

				struct
				Format
				{
					Size				dataOffset			=	0;
					ComponentSize		componentCount		=	ComponentSize::ZERO;		//	Asserted in debug version for invalid state.
					ComponentType		componentType		=	ComponentType::NONE;		//	Asserted in debug version for invalid state.
					GLboolean			normalization		=	GL_FALSE;					
					GLsizei				strideSizeInBytes	=	0;							//	Asserted in debug version for invalid state.
				};
				
			public:
				VertexAttributeChannel() = default;
				VertexAttributeChannel(VertexAttributeChannel const&) = default;
				VertexAttributeChannel(VertexAttributeChannel&&) = default;
				VertexAttributeChannel(Machine* machine, Size const& index);
				VertexAttributeChannel(Machine* machine, GLuint const& index);
				
				auto	operator==(VertexAttributeChannel const&) const -> bool;
				auto	operator!=(VertexAttributeChannel const&) const -> bool;
				
				auto	index() const -> GLuint;											//	Generic vertex attribute index.
				
			public:
				auto	linkWithClientMemory(void const* const memory, Format const format) -> void;
				auto	linkWithServerBuffer(ArrayBuffer const& buffer, Format const format) -> void;
				auto	unlink() -> void;
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
			public:
				auto	description() const -> str;
			};

		}
	}










}}}}

#endif /* defined(__EonilGraphics__VertexAttributeChannel__) */
