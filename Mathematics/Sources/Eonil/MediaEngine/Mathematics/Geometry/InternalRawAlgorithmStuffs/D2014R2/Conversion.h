//
//  Conversion.h
//  Mathematics
//
//  Created by Hoon H. on 2014/05/19.
//
//

#pragma once
#include "../../../Common.h"
#include "GLM.h"
#include "ApplePlatformExtras.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN

namespace
InternalRawAlgorithmStuffs
{
	namespace
	D2014R2
	{
		/*
		 Zero-cost conversions (if inlined by compiler, and very likely does).
		 */
		namespace
		Conversion
		{
			
			auto	fromGLM(glm::vec1 const& v) -> Vector1;
			auto	fromGLM(glm::vec2 const& v) -> Vector2;
			auto	fromGLM(glm::vec3 const& v) -> Vector3;
			auto	fromGLM(glm::vec4 const& v) -> Vector4;
			auto	fromGLM(glm::quat const& v) -> Quaternion;
			auto	fromGLM(glm::mat4 const& v) -> Matrix4;
			
			auto	toGLM(Vector1 const& v) -> glm::vec1;
			auto	toGLM(Vector2 const& v) -> glm::vec2;
			auto	toGLM(Vector3 const& v) -> glm::vec3;
			auto	toGLM(Vector4 const& v) -> glm::vec4;
			auto	toGLM(Quaternion const& v) -> glm::quat;
			auto	toGLM(Matrix4 const& v) -> glm::mat4;
	
			auto	reinterpretAsVector3(Vector4 const& vector) -> Vector3 const&;
			auto	reinterpretAsVector2(Vector4 const& vector) -> Vector2 const&;
			auto	reinterpretAsVector1(Vector4 const& vector) -> Vector1 const&;
			
			auto	reinterpretAsVector2(Vector3 const& vector) -> Vector2 const&;
			auto	reinterpretAsVector1(Vector3 const& vector) -> Vector1 const&;
			
			auto	reinterpretAsVector1(Vector2 const& vector) -> Vector1 const&;
			
			auto	reinterpretAsScalarArray(Vector2 const&) -> std::array<Scalar, 2> const&;
			auto	reinterpretAsScalarArray(Vector3 const&) -> std::array<Scalar, 3> const&;
			auto	reinterpretAsScalarArray(Vector4 const&) -> std::array<Scalar, 4> const&;
			auto	reinterpretAsScalarArray(Matrix4 const&) -> std::array<Scalar, 16> const&;
			
			
			
			
			
			
			
			
#if EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_APPLE_PLATFORM_EXTRAS_READY
			auto	fromGLK(float const& v) -> Vector1;
			auto	fromGLK(GLKVector2 const& v) -> Vector2;
			auto	fromGLK(GLKVector3 const& v) -> Vector3;
			auto	fromGLK(GLKVector4 const& v) -> Vector4;
//			auto	fromGLK(GLKQuaternion const& v) -> Quaternion;		//	Zero cost quaternion conversion from GLK is not supported.
			auto	fromGLK(GLKMatrix4 const& v) -> Matrix4;
			
			auto	toGLK(Vector1 const& v) -> float;
			auto	toGLK(Vector2 const& v) -> GLKVector2;
			auto	toGLK(Vector3 const& v) -> GLKVector3;
			auto	toGLK(Vector4 const& v) -> GLKVector4;
//			auto	toGLK(Quaternion const& v) -> GLKQuaternion;		//	Zero cost quaternion conversion to GLK is not supported.
			auto	toGLK(Matrix4 const& v) -> GLKMatrix4;

			
			
//			auto	fromCG(CGRect const&) -> Bounds2;
			auto	toCG(Bounds2 const&) -> CGRect;
			
#endif
			
			
			
			
			
			
		}
	}
}

EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END