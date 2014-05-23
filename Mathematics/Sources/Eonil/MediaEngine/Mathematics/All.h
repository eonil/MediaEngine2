//
//  All.h
//  Mathematics
//
//  Created by Hoon H. on 2014/05/19.
//
//

#pragma once

#include "Common.h"
#include "Debugging/Doctor.h"
#include "Trigonometry.h"
#include "Geometry/Bounds.h"
#include "Geometry/Vector.h"
#include "Geometry/Quaternion.h"
#include "Geometry/AxisAngle.h"
#include "Geometry/Matrix.h"
#include "Geometry/Transform.h"
#include "Geometry/_ImmatureFeaturesD1/Interpolation.h"
#include "Geometry/EqualityComparison.h"
//#include "Geometry/Spline.h"

EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN
static_assert(sizeof(Scalar) == 4, "Size of `Scalar` must be 4 bytes.");
static_assert(sizeof(Vector2) == sizeof(Geometry::Scalar) * 2, "Size of `Vector4` must be 2 `Scalar` size.");
static_assert(sizeof(Vector3) == sizeof(Geometry::Scalar) * 3, "Size of `Vector4` must be 3 `Scalar` size.");
static_assert(sizeof(Vector4) == sizeof(Geometry::Scalar) * 4, "Size of `Vector4` must be 4 `Scalar` size.");
static_assert(sizeof(Quaternion) == sizeof(Geometry::Scalar) * 4, "Size of `Quaternion` must be 4 `Scalar` size.");
static_assert(sizeof(AxisAngle) == sizeof(Geometry::Scalar) * 4, "Size of `AxisAngle` must be 4 `Scalar` size.");
static_assert(sizeof(Matrix4) == sizeof(Geometry::Scalar) * 16, "Size of `Matrix4` must be 16 `Scalar` size.");
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END



