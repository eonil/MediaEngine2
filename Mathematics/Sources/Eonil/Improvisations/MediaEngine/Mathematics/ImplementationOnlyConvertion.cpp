//
//  ImplementationOnlyConvertion.cpp
//  Mathematics
//
//  Created by Hoon H. on 3/4/14.
//
//

#include "ImplementationOnlyConvertion.h"
#include "Geometry/Vector.h"
#include "Geometry/Matrix.h"
#include "Geometry/Conversion/Unions.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN

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
toGLM(Matrix4 const& v) -> glm::mat4
{
	return	Conversion::FLOAT32x16{v}.GLM;
}








EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END
