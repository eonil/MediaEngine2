//
//  Trigonometry.h
//  Mathematics
//
//  Created by Hoon H. on 14/5/24.
//
//

#pragma once
#include "Common.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_TRIGONOMETRY_NAMESPACE_BEGIN
using namespace	Geometry;

auto	sine(Scalar const&) -> Scalar;
auto	cosine(Scalar const&) -> Scalar;
auto	tangent(Scalar const&) -> Scalar;

auto	arcsine(Scalar const&) -> Scalar;
auto	arccosine(Scalar const&) -> Scalar;
auto	arctangent(Scalar const&) -> Scalar;


EONIL_MEDIA_ENGINE_MATHEMATICS_TRIGONOMETRY_NAMESPACE_END