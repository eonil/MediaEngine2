//
//  ImplementationOnlyConvertion.h
//  Mathematics
//
//  Created by Hoon H. on 3/4/14.
//
//

#pragma once
#include "Common.h"
#include "ImplementationOnlyGLM.h"
#include "ImplementationOnlyCommon.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN

auto	fromGLM(glm::vec1 const& v) -> Vector1;
auto	fromGLM(glm::vec2 const& v) -> Vector2;
auto	fromGLM(glm::vec3 const& v) -> Vector3;
auto	fromGLM(glm::vec4 const& v) -> Vector4;
auto	fromGLM(glm::mat4 const& v) -> Matrix4;

auto	toGLM(Vector1 const& v) -> glm::vec1;
auto	toGLM(Vector2 const& v) -> glm::vec2;
auto	toGLM(Vector3 const& v) -> glm::vec3;
auto	toGLM(Vector4 const& v) -> glm::vec4;
auto	toGLM(Matrix4 const& v) -> glm::mat4;

EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END