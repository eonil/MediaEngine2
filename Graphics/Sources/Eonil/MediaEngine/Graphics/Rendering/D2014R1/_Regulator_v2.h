//
//  _Regulator_v2.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/16/13.
//
//

#pragma once
#include "../../Common.h"
#include "_Viewport_v1.h"

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

namespace
Rendering
{
	namespace
	D2014R1
	{
		
		using namespace	Geometry;
		
		
		
		/*!
		 Transforms *Regular Screen Space* into NDC.
		 
		 @discussion		
		 
		 This is an extra transform between PROJECTION space and NDC.
		 After projection, the coordination space will become *Regular Screen Space*
		 Which means a regular space based on space unit.
			 
			 +-------+---------------+-------+
			 |       |               |       |
			 |       |               |       |
			 |       |               |       |
			 |       |               |       |
			 |       |               |       |
			 |       |               |       |
			 |       |               |       |
			 +-------+---------------+-------+
			 
		 Where the physical screen is outer rectangle, a square in NDC space will look non-square
		 shape. Because it will be stretched to fill the screen. This class addresses this
		 issue. This defines a largest fitting square (inner-square) in the physical screen,
		 and adjust space coordination to fit there. As a result, the space in the above example
		 will have regulated volume roughly by 3:2. And then, square rectangle will look like a
		 square as expected like the picture above.
		 
		 Though it is rarely needed, this regulator also defines outer-square. In the above example,
		 outer square is defined like this.
			 
			 +-------------------------------+
			 |								 |
			 |								 |
			 |								 |
			 +-------+---------------+-------+
			 |		 | 				 |		 |
			 |		 |				 |		 |
			 |		 |				 |		 |
			 |		 |				 |		 |
			 |		 |				 |		 |
			 |		 |				 |		 |
			 |		 |				 |		 |
			 +-------+---------------+-------+
			 |								 |
			 |								 |
			 |								 |
			 +-------------------------------+
			 
		 Where the physical screen aspect ratio is 1:1, inner square and outer square are equal.
		 
		 The final transform stack is,
		 
			OBJECT -(transform)-> WORLD -(camera transform)-> VIEW -(camera projection)-> RSS -(regulator)-> NDC
		 
		 Unlike other transforms, Regulator is only about X/Y distortion, and Z/W coordinates remain untouched.
		 (but this may be changed later if there's a critical reason)
		 
		 This also can be thought as a *NDC with aspect ratio compensation*.
		 This was actually a part of camera projection, but I separated this from there for finer control.
		 
		 *Inner Square* - This is a biggest square which can be fit in screen viewport.
		 *Outer Square* - This is a smallest square which can contain screen viewport.
		 
		 Inner square volume is defined as (2x2) just as like NDC, and any other parameters will be adjusted
		 based on inner square.
		 Inner square corner is regularized as {-1, -1, +1, +1}.
		 Inner square origin is always placed at inner square center.
		 
		 Outer square and regular screen space shares center position with inner square.
		 */
		class
		_Regulator_v2
		{
		public:
			/*!
			 Creates an empty viewport which is all zero so invalid.
			 */
			_Regulator_v2();
			
			/*!
			 @param			aspectRatio
			 
							Viewport bounds' width/height.
			 
			 @param			frameScale
			 
							This overrides transform matrix overall scailing.
							Doesn't affect any other parameters, but only final matrix.
						
							You can make frame-border padding by setting this to other than 1.0.
							In that case, you can treat the number as ratio of content : screen
							for each axis.
			 
							This will give you a good debugging aid.
			 
			 */
			_Regulator_v2(Scalar const aspectRatio, Scalar const frameScale = 1);
			
			Scalar const	aspectRatio() const;
			Matrix4 const	aspectRatioCompensationTransformMatrix() const;			//!	Creates a matrix which transforms points in RSS into NDC.
			
			Bounds2 const	boundsOfViewportInRegularScreenSpace() const;
			Vector2 const	volumeOfViewportInRegularScreenSpace() const;
			Vector2 const	volumeOfInnerSquareInRegularScreenSpace() const;		//!	Always (1x1).
			Vector2 const	volumeOfOuterSquareInRegularScreenSpace() const;
			
			
			
			
			Vector4 const	projectPoint(Vector4 const pointInRSS) const;			//!	Project a point from regular screen space into NDC.
			Vector4 const	unprojectPoint(Vector4 const pointInNDC) const;
			
			Bounds2 const	projectBounds(Bounds2 const boundsInRSS) const;
			Bounds2 const	unprojectBounds(Bounds2 const boundsInNDC) const;
			
		private:
			Scalar			_aspect_ratio;		//!	width/height.
			Scalar			_viewport_scale;
			
			void			_assert_validity() const;
		};
		
		
		
		
		
		
		
		
		
		
	}
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END
