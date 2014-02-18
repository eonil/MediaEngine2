//
//  Vector.cpp
//  Mathematics
//
//  Created by Hoon Hwangbo on 6/10/13.
//
//

#include "Vector.h"
#include "Matrix.h"

/*
 Do not include whole GLKit which needs Objective-C context.
 */
//#include <GLKit/GLKit.h>
#include <GLKit/GLKitBase.h>
#include <GLKit/GLKMath.h>

#include "../ImplementationOnlyCommon.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Mathematics {

	namespace
	Value
	{
		/*
		 Consider using of OpenCL vector types which will be fully supported and
		 automatically vectorized by Clang 3.4 compiler.
		 */
		
		
		
		namespace
		{
			template<Size C> class GLKTypeResolver {};
			template<> struct GLKTypeResolver<2> { using TYPE = GLKVector2; };
			template<> struct GLKTypeResolver<3> { using TYPE = GLKVector3; };
			template<> struct GLKTypeResolver<4> { using TYPE = GLKVector4; };
			
			template<Size C> class GLMTypeResolver {};
			template<> struct GLMTypeResolver<2> { using TYPE = glm::vec2; };
			template<> struct GLMTypeResolver<3> { using TYPE = glm::vec3; };
			template<> struct GLMTypeResolver<4> { using TYPE = glm::vec4; };
			
			template<Size C> class EETypeResolver {};
			template<> struct EETypeResolver<2> { using TYPE = Vector2; };
			template<> struct EETypeResolver<3> { using TYPE = Vector3; };
			template<> struct EETypeResolver<4> { using TYPE = Vector4; };
			
			template<Size C> using GLKTypeFor = typename GLKTypeResolver<C>::TYPE;
			template<Size C> using GLMTypeFor = typename GLMTypeResolver<C>::TYPE;
			template<Size C> using EETypeFor = typename EETypeResolver<C>::TYPE;
			
			////

			template<Size C>
			union
			CONV
			{
				GLKTypeFor<C>	GLK;
				GLMTypeFor<C>	GLM;
				VectorState<C>	STATE;
				EETypeFor<C>	EE;
				
				CONV(GLKTypeFor<C> const glk) : GLK(glk) {}
				CONV(GLMTypeFor<C> const glm) : GLM(glm) {}
				CONV(VectorState<C> const state) : STATE(state) {}
				CONV(EETypeFor<C> const ee) : EE(ee) {}
			};
			
			Scalar const		GLK(Scalar const state) { return state; }
			GLKTypeFor<2> const	GLK(VectorState<2> const state) { return CONV<2>(state).GLK; }
			GLKTypeFor<3> const	GLK(VectorState<3> const state) { return CONV<3>(state).GLK; }
			GLKTypeFor<4> const	GLK(VectorState<4> const state) { return CONV<4>(state).GLK; }
			
			Scalar const		GLM(Scalar const state) { return state; }
			GLMTypeFor<2> const	GLM(VectorState<2> const state) { return CONV<2>(state).GLM; }
			GLMTypeFor<3> const	GLM(VectorState<3> const state) { return CONV<3>(state).GLM; }
			GLMTypeFor<4> const	GLM(VectorState<4> const state) { return CONV<4>(state).GLM; }
			
			bool const			EE(bool const glk) { return glk; }
			Scalar const		EE(Scalar const glk) { return glk; }
			EETypeFor<2> const	EE(GLKTypeFor<2> const glk) { return CONV<2>(glk).EE; }
			EETypeFor<3> const	EE(GLKTypeFor<3> const glk) { return CONV<3>(glk).EE; }
			EETypeFor<4> const	EE(GLKTypeFor<4> const glk) { return CONV<4>(glk).EE; }
			EETypeFor<2> const	EE(GLMTypeFor<2> const glm) { return CONV<2>(glm).EE; }
			EETypeFor<3> const	EE(GLMTypeFor<3> const glm) { return CONV<3>(glm).EE; }
			EETypeFor<4> const	EE(GLMTypeFor<4> const glm) { return CONV<4>(glm).EE; }
			
			////
							
			template<Size C>
			struct Ops
			{
			};
			
			template<>
			struct Ops<2>
			{
				inline static bool const		equals(GLKVector2 const a, GLKVector2 const b) { return GLKVector2AllEqualToVector2(a, b); }
				inline static GLKVector2 const 	negate(GLKVector2 const v) { return GLKVector2Negate(v); }
				inline static GLKVector2 const 	normalize(GLKVector2 const v) { return GLKVector2Normalize(v); }
				inline static Scalar const 		length(GLKVector2 const v) { return GLKVector2Length(v); }
				inline static Scalar const 		distance(GLKVector2 const a, GLKVector2 const b) { return GLKVector2Distance(a, b); }
				inline static Scalar const	 	dotProduct(GLKVector2 const a, GLKVector2 const b) { return GLKVector2DotProduct(a, b); }
//					inline static GLKVector2 const 	crossProduct(GLKVector2 const a, GLKVector2 const b) { return GLKVector2CrossProduct(a, b); }
				inline static GLKVector2 const 	project(GLKVector2 const a, GLKVector2 const b) { return GLKVector2Project(a, b); }
				inline static GLKVector2 const 	lerp(GLKVector2 const a, GLKVector2 const b, Scalar const t) { return GLKVector2Lerp(a, b, t); }
				
				inline static GLKVector2 const	minimum(GLKVector2 const a, GLKVector2 const b) { return GLKVector2Minimum(a, b); }
				inline static GLKVector2 const	maximum(GLKVector2 const a, GLKVector2 const b) { return GLKVector2Maximum(a, b); }
				inline static GLKVector2 const	add(GLKVector2 const a, GLKVector2 const b) { return GLKVector2Add(a, b); }
				inline static GLKVector2 const	subtract(GLKVector2 const a, GLKVector2 const b) { return GLKVector2Subtract(a, b); }
				inline static GLKVector2 const	multiply(GLKVector2 const a, GLKVector2 const b) { return GLKVector2Multiply(a, b); }
				inline static GLKVector2 const	divide(GLKVector2 const a, GLKVector2 const b) { return GLKVector2Divide(a, b); }
				
				inline static GLKVector2 const	addScalar(GLKVector2 const a, Scalar const b) { return GLKVector2AddScalar(a, b); }
				inline static GLKVector2 const	subtractScalar(GLKVector2 const a, Scalar const b) { return GLKVector2SubtractScalar(a, b); }
				inline static GLKVector2 const	multiplyScalar(GLKVector2 const a, Scalar const b) { return GLKVector2MultiplyScalar(a, b); }
				inline static GLKVector2 const	divideScalar(GLKVector2 const a, Scalar const b) { return GLKVector2DivideScalar(a, b); }
			};
			template<>
			struct Ops<3>
			{
				inline static bool const		equals(GLKVector3 const a, GLKVector3 const b) { return GLKVector3AllEqualToVector3(a, b); }
				inline static GLKVector3 const 	negate(GLKVector3 const v) { return GLKVector3Negate(v); }
				inline static GLKVector3 const 	normalize(GLKVector3 const v) { return GLKVector3Normalize(v); }
				inline static Scalar const 		length(GLKVector3 const v) { return GLKVector3Length(v); }
				inline static Scalar const 		distance(GLKVector3 const a, GLKVector3 const b) { return GLKVector3Distance(a, b); }
				inline static Scalar const	 	dotProduct(GLKVector3 const a, GLKVector3 const b) { return GLKVector3DotProduct(a, b); }
				inline static GLKVector3 const 	crossProduct(GLKVector3 const a, GLKVector3 const b) { return GLKVector3CrossProduct(a, b); }
				inline static GLKVector3 const 	project(GLKVector3 const a, GLKVector3 const b) { return GLKVector3Project(a, b); }
				inline static GLKVector3 const 	lerp(GLKVector3 const a, GLKVector3 const b, Scalar const t) { return GLKVector3Lerp(a, b, t); }
				
				inline static GLKVector3 const	minimum(GLKVector3 const a, GLKVector3 const b) { return GLKVector3Minimum(a, b); }
				inline static GLKVector3 const	maximum(GLKVector3 const a, GLKVector3 const b) { return GLKVector3Maximum(a, b); }
				inline static GLKVector3 const	add(GLKVector3 const a, GLKVector3 const b) { return GLKVector3Add(a, b); }
				inline static GLKVector3 const	subtract(GLKVector3 const a, GLKVector3 const b) { return GLKVector3Subtract(a, b); }
				inline static GLKVector3 const	multiply(GLKVector3 const a, GLKVector3 const b) { return GLKVector3Multiply(a, b); }
				inline static GLKVector3 const	divide(GLKVector3 const a, GLKVector3 const b) { return GLKVector3Divide(a, b); }
				
				inline static GLKVector3 const	addScalar(GLKVector3 const a, Scalar const b) { return GLKVector3AddScalar(a, b); }
				inline static GLKVector3 const	subtractScalar(GLKVector3 const a, Scalar const b) { return GLKVector3SubtractScalar(a, b); }
				inline static GLKVector3 const	multiplyScalar(GLKVector3 const a, Scalar const b) { return GLKVector3MultiplyScalar(a, b); }
				inline static GLKVector3 const	divideScalar(GLKVector3 const a, Scalar const b) { return GLKVector3DivideScalar(a, b); }
			};
			template<>
			struct Ops<4>
			{
				inline static bool const		equals(GLKVector4 const a, GLKVector4 const b) { return GLKVector4AllEqualToVector4(a, b); }
				inline static GLKVector4 const 	negate(GLKVector4 const v) { return GLKVector4Negate(v); }
				inline static GLKVector4 const 	normalize(GLKVector4 const v) { return GLKVector4Normalize(v); }
				inline static Scalar const 		length(GLKVector4 const v) { return GLKVector4Length(v); }
				inline static Scalar const 		distance(GLKVector4 const a, GLKVector4 const b) { return GLKVector4Distance(a, b); }
				inline static Scalar const	 	dotProduct(GLKVector4 const a, GLKVector4 const b) { return GLKVector4DotProduct(a, b); }
//					inline static GLKVector4 const 	crossProduct(GLKVector4 const a, GLKVector4 const b) { return GLKVector4CrossProduct(a, b); }		//	Just redirection of 3D vector. Not actually defined.
				inline static GLKVector4 const 	project(GLKVector4 const a, GLKVector4 const b) { return GLKVector4Project(a, b); }
				inline static GLKVector4 const 	lerp(GLKVector4 const a, GLKVector4 const b, Scalar const t) { return GLKVector4Lerp(a, b, t); }
				
				inline static GLKVector4 const	minimum(GLKVector4 const a, GLKVector4 const b) { return GLKVector4Minimum(a, b); }
				inline static GLKVector4 const	maximum(GLKVector4 const a, GLKVector4 const b) { return GLKVector4Maximum(a, b); }
				inline static GLKVector4 const	add(GLKVector4 const a, GLKVector4 const b) { return GLKVector4Add(a, b); }
				inline static GLKVector4 const	subtract(GLKVector4 const a, GLKVector4 const b) { return GLKVector4Subtract(a, b); }
				inline static GLKVector4 const	multiply(GLKVector4 const a, GLKVector4 const b) { return GLKVector4Multiply(a, b); }
				inline static GLKVector4 const	divide(GLKVector4 const a, GLKVector4 const b) { return GLKVector4Divide(a, b); }
				
				inline static GLKVector4 const	addScalar(GLKVector4 const a, Scalar const b) { return GLKVector4AddScalar(a, b); }
				inline static GLKVector4 const	subtractScalar(GLKVector4 const a, Scalar const b) { return GLKVector4SubtractScalar(a, b); }
				inline static GLKVector4 const	multiplyScalar(GLKVector4 const a, Scalar const b) { return GLKVector4MultiplyScalar(a, b); }
				inline static GLKVector4 const	divideScalar(GLKVector4 const a, Scalar const b) { return GLKVector4DivideScalar(a, b); }
			};
			
			
		}
		
		
		
		
		
		
		
		
		
		
		
#pragma mark	-	Method Implementations
		
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::Utility::signalingNaN() -> V const
		{
			V	v;
			for (Size i=0; i<C; i++)
			{
				v.components[i]	=	std::numeric_limits<Scalar>::signaling_NaN();
			}
			return	v;
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::Utility::infinity() -> V const
		{
			V	v;
			for (Size i=0; i<C; i++)
			{
				v.components[i]	=	std::numeric_limits<Scalar>::infinity();
			}
			return	v;
		}
		
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::Utility::distanceBetweenVectors(const V left, const V right) -> S const
		{
			return	EE(Ops<C>::distance(GLK(left), GLK(right)));
		}
		
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::Utility::minimumOfVectors(const V left, const V right) -> V const
		{
			return	EE(Ops<C>::minimum(GLK(left), GLK(right)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::Utility::maximumOfVectors(const V left, const V right) -> V const
		{
			return	EE(Ops<C>::maximum(GLK(left), GLK(right)));
		}
		
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::Utility::dotProductionOfVectors(const V left, const V right) -> S const
		{
			return	EE(Ops<C>::dotProduct(GLK(left), GLK(right)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::Utility::vectorUsingLinearInterpolationBetweenVectors(const V begin, const V end, const Scalar time) -> V const
		{
			return	EE(Ops<C>::lerp(GLK(begin), GLK(end), GLK(time)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::Utility::vectorUsingCatmullRomSplineBetweenVectors(const V prebegin, const V begin, const V end, const V postend, const Scalar time) -> V const
		{
			return	EE(glm::catmullRom(GLM(prebegin), GLM(begin), GLM(end), GLM(postend), time));
		}
		
		
		
		
		
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::operator==(V const& other) const -> bool const
		{
			return	EE(Ops<C>::equals(GLK(*this), GLK(other)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::operator!=(V const& other) const -> bool const
		{
			return	not EE(Ops<C>::equals(GLK(*this), GLK(other)));
		}
		
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::operator-() const -> V const
		{
			return	EE(Ops<C>::negate(GLK(*this)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::operator+(V const& other) const -> V const
		{
			return	EE(Ops<C>::add(GLK(*this), GLK(other)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::operator-(V const& other) const -> V const
		{
			return	EE(Ops<C>::subtract(GLK(*this), GLK(other)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::operator*(V const& other) const -> V const
		{
			return	EE(Ops<C>::multiply(GLK(*this), GLK(other)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::operator/(V const& other) const -> V const
		{
			return	EE(Ops<C>::divide(GLK(*this), GLK(other)));
		}
		
		
		
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::operator+(Scalar const& other) const -> V const
		{
			return	EE(Ops<C>::addScalar(GLK(*this), GLK(other)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::operator-(Scalar const& other) const -> V const
		{
			return	EE(Ops<C>::subtractScalar(GLK(*this), GLK(other)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::operator*(Scalar const& other) const -> V const
		{
			return	EE(Ops<C>::multiplyScalar(GLK(*this), GLK(other)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::operator/(Scalar const& other) const -> V const
		{
			return	EE(Ops<C>::divideScalar(GLK(*this), GLK(other)));
		}
		
		
		
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::length() const -> S const
		{
			return	EE(Ops<C>::length(GLK(*this)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::lengthSquare() const -> S const
		{
			return	length() * length();		//	TODO: optimize.
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::norm() const -> V const
		{
			return	EE(Ops<C>::normalize(GLK(*this)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::distanceToVector(V const target) const -> S const
		{
			return	EE(Ops<C>::distance(GLK(*this), GLK(target)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::dotProductionWithVector(V const target) const -> S const
		{
			return	EE(Ops<C>::dotProduct(GLK(*this), GLK(target)));
		}
		template<Size C, typename V> auto
		SimpleVectorAbstraction<C, V>::projectionOntoVector(V const target) const -> V const
		{
			return	EE(Ops<C>::project(GLK(*this), GLK(target)));
		}
		
		
					
		
		
		
		template class SimpleVectorAbstraction<2, Vector2>;
		template class SimpleVectorAbstraction<3, Vector3>;
		template class SimpleVectorAbstraction<4, Vector4>;
		
		
		
		
		
		
		
		
#pragma mark	-	Concrete Class Constructors
		
		Vector2::Vector2(Scalar const x, Scalar const y)
		{
			this->x	=	x;
			this->y	=	y;
		}
		
		Vector3::Vector3(Vector2 const v, Scalar const z)
		{
			this->x	=	v.x;
			this->y	=	v.y;
			this->z	=	z;
		}
		Vector3::Vector3(Scalar const x, Scalar const y, Scalar const z)
		{
			this->x	=	x;
			this->y	=	y;
			this->z	=	z;
		}
		
		Scalar const
		Vector3::Utility::angleBetweenVectorsOnPlane(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector3 a, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector3 b, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector3 planeAxis)
		{
			/*
			 The GLM method always return degrees.
			 Convert manually until it handles radians correctly.
			 */
			return	glm::radians(EE(glm::orientedAngle(GLM(a), GLM(b), GLM(planeAxis))));
		}
		Vector3 const
		Vector3::Utility::crossProductionOfVectors(const Vector3 left, const Vector3 right)
		{
			return	EE(Ops<3>::crossProduct(GLK(left), GLK(right)));
		}
		Vector3 const
		Vector3::crossProductionWithVector(Vector3 const target) const
		{
			return	EE(Ops<3>::crossProduct(GLK(*this), GLK(target)));
		}
		

		
		Vector4::Vector4(Vector3 const v, Scalar const w)
		{
			this->x	=	v.x;
			this->y	=	v.y;
			this->z	=	v.z;
			this->w	=	w;
		}
		Vector4::Vector4(Vector2 const v, Scalar const z, Scalar const w)
		{
			this->x	=	v.x;
			this->y	=	v.y;
			this->z	=	z;
			this->w	=	w;
		}
		Vector4::Vector4(Scalar const x, Scalar const y, Scalar const z, Scalar const w)
		{
			this->x	=	x;
			this->y	=	y;
			this->z	=	z;
			this->w	=	w;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
#pragma mark	-	Compile time tests.
		
		static_assert(std::is_pod<VectorState<2>>::value, "");
		static_assert(std::is_pod<VectorState<3>>::value, "");
		static_assert(std::is_pod<VectorState<4>>::value, "");
		
		static_assert(std::is_pod<SimpleVectorAbstraction<2, Vector2>>::value, "");
		static_assert(std::is_pod<SimpleVectorAbstraction<3, Vector3>>::value, "");
		static_assert(std::is_pod<SimpleVectorAbstraction<4, Vector4>>::value, "");
		
		static_assert(std::is_standard_layout<Vector2>::value, "");
		static_assert(std::is_standard_layout<Vector3>::value, "");
		static_assert(std::is_standard_layout<Vector4>::value, "");
		
		static_assert(sizeof(VectorState<2>) == sizeof(Scalar)*2, "`sizeof(VectorState<2>)` must be `sizeof(Scalar) * 2`.");
		static_assert(sizeof(VectorState<3>) == sizeof(Scalar)*3, "`sizeof(VectorState<3>)` must be `sizeof(Scalar) * 3`.");
		static_assert(sizeof(VectorState<4>) == sizeof(Scalar)*4, "`sizeof(VectorState<4>)` must be `sizeof(Scalar) * 4`.");
		
		static_assert(sizeof(Vector2) == sizeof(Scalar)*2, "`sizeof(Vector2)` must be 8.");
		static_assert(sizeof(Vector3) == sizeof(Scalar)*3, "`sizeof(Vector3)` must be 12.");
		static_assert(sizeof(Vector4) == sizeof(Scalar)*4, "`sizeof(Vector4)` must be 16.");
		
		static_assert(std::is_same<decltype(Vector2::x), Scalar>::value, "Vector2::x must be a Scalar.");
		static_assert(std::is_same<decltype(Vector2::y), Scalar>::value, "Vector2::y must be a Scalar.");
		static_assert(std::is_same<decltype(Vector3::x), Scalar>::value, "Vector3::x must be a Scalar.");
		static_assert(std::is_same<decltype(Vector3::y), Scalar>::value, "Vector3::y must be a Scalar.");
		static_assert(std::is_same<decltype(Vector3::z), Scalar>::value, "Vector3::z must be a Scalar.");
		static_assert(std::is_same<decltype(Vector4::x), Scalar>::value, "Vector4::x must be a Scalar.");
		static_assert(std::is_same<decltype(Vector4::y), Scalar>::value, "Vector4::y must be a Scalar.");
		static_assert(std::is_same<decltype(Vector4::z), Scalar>::value, "Vector4::z must be a Scalar.");
		static_assert(std::is_same<decltype(Vector4::w), Scalar>::value, "Vector4::w must be a Scalar.");
		
		
	}
	
	

	
	
}}}}
