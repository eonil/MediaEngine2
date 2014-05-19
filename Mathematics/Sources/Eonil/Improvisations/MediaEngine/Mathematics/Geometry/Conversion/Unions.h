//
//  Unions.h
//  Mathematics
//
//  Created by Hoon Hwangbo on 6/27/13.
//
//

#pragma once

/*!
 Whenever possible, avoid using of this code from client code.
 This is intended to be internal implementation details, and can
 be changed at any time. 
 Anyway, sometimes we need easy conversion method, and this will 
 provide it using union.
 

 
 UPDATE
 ------
 Recently, I got that C++ standard doesn't guarantee reading/writing
 of binary converted value via union. That means, union method is not
 safer then pointer-type-punning or `reinterpret_cast` method. So I am
 considering re-writing all these code with `reinterpret_cast` because
 that's simpler and all these conversion always requires memory layout
 equality.
 
 @todo
 Review and consider using simpler `reinterpret_cast`.
 */








#include "../../ImplementationOnlyCommon.h"


#include "../../Common.h"
#include "../Vector.h"
#include "../Matrix.h"

#if	EE_LANG_OBJC && (EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
/*
 Do not include whole GLKit which needs Objective-C context.
 */
//#include <GLKit/GLKit.h>
#include <GLKit/GLKitBase.h>
#include <GLKit/GLKMath.h>
#endif

EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN
namespace
Conversion
{
	static_assert(sizeof(Scalar) == 4, "Size of a scalar must be 4 bytes.");
	
	
	union
	FLOAT32x16
	{
		float								components[16];
		
#if	EE_LANG_OBJC && (EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
		GLKMatrix4							GLK;
#endif
		glm::mat4							GLM;
		Matrix4								EE;
		
#if	EE_LANG_OBJC && (EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
		FLOAT32x16(GLKMatrix4 const glk) : GLK(glk) {}
#endif
		
		FLOAT32x16(glm::mat4 const glm) : GLM(glm) {}
		FLOAT32x16(Matrix4 const ee) : EE(ee) {}
		FLOAT32x16(float const* const components)
		{
			for (Size i=0; i<16; i++)
			{
				this->components[i]	=	components[i];
			}
		}
	}
	__attribute__((aligned(16)));
	
	
	
	static_assert(sizeof(FLOAT32x16) == sizeof(Scalar) * 16, "Size of 4x4 matrix must be 16 scalars.");
	static_assert(sizeof(FLOAT32x16) == sizeof(glm::mat4), "Size of 4x4 matrix must be 16 scalars.");
	static_assert(sizeof(FLOAT32x16) == sizeof(Matrix4), "Size of 4x4 matrix must be 16 scalars.");
#if	EE_LANG_OBJC && (EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
	static_assert(sizeof(FLOAT32x16) == sizeof(GLKMatrix4), "Size of 4x4 matrix must be 16 scalars.");
#endif
	
	
	
	
	
	
	
	
	
	
	
	
	
	union
	FLOAT32x4
	{
		float								components[4];
		
#if	EE_LANG_OBJC && (EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
		GLKVector4							GLK;
#endif
		glm::vec4							GLM;
		Vector4								EE;
		
#if	EE_LANG_OBJC && (EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
		FLOAT32x4(GLKVector4 const glk) : GLK(glk) {}
#endif
		
		FLOAT32x4(glm::vec4 const glm) : GLM(glm) {}
		FLOAT32x4(Vector4 const ee) : EE(ee) {}
	}
	__attribute__((aligned(16)));
	
	static_assert(sizeof(FLOAT32x4) == sizeof(Scalar) * 4, "Size of 4D vector must be 4 scalars.");
	static_assert(sizeof(FLOAT32x4) == sizeof(glm::vec4), "Size of 4D vector must be 4 scalars.");
	static_assert(sizeof(FLOAT32x4) == sizeof(Vector4), "Size of 4D vector must be 4 scalars.");
#if	EE_LANG_OBJC && (EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
	static_assert(sizeof(FLOAT32x4) == sizeof(GLKVector4), "Size of 4D vector must be 4 scalars.");
#endif
	
	
	
	
	union
	FLOAT32x3
	{
		float								components[3];
		
#if	EE_LANG_OBJC && (EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
		GLKVector3							GLK;
#endif
		glm::vec3							GLM;
		Vector3								EE;
		
#if	EE_LANG_OBJC && (EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
		FLOAT32x3(GLKVector3 const glk) : GLK(glk) {}
#endif
		
		FLOAT32x3(glm::vec3 const glm) : GLM(glm) {}
		FLOAT32x3(Vector3 const ee) : EE(ee) {}
	};
	
	static_assert(sizeof(FLOAT32x3) == sizeof(Scalar) * 3, "Size of 3D vector must be 3 scalars.");
	static_assert(sizeof(FLOAT32x3) == sizeof(glm::vec3), "Size of 3D vector must be 3 scalars.");
	static_assert(sizeof(FLOAT32x3) == sizeof(Vector3), "Size of 3D vector must be 3 scalars.");
#if	EE_LANG_OBJC && (EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
	static_assert(sizeof(FLOAT32x3) == sizeof(GLKVector3), "Size of 3D vector must be 3 scalars.");
#endif
	
	
	
	
	
	
	union
	FLOAT32x2
	{
		float								components[2];
		
#if	EE_LANG_OBJC && (EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
		GLKVector2							GLK;
#endif
		glm::vec2							GLM;
		Vector2								EE;
		
#if	EE_LANG_OBJC && (EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
		FLOAT32x2(GLKVector2 const glk) : GLK(glk) {}
#endif
		
		FLOAT32x2(glm::vec2 const glm) : GLM(glm) {}
		FLOAT32x2(Vector2 const ee) : EE(ee) {}
	};
	
	static_assert(sizeof(FLOAT32x2) == sizeof(Scalar) * 2, "Size of 2D vector must be 2 scalars.");
	static_assert(sizeof(FLOAT32x2) == sizeof(glm::vec2), "Size of 2D vector must be 2 scalars.");
	static_assert(sizeof(FLOAT32x2) == sizeof(Vector2), "Size of 2D vector must be 2 scalars.");
#if	EE_LANG_OBJC && (EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX)
	static_assert(sizeof(FLOAT32x2) == sizeof(GLKVector2), "Size of 2D vector must be 2 scalars.");
#endif
}
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END

