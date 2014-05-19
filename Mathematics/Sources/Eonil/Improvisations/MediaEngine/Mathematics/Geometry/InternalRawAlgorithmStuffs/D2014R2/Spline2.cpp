//
//  Spline2.cpp
//  Mathematics
//
//  Created by Hoon H. on 3/4/14.
//
//

#include "Spline2.h"
#include "ImplementationOnlyGLM.h"
#include "ImplementationOnlyConvertion.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN

namespace
D2014R2
{
	namespace
	SplineV2
	{
	//			using namespace CommonUtility;


		auto
		catmullRom(Vector1 const& p0, Vector1 const& p1, Vector1 const& p2, Vector1 const& p3, Scalar const& time) -> Vector1
		{
			return	fromGLM(glm::catmullRom(toGLM(p1), toGLM(p1), toGLM(p2), toGLM(p3), time));
		}
		auto
		catmullRom(Vector2 const& p0, Vector2 const& p1, Vector2 const& p2, Vector2 const& p3, Scalar const& time) -> Vector2
		{
			return	fromGLM(glm::catmullRom(toGLM(p1), toGLM(p1), toGLM(p2), toGLM(p3), time));
		}
		auto
		catmullRom(Vector3 const& p0, Vector3 const& p1, Vector3 const& p2, Vector3 const& p3, Scalar const& time) -> Vector3
		{
			return	fromGLM(glm::catmullRom(toGLM(p1), toGLM(p1), toGLM(p2), toGLM(p3), time));
		}
		auto
		catmullRom(Vector4 const& p0, Vector4 const& p1, Vector4 const& p2, Vector4 const& p3, Scalar const& time) -> Vector4
		{
			return	fromGLM(glm::catmullRom(toGLM(p1), toGLM(p1), toGLM(p2), toGLM(p3), time));
		}
		
		auto
		cubic(Vector1 const& p0, Vector1 const& p1, Vector1 const& p2, Vector1 const& p3, Scalar const& time) -> Vector1
		{
			return	fromGLM(glm::cubic(toGLM(p1), toGLM(p1), toGLM(p2), toGLM(p3), time));
		}
		auto
		cubic(Vector2 const& p0, Vector2 const& p1, Vector2 const& p2, Vector2 const& p3, Scalar const& time) -> Vector2
		{
			return	fromGLM(glm::cubic(toGLM(p1), toGLM(p1), toGLM(p2), toGLM(p3), time));
		}
		auto
		cubic(Vector3 const& p0, Vector3 const& p1, Vector3 const& p2, Vector3 const& p3, Scalar const& time) -> Vector3
		{
			return	fromGLM(glm::cubic(toGLM(p1), toGLM(p1), toGLM(p2), toGLM(p3), time));
		}
		auto
		cubic(Vector4 const& p0, Vector4 const& p1, Vector4 const& p2, Vector4 const& p3, Scalar const& time) -> Vector4
		{
			return	fromGLM(glm::cubic(toGLM(p1), toGLM(p1), toGLM(p2), toGLM(p3), time));
		}
		
		auto
		hermite(Vector1 const& p0, Vector1 const& p1, Vector1 const& p2, Vector1 const& p3, Scalar const& time) -> Vector1
		{
			return	fromGLM(glm::cubic(toGLM(p1), toGLM(p1), toGLM(p2), toGLM(p3), time));
		}
		auto
		hermite(Vector2 const& p0, Vector2 const& p1, Vector2 const& p2, Vector2 const& p3, Scalar const& time) -> Vector2
		{
			return	fromGLM(glm::cubic(toGLM(p1), toGLM(p1), toGLM(p2), toGLM(p3), time));
		}
		auto
		hermite(Vector3 const& p0, Vector3 const& p1, Vector3 const& p2, Vector3 const& p3, Scalar const& time) -> Vector3
		{
			return	fromGLM(glm::cubic(toGLM(p1), toGLM(p1), toGLM(p2), toGLM(p3), time));
		}
		auto
		hermite(Vector4 const& p0, Vector4 const& p1, Vector4 const& p2, Vector4 const& p3, Scalar const& time) -> Vector4
		{
			return	fromGLM(glm::cubic(toGLM(p1), toGLM(p1), toGLM(p2), toGLM(p3), time));
		}
		
		
		






















	}
}

EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END