//
//  Quaternion.cpp
//  Mathematics
//
//  Created by Hoon Hwangbo on 6/11/13.
//
//

#include "Quaternion.h"
#include "InternalRawAlgorithmStuffs/D2014R2/GLM.h"
#include "InternalRawAlgorithmStuffs/D2014R2/ApplePlatformExtras.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN

/*
 Because I couldn't *ensure* out how each quaternion components are laid on
 memory on GLM and GKL types, I couldn't get memory compatibility.
 (mainly die to lack of time, investigate later)
 
 So I had to fallback to GLM-only code.
 */



namespace
{
	union
	CONV4
	{
		
		Scalar			V[4];
		Quaternion		EEQ;
		Vector4			EEV;
		AxisAngle		EEAA;
		glm::quat		GLMQ;
		
		CONV4(Vector4 const v) : EEV(v) {}
		CONV4(Quaternion const v) : EEQ(v) {}
		CONV4(AxisAngle const v) : EEAA(v) {}
		CONV4(glm::quat const v) : GLMQ(v) {}
	}
	__attribute__((aligned(16)));
	
	static_assert(sizeof(Scalar) == 4, "");
	static_assert(sizeof(CONV4) == sizeof(Scalar) * 4, "");

	////

	
	/*
	 Commented to suppress unused function warning. Uncomment when you want it.
	 */
//			Quaternion const
//			EE(glm::quat const glm)
//			{
//				return	CONV4(glm).EEQ;
//			}
//			
//			glm::quat const
//			GLM(Quaternion const ee)
//			{
//				return	CONV4(ee).GLMQ;
//			}
	
	
//				static_assert(CONV4(Quaternion(1,2,3,4)).EEV == CONV4(GLKQuaternionMake(1,2,3,4)).EEV ,"Two quaternion type component layout should match.");
}

////



#pragma mark	-	GLM Version

bool const
Quaternion::operator==(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Quaternion &other) const
{
	return	CONV4(*this).GLMQ == CONV4(other).GLMQ;
}
Quaternion const
Quaternion::operator+(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Quaternion &other) const
{
	//	Should be per component addition.
	return	CONV4(CONV4(*this).GLMQ + CONV4(other).GLMQ).EEQ;
}
Quaternion const
Quaternion::operator-(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Quaternion &other) const
{
	return	CONV4(CONV4(*this).GLMQ + (-CONV4(other).GLMQ)).EEQ;
}
Quaternion const
Quaternion::operator*(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Quaternion &other) const
{
	return	CONV4(CONV4(*this).GLMQ * CONV4(other).GLMQ).EEQ;
}

Quaternion const
Quaternion::conjugation() const
{
	return	CONV4(glm::conjugate(CONV4(*this).GLMQ)).EEQ;
}
Quaternion const
Quaternion::inversion() const
{
	return	CONV4(glm::inverse(CONV4(*this).GLMQ)).EEQ;
}
Quaternion const
Quaternion::norm() const
{
	return	CONV4(glm::normalize(CONV4(*this).GLMQ)).EEQ;
}

AxisAngle const
Quaternion::asAxisAngle() const
{
	Scalar const	angle	=	glm::angle(CONV4(*this).GLMQ);
	glm::vec3 const	axis	=	glm::axis(CONV4(*this).GLMQ);
	
	return	AxisAngle(Vector3(axis.x, axis.y, axis.z), angle);
}
//			Vector4 const
//			Quaternion::asVector4() const
//			{
//				return	CONV4(*this).EEV;
//			}



////		

Quaternion const
Quaternion::Utility::identity()
{
	return	CONV4(glm::quat()).EEQ;		//	Parameter-less quat ctor creates identity quaternion.
}
Quaternion const
Quaternion::Utility::quaternionWithAxisAngle(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::AxisAngle aa)
{
	glm::vec3	glm_axis_vector(aa.axis.x, aa.axis.y, aa.axis.z);
	float		glm_angle_rad(aa.angle);
	glm::quat	glm_quat(glm::angleAxis(glm_angle_rad, glm_axis_vector));
	
	return	CONV4(glm_quat).EEQ;
}
//			Quaternion const
//			quaternionBySamplingUsingSphericalLinearInterpolation(Quaternion const a, Quaternion const b, Scalar const time)
//			{
//				//				return	CONV4(glm::slerp<Scalar>(CONV4(a).GLMQ, CONV4(b).GLMQ, time)).EEQ;
//				glm::squad(<#const detail::tquat<T> &q1#>, <#const detail::tquat<T> &q2#>, <#const detail::tquat<T> &s1#>, <#const detail::tquat<T> &s2#>, <#const T &h#>)
//			}
Quaternion const
Quaternion::Utility::quaternionBySamplingUsingSphericalQuadraticInterpolation(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Quaternion a, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Quaternion b, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Quaternion c, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Quaternion d, const Scalar t)
{
	return	CONV4(glm::squad(CONV4(a).GLMQ, CONV4(b).GLMQ, CONV4(c).GLMQ, CONV4(d).GLMQ, t)).EEQ;
}





















































#pragma mark	-	GLKit Version




//			
//			namespace
//			{
//				union
//				CONV4
//				{
//					Scalar			V[4];
//					GLKQuaternion	GLKQ;
//					Quaternion		EEQ;
//					
//					GLKVector4		GLKV;
//					Vector4			EEV;
//					
//					AxisAngle		EEAA;
//					
//					CONV4(GLKVector4 const v) : GLKV(v) {}
//					CONV4(GLKQuaternion const v) : GLKQ(v) {}
//					CONV4(Vector4 const v) : EEV(v) {}
//					CONV4(Quaternion const v) : EEQ(v) {}
//					CONV4(AxisAngle const v) : EEAA(v) {}
//				}
//				__attribute__((aligned(16)));
//				
//				static_assert(sizeof(Scalar) == 4, "");
//				static_assert(sizeof(CONV4) == sizeof(Scalar) * 4, "");
//				
//				////
//				
//				Quaternion const
//				EE(GLKQuaternion const glk)
//				{
//					return	CONV4(glk).EEQ;
//				}
//				
//				GLKQuaternion const
//				GLK(Quaternion const ee)
//				{
//					return	CONV4(ee).GLKQ;
//				}
//				
//				
//				//				static_assert(CONV4(Quaternion(1,2,3,4)).EEV == CONV4(GLKQuaternionMake(1,2,3,4)).EEV ,"Two quaternion type component layout should match.");
//			}
//
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			Quaternion::Quaternion(Scalar const x, Scalar const y, Scalar const z, Scalar const w) : x(x), y(y), z(z), w(w)
//			{
//			}
//			
//			bool const
//			Quaternion::operator==(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Quaternion &other) const
//			{
//				return	GLKVector4AllEqualToVector4(CONV4(*this).GLKV, CONV4(other).GLKV);
//			}
//			Quaternion const
//			Quaternion::operator+(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Quaternion &other) const
//			{
//				return	EE(GLKQuaternionAdd(GLK(*this), GLK(other)));
//			}
//			Quaternion const
//			Quaternion::operator-(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Quaternion &other) const
//			{
//				return	EE(GLKQuaternionSubtract(GLK(*this), GLK(other)));
//			}
//			Quaternion const
//			Quaternion::operator*(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Quaternion &other) const
//			{
//				return	EE(GLKQuaternionMultiply(GLK(*this), GLK(other)));
//			}
//			
//			Quaternion const
//			Quaternion::conjugation() const
//			{
//				return	EE(GLKQuaternionConjugate(GLK(*this)));
//			}
//			Quaternion const
//			Quaternion::inversion() const
//			{
//				return	EE(GLKQuaternionInvert(GLK(*this)));
//			}
//			Quaternion const
//			Quaternion::norm() const
//			{
//				return	EE(GLKQuaternionNormalize(GLK(*this)));
//			}
//			
//			AxisAngle const
//			Quaternion::asAxisAngle() const
//			{
//				GLKQuaternion	q		=	GLK(*this);
//				GLKVector3		axis	=	GLKQuaternionAxis(q);
//				float			angle	=	GLKQuaternionAngle(q);
//				
//				return	AxisAngle(Vector3(axis.v[0], axis.v[1], axis.v[2]), angle);
//			}
//			Vector4 const
//			Quaternion::asVector4() const
//			{
//				return	CONV4(*this).EEV;
//			}
//			
//			
//			
//			////
//			
//			Quaternion const
//			Quaternion::Utility::identity()
//			{
//				return	EE(GLKQuaternionIdentity);
//			}
//			Quaternion const
//			Quaternion::Utility::quaternionWithAxisAngle(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::AxisAngle aa)
//			{
//				return	EE(GLKQuaternionMakeWithAngleAndAxis(aa.angle, aa.axis.x, aa.axis.y, aa.axis.z));
//			}





EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END




