//
//  Matrix.cpp
//  Mathematics
//
//  Created by Hoon Hwangbo on 6/11/13.
//
//

#include "Matrix.h"

#include "Conversion/Unions.h"


/*
 Do not include whole GLKit which needs Objective-C context.
 */
//#include <GLKit/GLKit.h>
#include <GLKit/GLKitBase.h>
#include <GLKit/GLKMath.h>



extern "C"
{
//	/*!
//	 GLM matrix parameter-less constructor makes identity matrix implicitly.
//	 Defined here to eliminate needs of linking to GLKit library.
//	 */
//	static GLKMatrix4 const			GLKMatrix4Identity	=	GLKMatrix4Make(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}




namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Mathematics {

	namespace
	Value
	{
		namespace
		{
			union
			CONV16
			{
				GLKMatrix4							GLK;
				glm::mat4							GLM;
				SimpleMatrixAbstraction<4, Matrix4>	SMA4;
				Matrix4								EE;
				Scalar								components[16];
				
				CONV16(GLKMatrix4 const glk) : GLK(glk) {}
				CONV16(glm::mat4 const glm) : GLM(glm) {}
				CONV16(SimpleMatrixAbstraction<4, Matrix4> const sma4) : SMA4(sma4) {}
				CONV16(Matrix4 const ee) : EE(ee) {}
			}
			__attribute__((aligned(16)));
			
			union
			CONV4
			{
				Scalar			V[4];
				glm::quat		GLMQ;
				Quaternion		EEQ;
				
				GLKVector4		GLKV;
				Vector4			EEV;
				Vector3			EEVxyz;
				Vector2			EEVxy;
				
				AxisAngle		EEAA;
				
				CONV4(GLKVector4 const v) : GLKV(v) {}
				CONV4(glm::quat const v) : GLMQ(v) {}
				CONV4(Vector4 const v) : EEV(v) {}
				CONV4(Quaternion const v) : EEQ(v) {}
				CONV4(AxisAngle const v) : EEAA(v) {}
			}
			__attribute__((aligned(16)));
			
			static_assert(sizeof(Scalar) == 4, "");
			static_assert(sizeof(CONV4) == sizeof(Scalar) * 4, "");
			
			////
			
			GLKMatrix4 const
			GLK(SimpleMatrixAbstraction<4, Matrix4> const ee)
			{
				return	CONV16(ee).GLK;
			}
			
			glm::mat4 const
			GLM(SimpleMatrixAbstraction<4, Matrix4> const ee)
			{
				return	CONV16(ee).GLM;
			}
			
			Matrix4 const
			EE(GLKMatrix4 const glk)
			{
				return	CONV16(glk).EE;
			}
			Matrix4 const
			EE(glm::mat4 const glm)
			{
				return	CONV16(glm).EE;
			}
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
#pragma mark	-	Methods
		
//			template<Size C, typename M> auto
//			SimpleMatrixAbstraction<C, M>::operator==(const M &other) const -> bool const
//			{
//			}
//			template<Size C, typename M> auto
//			SimpleMatrixAbstraction<C, M>::operator!=(const M &other) const -> bool const
//			{
//			}
		
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::operator+(const M &other) const -> M const
		{
			return	EE(GLKMatrix4Add(GLK(*this), GLK(other)));
		}
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::operator-(const M &other) const -> M const
		{
			return	EE(GLKMatrix4Subtract(GLK(*this), GLK(other)));
		}
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::operator*(const M &other) const -> M const
		{
			return	EE(GLKMatrix4Multiply(GLK(*this), GLK(other)));
		}
		
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::operator*(const S& s) const -> M const
		{
			return	EE(CONV16(*this).GLM * s);
		}
		
//			template<Size C, typename M> auto
//			SimpleMatrixAbstraction<C, M>::inversion(bool* isInvertible) const -> M const
//			{
//				return	EE(GLKMatrix4Invert(GLK(*this), isInvertible));
//			}
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::inversion() const -> M const
		{
			return	EE(glm::inverse(GLM(*this)));
		}
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::transposition() const -> M const
		{
			return	EE(GLKMatrix4Transpose(GLK(*this)));
		}
				
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::hasNaN() const -> bool const
		{
			CONV16	conv(*this);
			for (Size i=0; i<C*C; i++)
			{
				if (std::isnan(conv.components[i]))
				{
					return	true;
				}
			}
			return	false;
		}
		
		
		
		
#pragma mark	-	Utilities
		
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::Utility::zero() -> M const
		{
			return	EE(GLKMatrix4Make(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
		}
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::Utility::identity() -> M const
		{
			return	EE(GLKMatrix4Identity);
		}
		
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::Utility::signalingNaN() -> M const
		{
			Scalar	nan	=	std::numeric_limits<Scalar>::signaling_NaN();
			return	EE(GLKMatrix4Make(nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan, nan));
		}
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::Utility::scaleWithUniformScalar(const Scalar factor) -> M const
		{
			return	EE(GLKMatrix4MakeScale(factor, factor, factor));
		}
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::Utility::scaleWithScalar(const Scalar x, const Scalar y, const Scalar z) -> M const
		{
			return	EE(GLKMatrix4MakeScale(x,y, z));
		}
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::Utility::scaleWithVector(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector3 factor) -> M const
		{
			return	EE(GLKMatrix4MakeScale(factor.x, factor.y, factor.z));
		}
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::Utility::rotationWithAxisAngle(const Eonil::Improvisations::MediaEngine::Mathematics::Value::AxisAngle factor) -> M const
		{
			return	EE(GLKMatrix4MakeRotation(factor.angle, factor.axis.x, factor.axis.y, factor.axis.z));
		}
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::Utility::rotationWithQuaternion(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Quaternion factor) -> M const
		{
			return	EE(glm::toMat4(CONV4(factor).GLMQ));
		}
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::Utility::translationWithScalars(const Scalar x, const Scalar y, const Scalar z) -> M const
		{
			return	EE(GLKMatrix4MakeTranslation(x, y, z));
		}
		template<Size C, typename M> auto
		SimpleMatrixAbstraction<C, M>::Utility::translationWithVector(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector3 factor) -> M const
		{
			return	EE(GLKMatrix4MakeTranslation(factor.x, factor.y, factor.z));
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

		
		
		Vector3 const
		Matrix4::transform(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector3 point) const
		{
			return	CONV4(transform(Vector4(point,1.0f))).EEVxyz;
		}
		Vector4 const
		Matrix4::transform(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector4 point) const
		{
			return	CONV4(GLKMatrix4MultiplyVector4(CONV16(*this).GLK, CONV4(point).GLKV)).EEV;
		}
		Vector2 const
		Matrix4::transform(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector2 point) const
		{
			Vector4	v1(point.x, point.y, 0, 1);
			Vector4	v2	=	transform(v1);
			Vector2	v3(v2.x, v2.y);
			return	v3;
		}
		
		Matrix4 const
		Matrix4::Utility::orthograph(const Scalar left, const Scalar right, const Scalar bottom, const Scalar top, const Scalar near, const Scalar far)
		{
			return	EE(GLKMatrix4MakeOrtho(left, right, bottom, top, near, far));
		}
		Matrix4 const
		Matrix4::Utility::perspective(const Scalar left, const Scalar right, const Scalar bottom, const Scalar top, const Scalar near, const Scalar far)
		{
			return	EE(GLKMatrix4MakeFrustum(left, right, bottom, top, near, far));
		}
		//			template<Size C, typename M> auto
		//			SimpleMatrixAbstraction<C, M>::Utility::perspectiveWithFieldOfView(const Scalar fieldOfViewInY, const Scalar aspectRatio, const Scalar nearZ, const Scalar farZ) -> M const
		//			{
		//				return	EE(GLKMatrix4MakePerspective(fieldOfViewInY, aspectRatio, nearZ, farZ));
		//			}

		
		
		
		
		
		
		
		
		
		
		
		
		template class	SimpleMatrixAbstraction<4, Matrix4>;
	}
	
	
	
	
	
}}}}


