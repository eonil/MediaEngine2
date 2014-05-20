//
//  Transform.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "LEGACY_Transform.h"
#include "Debugging/Doctor.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	{
		EONIL_MEDIA_ENGINE_DEPRECATE()
		Matrix4 const	resolveProjection(_Transform_V1 const& t)
		{
			Matrix4 const	sm	=	Matrix4::Utility::scaleWithVector(t.scale());
			Matrix4 const	rm	=	Matrix4::Utility::rotationWithQuaternion(t.rotation());
			Matrix4 const	tm	=	Matrix4::Utility::translationWithVector(t.translation());
			
			return	sm * rm * tm;
		}
		
		EONIL_MEDIA_ENGINE_DEPRECATE()
		Matrix4 const	resolveUnprojection(Matrix4 const& proj)
		{
			return	proj.inversion();
		}
	}
	
	
#pragma mark	-	Cache
	
	struct
	_Transform_V1::Cache
	{
		Matrix4 const		projection;
		Matrix4 const		unprojection;
		
		static void createOnTransformIfDoesNotExist(_Transform_V1 const& t)
		{
//				EEGL_ASSERT(t._cache == nullptr, "The cache should be currently null to be created.");
			if (t._cache == nullptr)
			{
				t._cache	=	new Cache(t);
			}
		}
		static void destroyOnTransformIfExists(_Transform_V1 const& t)
		{
//				EEGL_ASSERT(t._cache != nullptr, "The cache to destroy does not exist currently.");
			if (t._cache != nullptr)
			{
				delete		t._cache;
				t._cache	=	nullptr;
			}
		}
		
		
		Cache(_Transform_V1 const& t) : projection(resolveProjection(t)), unprojection(resolveUnprojection(projection))
		{
		}
		~Cache()
		{
		}
	};
	
	
	
	

	
	
	
	
	
	
	
	
	
	
#pragma mark	-	Transform
	
	Vector3 const&
	_Transform_V1::scale() const
	{
		return	_s;
	}
	Quaternion const&
	_Transform_V1::rotation() const
	{
		return	_r;
	}		
	Vector3 const&
	_Transform_V1::translation() const
	{
		return	_t;
	}

	
	
	void
	_Transform_V1::setScale(const Vector3 value)
	{			
		_s	=	value;
		Debugging::Doctor::assertTransformValidity(*this);
		
		Cache::destroyOnTransformIfExists(*this);
	}
	void
	_Transform_V1::setRotation(const Quaternion value)
	{			
		_r	=	value;
		Debugging::Doctor::assertTransformValidity(*this);
		
		Cache::destroyOnTransformIfExists(*this);
	}
	void
	_Transform_V1::setTranslation(const Vector3 value)
	{
		_t	=	value;
		Debugging::Doctor::assertTransformValidity(*this);
		
		Cache::destroyOnTransformIfExists(*this);
	}
	
	
	
	
	Matrix4 const
	_Transform_V1::resolveProjectionMatrixIgnoringCache() const
	{
		return	resolveProjection(*this);
	}
	
	Matrix4 const
	_Transform_V1::resolveProjectionMatrix() const
	{
		Cache::createOnTransformIfDoesNotExist(*this);
		return	_cache->projection;
	}
	Matrix4 const
	_Transform_V1::resolveUnprojectionMatrix() const
	{
		Cache::createOnTransformIfDoesNotExist(*this);
		return	_cache->unprojection;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}}}}






