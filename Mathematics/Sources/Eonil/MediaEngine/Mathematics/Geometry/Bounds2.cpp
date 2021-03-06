//
//  Bounds2.cpp
//  Mathematics
//
//  Created by Eonil on 5/1/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include	"Bounds2.h"
#include	"../Common.h"
#include	"../Debugging/NaNCheck.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN










namespace
{
	using namespace	Debugging;
	
	Scalar const
	SCALAR_NAN()
	{
		return	std::numeric_limits<Scalar>::signaling_NaN();
	}
	Vector2 const
	VECTOR_NAN()
	{
		return	Vector2(SCALAR_NAN(), SCALAR_NAN());
	}
	
	
	bool const
	ALL_NAN(Vector2 const& v)
	{
		return	std::isnan(v.x) and std::isnan(v.y);
	}
//			bool const
//			ALL_NON_NAN(Vector2 const& v)
//			{
//				return	not std::isnan(v.x) and not std::isnan(v.y);
//			}
	bool const
	ALL_NAN(Bounds2 const& v)
	{
		return	ALL_NAN(v.minimum) and ALL_NAN(v.maximum);
	}
	bool const
	ALL_NON_NAN(Bounds2 const& v)
	{
		return	not ALL_NAN(v.minimum) and not ALL_NAN(v.maximum);
	}
	
	void
	ASSERT_LEGAL_STATE(Bounds2 const& b)
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err1_recoverable_bad_input_parameter_if(not (ALL_NAN(b) or ALL_NON_NAN(b)), "A `Bounds2` instance must be null-state(all-NAN) or numeric-state(all-non-NAN). Partial NAN is illegal.");
			err1_recoverable_bad_input_parameter_if(not (ALL_NAN(b) or b.minimum.x <= b.maximum.x));
			err1_recoverable_bad_input_parameter_if(not (ALL_NAN(b) or b.minimum.y <= b.maximum.y));
		}
//		EONIL_MEDIA_ENGINE_MATH_ASSERT_WITH_REASON(ALL_NAN(b) or ALL_NON_NAN(b), "A `Bounds2` instance must be null-state(all-NAN) or numeric-state(all-non-NAN). Partial NAN is illegal.");
//		EONIL_MEDIA_ENGINE_MATH_ASSERT(ALL_NAN(b) or b.minimum.x <= b.maximum.x);
//		EONIL_MEDIA_ENGINE_MATH_ASSERT(ALL_NAN(b) or b.minimum.y <= b.maximum.y);
	}
	
	void
	ASSERT_NON_NULL(Bounds2 const& b)
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err1_recoverable_bad_input_parameter_if(not ALL_NON_NAN(b));
		}
//		EONIL_MEDIA_ENGINE_MATH_ASSERT(ALL_NON_NAN(b));
	}
}




Bounds2::Bounds2() : Bounds2(VECTOR_NAN(), VECTOR_NAN())
{
}
Bounds2::Bounds2(Scalar const x, Scalar const y) : Bounds2(Vector2(x, y), Vector2(x, y))
{
}
Bounds2::Bounds2(Vector2 const minimum, Vector2 const maximum) : minimum(minimum), maximum(maximum)
{
	ASSERT_LEGAL_STATE(*this);
}
Bounds2::Bounds2(Scalar const minX, Scalar const minY, Scalar const maxX, Scalar const maxY) : Bounds2(Vector2(minX, minY), Vector2(maxX, maxY))
{
}







bool const
Bounds2::operator==(const Bounds2 &other) const
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_LEGAL_STATE(other);
		ASSERT_NON_NULL(*this);
		ASSERT_NON_NULL(other);
	}
	
	////
	
	return	minimum == other.minimum and maximum == other.maximum;
}
bool const
Bounds2::operator!=(const Bounds2 &other) const
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_LEGAL_STATE(other);
		ASSERT_NON_NULL(*this);
		ASSERT_NON_NULL(other);
	}
	
	////
	
	return	minimum != other.minimum or maximum != other.maximum;
}
//			bool const
//			Bounds2::operator==(const decltype(nullptr) null) const
//			{
//				ASSERT_LEGAL_STATE(*this);
//				return	ALL_NAN(*this);
//			}
//			bool const
//			Bounds2::operator!=(const decltype(nullptr) null) const
//			{
//				ASSERT_LEGAL_STATE(*this);
//				return	not ALL_NAN(*this);
//			}








Vector2 const
Bounds2::center() const
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_NON_NULL(*this);
	}
	
	////
	
	Scalar	midX	=	(minimum.x + maximum.x) * 0.5;
	Scalar	midY	=	(minimum.y + maximum.y) * 0.5;
	return	Vector2(midX, midY);
}
Vector2 const
Bounds2::size() const
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_NON_NULL(*this);
	}
	
	////
	
	return	Vector2(maximum.x - minimum.x, maximum.y - minimum.y);
}
Scalar const
Bounds2::aspectRatio() const
{
	Vector2	sz0	=	size();
	return	sz0.x / sz0.y;
}
Scalar const
Bounds2::width() const
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_NON_NULL(*this);
	}
	
	////
	
	return	maximum.x - minimum.x;
}
Scalar const
Bounds2::height() const
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_NON_NULL(*this);
	}
	
	////
	
	return	maximum.y - minimum.y;
}
bool const
Bounds2::isNaN() const
{
	return	ALL_NAN(*this);
}
bool const
Bounds2::isEmpty() const
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
	}
	
	////
	
	return	minimum.x == maximum.x and minimum.y == maximum.y;
}
bool const
Bounds2::isIntegral() const
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
	}
	
	////
	
	return	roundf(minimum.x) == minimum.x
	and		roundf(minimum.y) == minimum.y
	and		roundf(maximum.x) == maximum.x
	and		roundf(maximum.y) == maximum.y
	;
}





Bounds2 const
Bounds2::integralBounds2ByRounding() const
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_NON_NULL(*this);
	}
	
	////
	
	return	Bounds2(roundf(minimum.x), roundf(minimum.y), roundf(maximum.x), roundf(maximum.y));
}

bool const
Bounds2::containsPoint(const Vector2 point) const
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_NON_NULL(*this);
	}
	
	////
	
	return	point.x >= minimum.x and point.x <= maximum.x and point.y >= minimum.y and point.y <= maximum.y;
}
bool const
Bounds2::intersectsWith(const Bounds2 bounds) const
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_LEGAL_STATE(bounds);
		ASSERT_NON_NULL(*this);
		ASSERT_NON_NULL(bounds);
	}
	
	////
	
	return	not intersectionWith(bounds).isNaN();
}
Bounds2 const
Bounds2::intersectionWith(const Bounds2 bounds) const
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_LEGAL_STATE(bounds);
		ASSERT_NON_NULL(*this);
		ASSERT_NON_NULL(bounds);
	}
	
	////
	
	if (this->isNaN() or bounds.isNaN())
	{
		return	Bounds2::Utility::NaN();
	}
	
	Vector2		min	=	Vector2::Utility::maximumOfVectors(minimum, bounds.minimum);
	Vector2		max	=	Vector2::Utility::minimumOfVectors(maximum, bounds.maximum);
	if (min.x > max.x or min.y > max.y)
	{
		return	Bounds2::Utility::NaN();
	}
	else
	{
		return	Bounds2(min, max);
	}
}
Bounds2 const
Bounds2::boundsWithDisplacementOfEdges(const Vector2 f) const
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_NON_NULL(*this);
	}
	
	////
	
	Bounds2	b1	=	*this;
	b1.displaceEdges(f);
	return	b1;
}
Bounds2 const
Bounds2::boundsWithTransformationByMatrix(const Matrix4 m) const
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_NON_NULL(*this);
	}
	
	////
	
	Bounds2	r1	=	*this;
	r1.transformByMatrix(m);
	return	r1;
}













void
Bounds2::displaceEdges(const Vector2 f)
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_NON_NULL(*this);
	}
	
	////
	
	displaceEdgesHorizontally(f.x);
	displaceEdgesVertically(f.y);
}
void
Bounds2::displaceEdgesHorizontally(const Scalar f)
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_NON_NULL(*this);
	}
	
	////
	
	minimum.x	-=	f;
	maximum.x	+=	f;
}
void
Bounds2::displaceEdgesVertically(const Scalar f)
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_NON_NULL(*this);
	}
	
	////
	
	minimum.y	-=	f;
	maximum.y	+=	f;
}
void
Bounds2::transformByMatrix(const Matrix4 m)
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		ASSERT_LEGAL_STATE(*this);
		ASSERT_NON_NULL(*this);
	}
	
	////
	
	Vector4	min0	=	Vector4(minimum, 0, 1);
	Vector4	max0	=	Vector4(maximum, 0, 1);
	Vector4	min1	=	m.transform(min0);
	Vector4	max1	=	m.transform(max0);
	Vector2	min2	=	Vector2(min1.x, min1.y);
	Vector2	max2	=	Vector2(max1.x, max1.y);
	minimum			=	min2;
	maximum			=	max2;
}











Bounds2 const
Bounds2::Utility::NaN()
{
	return	Bounds2(VECTOR_NAN(), VECTOR_NAN());
}
Bounds2 const
Bounds2::Utility::zero()
{
	return	Bounds2(0,0,0,0);
}
Bounds2 const
Bounds2::Utility::infinity()
{
	return	Bounds2(Vector2(-std::numeric_limits<Scalar>::infinity(), -std::numeric_limits<Scalar>::infinity()),
					Vector2(+std::numeric_limits<Scalar>::infinity(), +std::numeric_limits<Scalar>::infinity()));
}
Bounds2 const
Bounds2::Utility::boundsWithPointWithZeroSize(const Vector2 point)
{
	return	Bounds2(point.x, point.y, point.x, point.y);
}
Bounds2 const
Bounds2::Utility::boundsWithMinimumPointAndSize(const Vector2 point, const Vector2 size)
{
	return	Bounds2(point, point + size);
}

Bounds2 const
Bounds2::Utility::boundsWithMaximumPointAndSize(const Vector2 point, const Vector2 size)
{
	return	Bounds2(point - size, point);
}

















EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END
