//
//  Exceptions.cpp
//  Mathematics
//
//  Created by Hoon H. on 14/5/19.
//
//

#include "Exceptions.h"
#include "../Geometry/Vector.h"
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
default_epsilon() -> Geometry::Scalar
{
	return	std::numeric_limits<Geometry::Scalar>::epsilon();
}
auto
almost_equals(Geometry::Scalar const& a, Geometry::Scalar const& b, Geometry::Scalar const& epsilon) -> bool
{
	if (USE_EXCEPTIONS)
	{
		error_if(epsilon < 0);
	}
	
	////
	
	return	std::abs(a - b) < epsilon;
}
auto
almost_equals(Geometry::Vector3 const& a, Geometry::Vector3 const& b, Geometry::Scalar const& epsilon) -> bool
{
	if (USE_EXCEPTIONS)
	{
		error_if(epsilon < 0);
	}
	
	////
	
	return	(a - b).length() < epsilon;
}





EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_END


