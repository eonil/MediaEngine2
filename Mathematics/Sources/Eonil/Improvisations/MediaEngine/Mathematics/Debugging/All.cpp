//
//  All.cpp
//  Mathematics
//
//  Created by Hoon H. on 2014/05/19.
//
//

#include "All.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_BEGIN







namespace
{
	static char const*	DEFAULT_DOMAIN	=	"Eonil::MediaEngine::Mathematics";
}

auto
throw_if(bool const cond, std::string const& message) -> void
{
	if (cond)
	{
		throw	Error(DEFAULT_DOMAIN, message);
	}
}

auto
halt_if(bool const cond, std::string const& message) -> void
{
	if (cond)
	{
		throw	Crash(DEFAULT_DOMAIN, message);
	}
}








EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_END

