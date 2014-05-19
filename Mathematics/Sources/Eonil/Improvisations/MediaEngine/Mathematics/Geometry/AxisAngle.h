//
//  AxisAngle.h
//  Mathematics
//
//  Created by Hoon Hwangbo on 6/11/13.
//
//

#pragma once
#include "../Common.h"
#include "Vector.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN






struct
AxisAngle
{
	Vector3		axis;			//	A vector in 3-dimensional space.
	Scalar		angle;			//	Angle in radian. Always in radian.
	
	AxisAngle(Vector3 const axis, Scalar const angle) : axis(axis), angle(angle)
	{
	}
	
	bool const	operator==(AxisAngle const& other) const;
	bool const	operator!=(AxisAngle const& other) const;
	
	Quaternion const	asQuaternion() const;
}
__attribute__((aligned(16)));

////

static_assert(sizeof(Scalar) == 4, "");
static_assert(sizeof(AxisAngle) == sizeof(Scalar)*4, "");




EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END
