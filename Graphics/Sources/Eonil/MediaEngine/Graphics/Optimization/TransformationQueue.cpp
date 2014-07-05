//
//  TransformationQueue.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/15/13.
//
//

#include "TransformationQueue.h"
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

namespace
Optimization
{
	namespace
	{
		static inline void
		resetAllAsScales(Vector3 const* const __restrict__ scales, Matrix4* const __restrict__ transforms, sz const count)
		{
			for (sz i=0; i<count; i++)
			{
				transforms[i]	=	Matrix4::Utility::scaleWithVector(scales[i]);
			}
		}
		static inline void
		applyAllRotations(Quaternion const* const __restrict__ rotations, Matrix4* const __restrict__ transforms, sz const count)
		{
			for (sz i=0; i<count; i++)
			{
				Matrix4 const	rm	=	Matrix4::Utility::rotationWithQuaternion(rotations[i]);
				Matrix4 const	tm2	=	transforms[i] * rm;
				transforms[i]		=	tm2;
			}
		}
		static inline void
		applyAllTransforms(Vector3 const* const __restrict__ translations, Matrix4* const __restrict__ transforms, sz const count)
		{
			for (sz i=0; i<count; i++)
			{
				Matrix4 const	tm	=	Matrix4::Utility::translationWithVector(translations[i]);
				Matrix4 const	tm2	=	transforms[i] * tm;
				transforms[i]		=	tm2;
			}
		}
	}
	
	
	
	TransformationQueue::TransformationQueue(sz const count)
	{
		resize(count);
	}
	TransformationQueue::~TransformationQueue()
	{
		resize(0);
	}
	
	void
	TransformationQueue::resize(const sz count)
	{
		if (_c != count)
		{
			delete[]	_ss;
			delete[]	_rs;
			delete[]	_ts;
			delete[]	_ms;
			
			_ss	=	new Vector3[count];
			_rs	=	new Quaternion[count];
			_ts	=	new Vector3[count];
			_ms	=	new Matrix4[count];
		}
	}
	
	void
	TransformationQueue::resolveAll()
	{
		resetAllAsScales(_ss, _ms, _c);
		applyAllRotations(_rs, _ms, _c);
		applyAllTransforms(_ts, _ms, _c);
	};
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END
