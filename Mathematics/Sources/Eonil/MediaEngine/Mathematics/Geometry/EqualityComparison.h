//
//  EqualityComparison.h
//  Mathematics
//
//  Created by Hoon H. on 14/5/24.
//
//

#pragma once
#include "../Common.h"
#include "Vector.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN





auto	default_epsilon() -> Geometry::Scalar;
auto	default_tolerance() -> Geometry::Scalar;
auto	almost_equals(Geometry::Scalar const& a, Geometry::Scalar const& b, Geometry::Scalar const& tolerance = default_tolerance()) -> bool;
auto	almost_equals(Geometry::Vector3 const& a, Geometry::Vector3 const& b, Geometry::Scalar const& tolerance = default_tolerance()) -> bool;
auto	almost_normalized(Geometry::Vector3 const& a, Geometry::Scalar const& tolerance = default_tolerance()) -> bool;






EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END

