//
//  Transform.h
//  Graphics
//
//  Created by Hoon H. on 14/5/20.
//
//

#pragma once
#include "RenderingD2014R2Common.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN








struct
Transform
{
	Vector3		scale		=	{1,1,1};
	Quaternion	rotation	=	Quaternion::Utility::identity();
	Vector3		translation	=	{0,0,0};
	
	inline auto
	matrix() const -> Matrix4
	{
		using	util	=	Matrix4::Utility;
		
		return	util::translationWithVector(translation) * util::rotationWithQuaternion(rotation) * util::scaleWithVector(scale);
	}
};







EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END
