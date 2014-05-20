//
//  Symbols.h
//  Graphics
//
//  Created by Hoon H. on 2/19/14.
//
//

#pragma once
#include "../Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		
		
		
		enum class
		FACE : GLenum
		{
			FRONT			=	GL_FRONT,
			BACK			=	GL_BACK,
			BOTH			=	GL_FRONT_AND_BACK,
		};
		
		enum class
		COMPARISON : GLenum
		{
			NEVER					=	GL_NEVER,
			ALWAYS					=	GL_ALWAYS,
			EQUAL					=	GL_EQUAL,
			NOT_EQUAL				=	GL_NOTEQUAL,
			LESS					=	GL_LESS,
			LESS_OR_EQUAL			=	GL_LEQUAL,
			GREATER					=	GL_GREATER,
			GREATOR_OR_EQUAL		=	GL_GEQUAL,
		};

		enum class
		OPERATION : GLenum
		{
			KEEP					=	GL_KEEP,
			ZERO					=	GL_ZERO,
			REPLACE					=	GL_REPLACE,
			INVERT					=	GL_INVERT,			//!	Bit-wise invert.
			INCREASE				=	GL_INCR,
			DECREASE				=	GL_DECR,
			INCREASE_WRAP			=	GL_INCR_WRAP,
			DECREASE_WRAP			=	GL_DECR_WRAP,
		};
		
		
		
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

