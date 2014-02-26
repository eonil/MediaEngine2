//
//  DisplayScreenFrame.h
//  Graphics
//
//  Created by Hoon H. on 2/23/14.
//
//

#ifndef __Graphics__DisplayScreenFrame__
#define __Graphics__DisplayScreenFrame__

#include "../../Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{
			
			
			
			
			
			
			
			
			
			/*!
			 Defines displaying area of a frame in a client window.
			 
			 @classdesign
			 You should create only one of this class at a time. If you
			 create multiple instances, GL state will be messed, and
			 result is undefined.
			 
			 @discussion
			 This symbolize existence of viewport definition. Literally, 
			 this object set a viewport definition when being created, 
			 and unset the viewport definition when being destroyed.
			 */
			class
			DisplayScreenFrame
			{
				Bounds2		_bounds		{};
				
			public:
				/*!
				 @param	bounds
				 Bounding box of viewport in display window's local coordinate system.
				 */
				DisplayScreenFrame(Bounds2 const& bounds);
				~DisplayScreenFrame();
			};
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__DisplayScreenFrame__) */
