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
	CODE : sz
	{
		NONE		=	0,
		BEGIN,
		CONTINUE,
		END,
		CANCEL,
	};
	
	CODE	code		{CODE::NONE};
	sz		identifier	{0};
	sz		tick		{0};
	Vector2	coordinate	{0,0};
	
	Touch() = default;
	Touch(CODE const& code, sz const& identifier, sz const& tick, Vector2 const& coordinate) : identifier(identifier), code(code), tick(tick), coordinate(coordinate) {}
};








EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_END

