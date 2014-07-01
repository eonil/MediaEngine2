//
//  NaNCheck.h
//  Mathematics
//
//  Created by Hoon H. on 14/7/2.
//
//

#pragma once
#include "../Common.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_BEGIN





auto	has_nan(Geometry::Scalar const&) -> bool;
auto	has_nan(Geometry::Vector2 const&) -> bool;
auto	has_nan(Geometry::Vector3 const&) -> bool;
auto	has_nan(Geometry::Vector4 const&) -> bool;
auto	has_nan(Geometry::Matrix4 const&) -> bool;



EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_END

