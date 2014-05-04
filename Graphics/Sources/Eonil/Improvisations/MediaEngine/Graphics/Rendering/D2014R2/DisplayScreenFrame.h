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
				struct	Core;
				
				uptr<Core>	_core_ptr	{};

				
			public:
				/*!
				 @param	bounds
				 Bounding box of viewport in display window's local coordinate system.
				 */
				DisplayScreenFrame(Bounds2 const& bounds);
				~DisplayScreenFrame();
				
				/*!
				 Provides pixel dimension of the display surface.
				 Take care that this covers only display surface (client window), not whole a screen.
				 */
				auto	dimensionInPixels() const -> Bounds2;

				/*!
				 Creates a matrix which transforms points in RSS into NDC.
				 If you draw 2x2 square with this transform, it will become biggest filling square in the screen.
				 If the screen is non-square shape, then longer side will have paddings.
				 */
				auto	regulationTransformMatrix() const -> Matrix4;
			};
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__DisplayScreenFrame__) */
