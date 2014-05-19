//
//  Transform.h
//  Mathematics
//
//  Created by Hoon Hwangbo on 6/15/13.
//
//

#pragma once
#include "../Common.h"
#include "Vector.h"
#include "Quaternion.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN


/*!
 @note
 Erased because transform concept is too specific to be in this library.
 Also, there's a problem of quaternion vs axis-angle.
 Define specialized transforms in each specialized libraries for thier own needs.
 */



///*!
// Represents generic transform.
// */
//struct
//Transform
//{
//	Quaternion	rotation	=	Quaternion::Utility::identity();
//	Vector3		scale		=	{1,1,1};
//	Vector3		translation	=	{0,0,0};
//	
//	auto		matrix() const -> Matrix4;
//};





EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END