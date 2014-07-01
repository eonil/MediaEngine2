//
//  Matrix.cpp
//  Mathematics
//
//  Created by Hoon Hwangbo on 6/11/13.
//
//

#include "Matrix.h"
#include "InternalRawAlgorithmStuffs/D2014R2/GLM.h"
#include "InternalRawAlgorithmStuffs/D2014R2/Conversion.h"
#include "InternalRawAlgorithmStuffs/D2014R2/ConversionUnions.h"
#include "InternalRawAlgorithmStuffs/D2014R2/ApplePlatformExtras.h"

extern "C"
{
//	/*!
//	 GLM matrix parameter-less constructor makes identity matrix implicitly.
//	 Defined here to eliminate needs of linking to GLKit library.
//	 */
//	static GLKMatrix4 const			GLKMatrix4Identity	=	GLKMatrix4Make(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN

namespace
{
	using namespace	InternalRawAlgorithmStuffs::D2014R2::Conversion;
		
	static inline auto
	refAsMatrix4(SimpleMatrixAbstraction<4, Matrix4> const& o) -> Matrix4 const&
	{
		return	reinterpret_cast<Matrix4 const&>(o);
	}
	static inline auto
	toGLMFromBase(SimpleMatrixAbstraction<4, Matrix4> const& o) -> glm::mat4
	{
		return	toGLM(refAsMatrix4(o));
	}
	static inline auto
	toGLKFromBase(SimpleMatrixAbstraction<4, Matrix4> const& o) -> GLKMatrix4
	{
		return	toGLK(refAsMatrix4(o));
	}
}















#pragma mark	-	Methods

//			template<size_t C, typename M> auto
//			SimpleMatrixAbstraction<C, M>::operator==(const M &other) const -> bool const
//			{
//			}
//			template<size_t C, typename M> auto
//			SimpleMatrixAbstraction<C, M>::operator!=(const M &other) const -> bool const
//			{
//			}

template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::operator+(const M &other) const -> M const
{
	return	fromGLK(GLKMatrix4Add(toGLKFromBase(*this), toGLKFromBase(other)));
}
template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::operator-(const M &other) const -> M const
{
	return	fromGLK(GLKMatrix4Subtract(toGLKFromBase(*this), toGLKFromBase(other)));
}
template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::operator*(const M &other) const -> M const
{
	return	fromGLK(GLKMatrix4Multiply(toGLKFromBase(*this), toGLKFromBase(other)));
}

template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::operator*(const S& s) const -> M const
{
	return	fromGLM(toGLMFromBase(*this) * s);
}

//			template<size_t C, typename M> auto
//			SimpleMatrixAbstraction<C, M>::inversion(bool* isInvertible) const -> M const
//			{
//				return	EE(GLKMatrix4Invert(GLK(*this), isInvertible));
//			}
template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::inversion() const -> M const
{
	return	fromGLM(glm::inverse(toGLMFromBase(*this)));
}
template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::transposition() const -> M const
{
	return	fromGLK(GLKMatrix4Transpose(toGLKFromBase(*this)));
}
		
template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::hasNaN() const -> bool const
{
	MatrixState<C> const&	ms1	=	reinterpret_cast<MatrixState<C> const&>(*this);
	for (Size i=0; i<C*C; i++)
	{
		if (std::isnan(ms1.components[i]))
		{
			return	true;
		}
	}
	return	false;
}




#pragma mark	-	Utilities

template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::Utility::zero() -> M const
{
	return	fromGLK(GLKMatrix4Make(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
}
template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::Utility::identity() -> M const
{
	return	fromGLK(GLKMatrix4Identity);
}

template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::Utility::signalingNaN() -> M const
{
	Scalar	nan	=	std::numeric_limits<Scalar>::signaling_NaN();
	return	fromGLK(GLKMatrix4Make(nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan));
}
template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::Utility::scaleWithUniformScalar(const Scalar factor) -> M const
{
	return	fromGLK(GLKMatrix4MakeScale(factor, factor, factor));
}
template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::Utility::scaleWithScalar(const Scalar x, const Scalar y, const Scalar z) -> M const
{
	return	fromGLK(GLKMatrix4MakeScale(x,y, z));
}
template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::Utility::scaleWithVector(const Vector3 factor) -> M const
{
	return	fromGLK(GLKMatrix4MakeScale(factor.x, factor.y, factor.z));
}
template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::Utility::rotationWithAxisAngle(const AxisAngle factor) -> M const
{
	return	fromGLK(GLKMatrix4MakeRotation(factor.angle, factor.axis.x, factor.axis.y, factor.axis.z));
}
template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::Utility::rotationWithQuaternion(const Quaternion factor) -> M const
{
	return	fromGLM(glm::toMat4(toGLM(factor)));
}
template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::Utility::translationWithScalars(const Scalar x, const Scalar y, const Scalar z) -> M const
{
	return	fromGLK(GLKMatrix4MakeTranslation(x, y, z));
}
template<size_t C, typename M> auto
SimpleMatrixAbstraction<C, M>::Utility::translationWithVector(const Vector3 factor) -> M const
{
	return	fromGLK(GLKMatrix4MakeTranslation(factor.x, factor.y, factor.z));
}





//			Vector3 const
//			Matrix4::scaleComponent() const
//			{
//				//!	@todo	Implement this.
//			}
//			
//			Quaternion const
//			Matrix4::rotationComponent() const
//			{
//				return	CONV4(glm::toQuat(CONV16(*this).GLM)).EEQ;
//			}
//			Vector3 const
//			Matrix4::translationComponent() const
//			{
//				//!	@todo	Implement this.
//			}



auto
Matrix4::transform(const Vector3 point) const -> Vector3
{
	return	reinterpretAsVector3(transform(Vector4(point,1.0f)));
}
auto
Matrix4::transform(const Vector4 point) const -> Vector4
{
//	return	CONV4(GLKMatrix4MultiplyVector4(CONV16(*this).GLK, CONV4(point).GLKV)).EEV;
	return	fromGLK(GLKMatrix4MultiplyVector4(toGLK(*this), toGLK(point)));
}
auto
Matrix4::transform(const Vector2 point) const -> Vector2
{
	Vector4	v1(point.x, point.y, 0, 1);
	Vector4	v2	=	transform(v1);
	Vector2	v3(v2.x, v2.y);
	return	v3;
}

Matrix4 const
Matrix4::Utility::orthograph(const Scalar left, const Scalar right, const Scalar bottom, const Scalar top, const Scalar near, const Scalar far)
{
	return	fromGLK(GLKMatrix4MakeOrtho(left, right, bottom, top, near, far));
}
Matrix4 const
Matrix4::Utility::perspective(const Scalar left, const Scalar right, const Scalar bottom, const Scalar top, const Scalar near, const Scalar far)
{
	return	fromGLK(GLKMatrix4MakeFrustum(left, right, bottom, top, near, far));
}
//			template<size_t C, typename M> auto
//			SimpleMatrixAbstraction<C, M>::Utility::perspectiveWithFieldOfView(const Scalar fieldOfViewInY, const Scalar aspectRatio, const Scalar nearZ, const Scalar farZ) -> M const
//			{
//				return	EE(GLKMatrix4MakePerspective(fieldOfViewInY, aspectRatio, nearZ, farZ));
//			}













template class	SimpleMatrixAbstraction<4, Matrix4>;

EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END
