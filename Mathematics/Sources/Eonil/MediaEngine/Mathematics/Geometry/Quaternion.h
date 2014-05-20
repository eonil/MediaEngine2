//
//  Quaternion.h
//  Mathematics
//
//  Created by Hoon Hwangbo on 6/11/13.
//
//

#pragma once
#include "../Common.h"
#include "AxisAngle.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN

/*!
 Memory layout and component semantics of quaternion is implementation detail, 
 and fully hidden except it's built with 4 scalars.
 
 @classdesign
 Fully based on GLM quaternion. No GLK quaternion feature is employed due to undefined memory layout.
 */
struct
Quaternion
{
private:
	union
	{
		Scalar	components[4];
	};
	
public:
	bool const	operator==(Quaternion const& other) const;
	bool const	operator!=(Quaternion const& other) const;
	
	Quaternion const	operator+(Quaternion const& other) const;
	Quaternion const	operator-(Quaternion const& other) const;
	Quaternion const	operator*(Quaternion const& other) const;
	
	/*
	 Quaternion division is not well defined mathmatically, so it's excluded.
	 */
	
//				Quaternion const	operator*(Scalar const& other) const;			//	Scalar multiplication of quaternion.
//				Quaternion const	operator/(Scalar const& other) const;			//	Scalar multiplication of quaternion.
	
	Quaternion const	conjugation() const;
	Quaternion const	inversion() const;
	Quaternion const	norm() const;
	
	AxisAngle const		asAxisAngle() const;							//	Calculates a new `AxisAngle` object which semantically same with this object.
//				Vector4 const		asVector4() const;								//	Just reinterpretation as `Vector4` type. Source and result equals in binary.
	
public:
	struct
	Utility
	{
		Utility() = delete;
		
		static Quaternion const		identity();
		static Quaternion const		quaternionWithAxisAngle(AxisAngle const aa);
//					static Quaternion const		quaternionBySamplingUsingSphericalLinearInterpolation(Quaternion const a, Quaternion const b, Scalar const t);
		static Quaternion const		quaternionBySamplingUsingSphericalQuadraticInterpolation(Quaternion const a, Quaternion const b, Quaternion const c, Quaternion const d, Scalar const t);
	};
}
__attribute__((aligned(16)));








EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END