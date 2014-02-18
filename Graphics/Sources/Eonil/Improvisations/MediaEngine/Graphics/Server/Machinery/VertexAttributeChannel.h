//
//  VertexAttributeChannel.h
//  EonilGraphics
//
//  Created by Eonil on 5/1/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__VertexAttributeChannel__
#define __EonilGraphics__VertexAttributeChannel__

#include "../Buffer.h"
#include "../_Legacy2013Compat.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		namespace
		Machinery
		{
			
			/*!
			 @discussion
			 Linked data source (regardless of client or server) will be used while drawing something
			 with GL API. And the data required while drawing. Anyway this object doesn't keep the data
			 sources alive, so it's your responsibility to keep them alive while drawing.
			 */
			class
			VertexAttributeChannel
			{
				GLuint					_idx		=	-1;
				
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_INLINE_FIELD(ptr<ArrayBuffer const>, _dbg_cur_ab_ptr{nullptr});
				bool				_validity	=	false;		//	This seems debugging-only, but I am not sure... If it is, make it conditional macro.
				
			public:
				
				struct
				ComponentSize
				{
					ComponentSize() = delete;
					
					enum
					CODE : GLint
					{
						ZERO	=	0,
						ONE		=	1,
						TWO		=	2,
						THREE	=	3,
						FOUR	=	4,
					};
				};
				struct
				ComponentType
				{
					ComponentType() = delete;
					
					enum
					CODE : GLenum
					{
						NONE	=	0,
						BYTE	=	GL_BYTE,
						UBYTE	=	GL_UNSIGNED_BYTE,
						SHORT	=	GL_SHORT,
						USHORT	=	GL_UNSIGNED_SHORT,
						FLOAT	=	GL_FLOAT,
#if	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
						FIXED	=	GL_FIXED,
#endif
					};
				};
				
				struct
				Format
				{
					Size				dataOffset			=	0;
					ComponentSize::CODE	componentCount		=	ComponentSize::CODE::ZERO;		//	Invalid value to trigger assertion.
					ComponentType::CODE	componentType		=	ComponentType::CODE::NONE;		//	Invalid value to trigger assertion.
					GLboolean			normalization		=	GL_FALSE;					
					GLsizei				strideSizeInBytes	=	0;								//	Invalid value to trigger assertion.
				};
				
				
				
			public:
				VertexAttributeChannel(GLuint const index);
				GLuint const		index() const;			//	Generic vertex attribute index.
				
			public:				
				auto	linkWithClientMemory(void const* const memory, Format const format) -> void;
				auto	linkWithServerBuffer(ArrayBuffer const& buffer, Format const format) -> void;
				auto	unlink() -> void;
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
			public:
				auto	description() const -> str;
				auto	validity() const -> bool;		//!	Means this channel is established and can be used for rendering.
			};

		}
	}










}}}}

#endif /* defined(__EonilGraphics__VertexAttributeChannel__) */
