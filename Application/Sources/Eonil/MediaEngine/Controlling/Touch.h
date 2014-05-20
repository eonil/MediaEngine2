//
//  Touch.h
//  TheMagnetismGame
//
//  Created by Hoon H. on 4/16/14.
//  Copyright (c) 2014 Eonil Company. All rights reserved.
//

#pragma once
#include "Common.h"
EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_BEGIN








struct
Touch
{
public:
	enum class
	CODE : Size
	{
		NONE		=	0,
		BEGIN,
		CONTINUE,
		END,
		CANCEL,
	};
	
	CODE	code		{CODE::NONE};
	Size	identifier	{0};
	Size	tick		{0};
	Vector2	coordinate	{0,0};
	
	Touch() = default;
	Touch(CODE const& code, Size const& identifier, Size const& tick, Vector2 const& coordinate) : identifier(identifier), code(code), tick(tick), coordinate(coordinate) {}
};








EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_END

