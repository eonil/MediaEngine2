//
//  Symbols.h
//  Graphics
//
//  Created by Hoon H. on 2/19/14.
//
//

#ifndef __Graphics__Symbols__
#define __Graphics__Symbols__

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		
		
		
		
		
		
		
		enum class
		DrawingMode : GLenum
		{
			POINTS			=	GL_POINTS,
			LINE_STRIP		=	GL_LINE_STRIP,
			LINE_LOOP		=	GL_LINE_LOOP,
			LINES			=	GL_LINES,
			TRIANGLE_STRIP	=	GL_TRIANGLE_STRIP,
			TRIANGLE_FAN	=	GL_TRIANGLE_FAN,
			TRIANGLES		=	GL_TRIANGLES,
		};
		enum class
		BlendingMode : GLenum
		{
			ZERO						=	GL_ZERO,
			ONE							=	GL_ONE,
			SOURCE_COLOR				=	GL_SRC_COLOR,
			DESTINATION_COLOR			=	GL_DST_COLOR,
			SOURCE_ALPHA				=	GL_SRC_ALPHA,
			DESTINATION_ALPHA			=	GL_DST_ALPHA,
			ONE_MINUS_SOURCE_COLOR		=	GL_ONE_MINUS_SRC_COLOR,
			ONE_MINUS_DESTINATION_COLOR	=	GL_ONE_MINUS_DST_COLOR,
			ONE_MINUS_SOURCE_ALPHA		=	GL_ONE_MINUS_SRC_ALPHA,
			ONE_MINUS_DESTINATION_ALPHA	=	GL_ONE_MINUS_DST_ALPHA,
			ONE_MINUS_CONSTANT_COLOR	=	GL_ONE_MINUS_CONSTANT_COLOR,
			ONE_MINUS_CONSTANT_ALPHA	=	GL_ONE_MINUS_CONSTANT_ALPHA,
			CONSTANT_COLOR				=	GL_CONSTANT_COLOR,
			CONSTANT_ALPHA				=	GL_CONSTANT_ALPHA,
			SOURCE_ALPHA_SATURATE		=	GL_SRC_ALPHA_SATURATE,			//	This is the only value which is not supported as destination blending.
		};
		
		
		
		
		
	}		
			
}}}}

#endif /* defined(__Graphics__Symbols__) */
