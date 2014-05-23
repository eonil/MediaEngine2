//
//  Exceptions.h
//  Mathematics
//
//  Created by Hoon H. on 14/5/19.
//
//

#pragma once
#include "../Common.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_BEGIN






struct
Error : Eonil::CommonRealtimeGameAlgorithms::Error
{
	using	Eonil::CommonRealtimeGameAlgorithms::Error::Error;
};

struct
Halt : Eonil::CommonRealtimeGameAlgorithms::Crash
{
	using	Eonil::CommonRealtimeGameAlgorithms::Crash::Crash;
};


static const bool	USE_EXCEPTIONS	=	EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUG_MODE;

auto	error_if(bool const cond, std::string const& message = Eonil::CommonRealtimeGameAlgorithms::EXCEPTION_DEFAULT_MESSAGE) -> void;
auto	halt_if(bool const cond, std::string const& message = Eonil::CommonRealtimeGameAlgorithms::EXCEPTION_DEFAULT_MESSAGE) -> void;



auto	default_epsilon() -> Geometry::Scalar;
auto	almost_equals(Geometry::Scalar const& a, Geometry::Scalar const& b, Geometry::Scalar const& epsilon = default_epsilon()) -> bool;
auto	almost_equals(Geometry::Vector3 const& a, Geometry::Vector3 const& b, Geometry::Scalar const& epsilon = default_epsilon()) -> bool;





EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_END

