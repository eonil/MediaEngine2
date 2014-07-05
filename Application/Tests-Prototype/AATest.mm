//
//  AATest.cpp
//  EonilGraphicsRunningTester
//
//  Created by Hoon Hwangbo on 6/10/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include <cstdlib>
#include <cstring>
#include "AATest.h"
#include <GLKit/GLKit.h>

#ifndef GLM_FORCE_RADIANS
#define GLM_FORCE_RADIANS 1
#endif
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <Eonil/MediaEngine/Graphics.h>
using namespace Eonil::MediaEngine::Graphics::Value;



bool const
binaryEqual(void const* m0, void const* m1, size_t const len)
{
	return	memcmp(m0, m1, len) == 0;
}


union
CONV3
{
	GLKVector3	GLKV;
	Vector3		EEV;
	
	CONV3(GLKVector3 const& glkv) : GLKV(glkv) {}
	CONV3(Vector3 const& eev) : EEV(eev) {}
};
union
CONV4
{
	GLKVector4	GLKV;
	Vector4		EEV;
//	glm::vec4	GLM;
	
	CONV4(GLKVector4 const& glkv) : GLKV(glkv) {}
	CONV4(Vector4 const& eev) : EEV(eev) {}
	CONV4(glm::vec4 const& glm) : EEV(Vector4(glm.x, glm.y, glm.z, glm.w)) {}
};
union
CONV16
{
	float		components[16];
	GLKMatrix4	GLK;
	Matrix4		EE;
	glm::mat4	GLM;
	
	CONV16(GLKMatrix4 const glk) : GLK(glk) {}
	CONV16(Matrix4 const ee) : EE(ee) {}
	CONV16(glm::mat4 const glm) : GLM(glm) {}
};
	
static_assert(sizeof(CONV16) == sizeof(float)*16, "");

	
	
	

GLKVector4 const
GLK(CONV4 const v)
{
	return	v.GLKV;
}
GLKVector3 const
GLK(CONV3 const v)
{
	return	v.GLKV;
}



void
tassert(bool const cond)
{
	if (not cond)
	{
		printf("test failed.\n");
		abort();
	}
}
void
tassertEqual(float current, float reference)
{
	if (current == reference)
	{
		printf("Testing float value equality %f == %f passed.\n", current, reference);
	}
	else
	{
		printf("Testing float value equality %f == %f failed.\n", current, reference);
		abort();
	}
}

void
tassertEqual(CONV3 const a, CONV3 const b)
{
	if (binaryEqual(&a, &b, sizeof(CONV3)))
	{
		printf("Testing float value equality %f,%f,%f == %f,%f,%f passed.\n", a.EEV.x, a.EEV.y, a.EEV.z, b.EEV.x, b.EEV.y, b.EEV.z);
	}
	else
	{
		printf("Testing float value equality %f,%f,%f == %f,%f,%f failed.\n", a.EEV.x, a.EEV.y, a.EEV.z, b.EEV.x, b.EEV.y, b.EEV.z);
		abort();
	}

}

void
tassertEqual(CONV4 const a, CONV4 const b)
{
	if (binaryEqual(&a, &b, sizeof(CONV4)))
	{
		printf("Testing float value equality %f,%f,%f,%f == %f,%f,%f,%f passed.\n", a.EEV.x, a.EEV.y, a.EEV.z, a.EEV.w, b.EEV.x, b.EEV.y, b.EEV.z, b.EEV.w);
	}
	else
	{
		printf("Testing float value equality %f,%f,%f,%f == %f,%f,%f,%f failed.\n", a.EEV.x, a.EEV.y, a.EEV.z, a.EEV.w, b.EEV.x, b.EEV.y, b.EEV.z, b.EEV.w);
		abort();
	}
}

	
	
//void
//tassertEqual(Vector4 const a, GLKVector4 const b)
//{
//	tassertEqual(CONV4(a), CONV4(b));
//}









using namespace Eonil::MediaEngine::Graphics::Value;

void
TestVector()
{
//	printf("sizeof v4 = %d", sizeof(Vector4));
//	abort();
	{
		
	}
	{
		
		Vector2	v(1,2);
		Vector2	v2	=	v;
		
		tassertEqual(v2.x, 1);
		tassertEqual(v2.y, 2);
	}
	{
		
		Vector2	v1(1,2);
		Vector2	v2(1,2);
		Vector2	v3	=	v1 + v2;
		
		tassertEqual(v3.x, 2);
		tassertEqual(v3.y, 4);
		
		
	}
	{
		Vector2	v2(0,0);
		Vector3	v3(0,0,0);
		Vector4	v4(0,0,0,0);
	}
	{
		Vector3	v1(1,1,1);
		Vector3	v2(2,2,2);
		Vector3	v3	=	v1 + v2;
		
		tassertEqual(v3.x, 3);
		tassertEqual(v3.y, 3);
		tassertEqual(v3.z, 3);
	}
	//	operators.
	{
		Vector4	v1(1,1,1,1);
		Vector4	v2	=	v1 + 3;
		Vector4	v3	=	v1 - 3;
		Vector4	v4	=	v1 * 3;
		Vector4	v5	=	v1 / 2;
		
		tassertEqual(v2, Vector4(4,4,4,4));
		tassertEqual(v3, Vector4(-2,-2,-2,-2));
		tassertEqual(v4, Vector4(3,3,3,3));
		tassertEqual(v5, Vector4(0.5, 0.5, 0.5, 0.5));
	}
	//	productions.
	{
		Vector3	v1(2,3,4);
		Vector3	v2(6,7,8);
		
		tassertEqual(v1.dotProductionWithVector(v2), GLKVector3DotProduct(GLK(v1), GLK(v2)));
		tassertEqual(v1.crossProductionWithVector(v2), GLKVector3CrossProduct(GLK(v1), GLK(v2)));
	}
	//	etcs.
	{
		Vector4	v0(1,2,3,4);
		Vector4	v1(5,6,7,8);
		float	t(0.5);
		tassertEqual(v0.norm(), GLKVector4Normalize(GLK(v0)));
		tassertEqual(v0.length(), GLKVector4Length(GLK(v0)));
		tassertEqual(v0.distanceToVector(v1), GLKVector4Distance(GLK(v0), GLK(v1)));
		tassertEqual(v0.projectionOntoVector(v1), GLKVector4Project(GLK(v0), GLK(v1)));
		tassertEqual(Vector4::Utility::vectorUsingLinearInterpolationBetweenVectors(v0, v1, t), GLKVector4Lerp(GLK(v0), GLK(v1), t));
	}
	
//	abort();
}






















void
TestMatrix()
{
	{
		Matrix4		m0		=	Matrix4::Utility::identity();
		GLKMatrix4	glkm0	=	GLKMatrix4Identity;
		
		tassert(binaryEqual(&m0, &glkm0, 16*4));
	}
	//	multiplication equality.
	{
		Matrix4		a0		=	Matrix4::Utility::scaleWithScalar(3, 3, 3);
		Matrix4		b0		=	Matrix4::Utility::translationWithScalars(7, 7, 7);
		Matrix4		c0		=	b0 * a0;
		
		glm::mat4	a1		=	glm::scale(glm::vec3(3.0f, 3.0f, 3.0f));
		glm::mat4	b1		=	glm::translate(glm::vec3(7.0f, 7.0f, 7.0f));
		glm::mat4	c1		=	b1 * a1;
		
//		CONV16		x0(c0);
//		CONV16		x1(c1);
		
		tassert(binaryEqual(&c0, &c1, 4*16));
	}
	//	multiplication order.
	{
		Matrix4		a0		=	Matrix4::Utility::scaleWithScalar(3, 3, 3);
		Matrix4		b0		=	Matrix4::Utility::translationWithScalars(7, 7, 7);
		Matrix4		c0		=	b0 * a0;
		
		/*
		 Latter application must be at left.
		 */
		
		Vector4		p0		=	Vector4(1,0,0,1);
		Vector4		p1		=	c0.transform(p0);
		Vector4		p2		=	Vector4(1*3+7,7,7,1);
		
		tassertEqual(p1, p2);
	}
	
	//	multiplication order.
	{
		glm::mat4	a0		=	glm::scale(glm::vec3(3.0f, 3.0f, 3.0f));
		glm::mat4	b0		=	glm::translate(glm::vec3(7.0f, 7.0f, 7.0f));
		glm::mat4	c0		=	b0 * a0;
		
		/*
		 Latter application transform matrix must be at left.
		 Transform matrix must be left, and transforming target point must be right.
		 If order is different, result is invalid.
		 */
		
		glm::vec4	p0		=	glm::vec4(1,0,0,1);
		glm::vec4	p1		=	c0 * p0;
		glm::vec4	p2		=	glm::vec4(1*3+7,7,7,1);
		
		tassertEqual(p1, p2);
	}
}















