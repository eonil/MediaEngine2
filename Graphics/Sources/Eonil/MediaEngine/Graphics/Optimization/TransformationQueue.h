//
//  TransformationQueue.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/15/13.
//
//

#pragma once
#include "../LEGACY_Transform.h"
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

namespace
Optimization
{
	using namespace	Eonil::MediaEngine::Graphics::Geometry;
	
	/*!
	 Batched matrix resolution facility.
	 
	 All the vector/matrix codes are alreay vectorized, but still
	 we can optimize them by batching which will increase program
	 code locality.
	 
	 @todo
	 This is not proven and tested. Implement and prove by measuring.
	 */
	class
	EONIL_MEDIA_ENGINE_DEPRECATE()
	TransformationQueue
	{
	public:
		TransformationQueue(sz const count = 0);
		~TransformationQueue();
		
		void		resize(sz const count);
		void		resolveAll();
		
	private:
		sz			_c	=	0;
		
		Vector3*	_ss	=	nullptr;
		Quaternion*	_rs	=	nullptr;
		Vector3*	_ts	=	nullptr;
		
		Matrix4*	_ms	=	nullptr;
	};
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END

