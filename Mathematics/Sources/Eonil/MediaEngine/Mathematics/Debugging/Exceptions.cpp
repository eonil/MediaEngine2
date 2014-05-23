//
//  Exceptions.cpp
//  Mathematics
//
//  Created by Hoon H. on 14/5/19.
//
//

#include "Exceptions.h"
#include "../Geometry/Vector.h"
#include "../Geometry/Matrix.h"
#include <iostream>
EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_BEGIN







namespace
{
	static char const*	DEFAULT_DOMAIN	=	"Eonil::MediaEngine::Mathematics";
	
	static inline auto
	log(std::string const& msg) -> void
	{
		std::cout << msg << "\n";
	}
}



auto
error_if(bool const cond, std::string const& message) -> void
{
	if (cond)
	{
		auto	exc	=	Error(DEFAULT_DOMAIN, message);
		log(exc.what());
		throw	exc;
	}
}

auto
halt_if(bool const cond, std::string const& message) -> void
{
	if (cond)
	{
		auto	exc	=	Halt(DEFAULT_DOMAIN, message);
		
		log(exc.what());
		throw	exc;
	}
}

		
		
		
		
		
		
		
		
		
auto
has_nan(Geometry::Scalar const& o) -> bool
{
	return	std::isnan(o);
}
auto
has_nan(Geometry::Vector2 const& o) -> bool
{
	for (auto const& v: o.components)
	{
		if (std::isnan(v))
		{
			return	true;
		}
	}
	return	false;
}
auto
has_nan(Geometry::Vector3 const& o) -> bool
{
	for (auto const& v: o.components)
	{
		if (std::isnan(v))
		{
			return	true;
		}
	}
	return	false;
}
auto
has_nan(Geometry::Vector4 const& o) -> bool
{
	for (auto const& v: o.components)
	{
		if (std::isnan(v))
		{
			return	true;
		}
	}
	return	false;
}
auto
has_nan(Geometry::Matrix4 const& o) -> bool
{
	for (auto const& v: o.components)
	{
		if (std::isnan(v))
		{
			return	true;
		}
	}
	return	false;
}

		




EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_END


