//
//  TransformationQueue.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/15/13.
//
//

#ifndef __EonilGraphics__TransformationQueue__
#define __EonilGraphics__TransformationQueue__

#include "../Transform.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Optimization
	{
		using namespace	Eonil::Improvisations::MediaEngine::Graphics::Value;
		
		/*!
		 Batched matrix resolution facility.
		 
		 All the vector/matrix codes are alreay vectorized, but still
		 we can optimize them by batching which will increase program
		 code locality.
		 
		 @todo
		 This is not proven and tested. Implement and prove by measuring.
		 */
		class
		TransformationQueue
		{
		public:
			TransformationQueue(Size const count = 0);
			~TransformationQueue();
			
			void		resize(Size const count);
			void		resolveAll();
			
		private:
			Size		_c	=	0;
			
			Vector3*	_ss	=	nullptr;
			Quaternion*	_rs	=	nullptr;
			Vector3*	_ts	=	nullptr;
			
			Matrix4*	_ms	=	nullptr;
		};
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics__TransformationQueue__) */
