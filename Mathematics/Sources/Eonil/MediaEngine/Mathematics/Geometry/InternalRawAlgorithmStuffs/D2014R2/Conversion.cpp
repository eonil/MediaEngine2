//
//  Conversion.cpp
//  Mathematics
//
//  Created by Hoon H. on 2014/05/19.
//
//

#include "Conversion.h"
#include "../../../Debugging/Exceptions.h"
#include "../../Vector.h"
#include "../../AxisAngle.h"
#include "../../Matrix.h"
#include "../../Bounds.h"
#include "ConversionUnions.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN

namespace
InternalRawAlgorithmStuffs
{
	namespace
	D2014R2
	{
		namespace
		Conversion
		{
			using namespace	Debugging;
			
			using	S2	=	Conversion::FLOAT32x2;
			using	S3	=	Conversion::FLOAT32x3;
			using	S4	=	Conversion::FLOAT32x4;
			using	S16	=	Conversion::FLOAT32x16;
			

			
			auto
			fromGLM(glm::vec1 const& v) -> Vector1
			{
				return	v.x;
			}
			auto
			fromGLM(glm::vec2 const& v) -> Vector2
			{
				return	Conversion::FLOAT32x2{v}.EE;
			}
			auto
			fromGLM(glm::vec3 const& v) -> Vector3
			{
				return	Conversion::FLOAT32x3{v}.EE;
			}
			auto
			fromGLM(glm::vec4 const& v) -> Vector4
			{
				return	Conversion::FLOAT32x4{v}.EE;
			}
			auto
			fromGLM(glm::quat const& v) -> Quaternion
			{
				/*
				 This is safe because `Quaternion` class is just a wrapper of GLM quaternion.
				 */
				return	S4(v).EEQ;
			}
			auto
			fromGLM(glm::mat4 const& v) -> Matrix4
			{
				return	Conversion::FLOAT32x16{v}.EE;
			}
			
			
			
			
			
			auto
			toGLM(Vector1 const& v) -> glm::vec1
			{
				return	v;
			}
			auto
			toGLM(Vector2 const& v) -> glm::vec2
			{
				return	Conversion::FLOAT32x2{v}.GLM;
			}
			auto
			toGLM(Vector3 const& v) -> glm::vec3
			{
				return	Conversion::FLOAT32x3{v}.GLM;
			}
			auto
			toGLM(Vector4 const& v) -> glm::vec4
			{
				return	Conversion::FLOAT32x4{v}.GLM;
			}
			auto
			toGLM(Quaternion const& v) -> glm::quat
			{
				return	S4(v).GLMQ;
			}
			auto
			toGLM(Matrix4 const& v) -> glm::mat4
			{
				return	Conversion::FLOAT32x16{v}.GLM;
			}
			
			
			
			
			
			
			
						
			
			
			
			
			
			
			
			
			auto
			refAsVector3(Vector4 const& vector) -> Vector3 const&
			{
				return	reinterpret_cast<Vector3 const&>(vector);
			}
			auto
			refAsVector2(Vector4 const& vector) -> Vector2 const&
			{
				return	reinterpret_cast<Vector2 const&>(vector);
			}
			auto
			refAsVector1(Vector4 const& vector) -> Vector1 const&
			{
				return	reinterpret_cast<Vector1 const&>(vector);
			}
			
			auto
			refAsVector2(Vector3 const& vector) -> Vector2 const&
			{
				return	reinterpret_cast<Vector2 const&>(vector);
			}
			auto
			refAsVector1(Vector3 const& vector) -> Vector1 const&
			{
				return	reinterpret_cast<Vector1 const&>(vector);
			}
			
			auto
			refAsVector1(Vector2 const& vector) -> Vector1 const&
			{
				return	reinterpret_cast<Vector1 const&>(vector);
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
#if (EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
			
			auto
			fromGLK(float const& v) -> Vector1
			{
				return	v;
			}
			auto
			fromGLK(GLKVector2 const& v) -> Vector2
			{
				return	S2{v}.EE;
			}
			auto
			fromGLK(GLKVector3 const& v) -> Vector3
			{
				return	S3{v}.EE;
			}
			auto
			fromGLK(GLKVector4 const& v) -> Vector4
			{
				return	S4{v}.EE;
			}
			auto
			fromGLK(GLKMatrix4 const& v) -> Matrix4
			{
				return	S16{v}.EE;
			}
			
			
			auto
			toGLK(Vector1 const& v) -> float
			{
				return	v;
			}
			auto
			toGLK(Vector2 const& v) -> GLKVector2
			{
				return	S2{v}.GLK;
			}
			auto
			toGLK(Vector3 const& v) -> GLKVector3
			{
				return	S3{v}.GLK;
			}
			auto
			toGLK(Vector4 const& v) -> GLKVector4
			{
				return	S4{v}.GLK;
			}
			auto
			toGLK(Matrix4 const& v) -> GLKMatrix4
			{
				return	S16{v}.GLK;
			}
			
			
			
			
//			auto
//			fromCG(CGRect const& v) -> Bounds2
//			{
//				Bounds2	r;
//				r.minX	=	v.origin.x;
//				r.minY	=	v.origin.y;
//				r.maxX	=	v.origin.x + v.size.width;
//				r.maxY	=	v.origin.y + v.size.height;
//				return	r;
//			}
			
			auto
			toCG(Bounds2 const& v) -> CGRect
			{
				Vector2	sz	=	v.size();
				return	CGRectMake(v.minimum.x, v.maximum.y, sz.x, sz.y);
			}
#endif

			
			
			
		}
	}
}

EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END