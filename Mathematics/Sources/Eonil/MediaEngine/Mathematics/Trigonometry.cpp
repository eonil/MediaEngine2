//
//  Trigonometry.cpp
//  Mathematics
//
//  Created by Hoon H. on 14/5/24.
//
//

#include "Trigonometry.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_TRIGONOMETRY_NAMESPACE_BEGIN
using namespace	Geometry;

/*!
 Replace these function implementations to better one if you need...
 */




auto
sine(Scalar const& o) -> Scalar
{
	return	std::sin(o);
}

auto
cosine(Scalar const& o) -> Scalar
{
	return	std::cos(o);
}

auto
tangent(Scalar const& o) -> Scalar
{
	return	std::tan(o);
}


auto
arcsine(Scalar const& o) -> Scalar
{
	return	std::asin(o);
}

auto
arccosine(Scalar const& o) -> Scalar
{
	return	std::acos(o);
}

auto
arctangent(Scalar const& o) -> Scalar
{
	return	std::atan(o);
}



EONIL_MEDIA_ENGINE_MATHEMATICS_TRIGONOMETRY_NAMESPACE_END