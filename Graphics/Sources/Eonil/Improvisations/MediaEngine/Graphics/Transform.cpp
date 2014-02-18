//
//  Transform.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "Transform.h"
#include "Debugging/Doctor.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	{
		Matrix4 const	resolveProjection(Transform const& t)
		{
			Matrix4 const	sm	=	Matrix4::Utility::scaleWithVector(t.scale());
			Matrix4 const	rm	=	Matrix4::Utility::rotationWithQuaternion(t.rotation());
			Matrix4 const	tm	=	Matrix4::Utility::translationWithVector(t.translation());
			
			return	sm * rm * tm;
		}
		Matrix4 const	resolveUnprojection(Matrix4 const& proj)
		{
			return	proj.inversion();
		}
	}
	
	
#pragma mark	-	Cache
	
	struct
	Transform::Cache
	{
		Matrix4 const		projection;
		Matrix4 const		unprojection;
		
		static void createOnTransformIfDoesNotExist(Transform const& t)
		{
//				EEGL_ASSERT(t._cache == nullptr, "The cache should be currently null to be created.");
			if (t._cache == nullptr)
			{
				t._cache	=	new Cache(t);
			}
		}
		static void destroyOnTransformIfExists(Transform const& t)
		{
//				EEGL_ASSERT(t._cache != nullptr, "The cache to destroy does not exist currently.");
			if (t._cache != nullptr)
			{
				delete		t._cache;
				t._cache	=	nullptr;
			}
		}
		
		
		Cache(Transform const& t) : projection(resolveProjection(t)), unprojection(resolveUnprojection(projection))
		{
		}
		~Cache()
		{
		}
	};
	
	
	
	

	
	
	
	
	
	
	
	
	
	
#pragma mark	-	Transform
	
	Vector3 const&
	Transform::scale() const
	{
		return	_s;
	}
	Quaternion const&
	Transform::rotation() const
	{
		return	_r;
	}		
	Vector3 const&
	Transform::translation() const
	{
		return	_t;
	}

	
	
	void
	Transform::setScale(const Vector3 value)
	{			
		_s	=	value;
		Debugging::Doctor::assertTransformValidity(*this);
		
		Cache::destroyOnTransformIfExists(*this);
	}
	void
	Transform::setRotation(const Quaternion value)
	{			
		_r	=	value;
		Debugging::Doctor::assertTransformValidity(*this);
		
		Cache::destroyOnTransformIfExists(*this);
	}
	void
	Transform::setTranslation(const Vector3 value)
	{
		_t	=	value;
		Debugging::Doctor::assertTransformValidity(*this);
		
		Cache::destroyOnTransformIfExists(*this);
	}
	
	
	
	
	Matrix4 const
	Transform::resolveProjectionMatrixIgnoringCache() const
	{
		return	resolveProjection(*this);
	}
	
	Matrix4 const
	Transform::resolveProjectionMatrix() const
	{
		Cache::createOnTransformIfDoesNotExist(*this);
		return	_cache->projection;
	}
	Matrix4 const
	Transform::resolveUnprojectionMatrix() const
	{
		Cache::createOnTransformIfDoesNotExist(*this);
		return	_cache->unprojection;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}}}}






