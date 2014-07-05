//
//  _Regulator.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/21/13.
//
//

#ifndef __EonilGraphics___DevViewport__
#define __EonilGraphics___DevViewport__

#include "../Common.h"
#include "_Viewport_v1.h"

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

	namespace
	_DEV_
	{
		using namespace	Value;
		
		
		
		/*!
		 Transforms *Regular Screen Space* into NDC.
		 
		 @discussion		This is extra transform between PROJECTION space and NDC.
							After projection, the coordination space will become *Regular Screen Space*
							Which means a regular space based on space unit.
		 
								+-------+---------------+-------+
								|		|				|		|
								|		|				|		|
								|		|				|		|
								|		|				|		|
								|		|				|		|
								|		|				|		|
								|		|				|		|
								+-------+---------------+-------+
		 
							Where the physical screen is outer rectangle, a square in NDC space will look non-square
							shape. Because it will be stretched to fill the screen. This class addresses this
							issue. This defines a largest fitting square (inner-square) in the physical screen,
							and adjust space coordination to fit there. As a result, the space in the above example
							will have rougly 1.5x1 regulated volume. So square rectangle will look square as expected
							like the picture above.
		 
							Though it is rarely needed, this regulator also defines outer-square. In the above example, 
							outer square is defined like this.
									
								+-------------------------------+
								|								|
								|								|
								|								|
								+-------+---------------+-------+
								|		|				|		|
								|		|				|		|
								|		|				|		|
								|		|				|		|
								|		|				|		|
								|		|				|		|
								|		|				|		|
								+-------+---------------+-------+
								|								|
								|								|
								|								|
								+-------------------------------+
		 
							Where the physical screen aspect ratio is 1:1, inner square and outer square are equal.
		 
							The final transform stack is,
		 
								OBJECT -(transform)-> WORLD -(camera transform)-> VIEW -(camera projection)-> RSS -(regulator)-> NDC
		 
							Unlike other transforms, Regulator is only about X/Y distortion, so Z/W coordinate remain untouched.
							(but this may be changed later)
		 
							This also can be though as a *NDC with aspect ratio compensation*.
							This was actually a part of camera projection, but I separated this from there for finer control.

							*Inner Square* - This is a biggest square which can be fit in screen viewport.
							*Outer Square* - This is a smallest square which can contain screen viewport.
		 
							Inner square volume is defined as (1x1), and any other parameters will be adjusted based on inner square.
							Inner square corner is regularized as {-0.5, -0.5, +0.5, +0.5}.
							Inner square origin is always placed at inner square center.

							Outer square and regular screen space shares center position with inner square.
		 */
		class
		_Regulator
		{
		public:
			/*!
			 Creates an empty viewport which is all zero so invalid.
			 
			 THIS CLASS IS DEPRECATED. DO NOT USE THIS. USE CORRESPONDING RECENT VERSION CLASS.
			 */
			_Regulator() __attribute((deprecated));
			
			/*!
			 @param			scale
			 
							This overrides transform matrix overall scailing.
							Doesn't affect any other parameters, but only final matrix.
						
							You can make frame-border padding by setting this to other than 1.0.
							In that case, you can treat the number as ratio of content : screen
							for each axis.
			 
							This will give you a good debugging aid.
			 
			 */
			_Regulator(Bounds2 const bounds, Scalar const scale = 1);
			
			_Viewport_v1 const	viewport() const;
			
			Bounds2 const	boundsOfViewport() const;				//!	Measured in pixels.
//				Rect const		boundsOfInnerSquare() const;			//!	Measured in pixels.
//				Rect const		boundsOfOuterSquare() const;			//!	Measured in pixels.
			
			Scalar const	aspectRatio() const;
			Matrix4 const	aspectRatioCompensationTransformMatrix() const;
			
			Vector2 const	volumeOfViewportInRegularScreenSpace() const;
			Vector2 const	volumeOfInnerSquareInRegularScreenSpace() const;		//!	Always (1x1).
			Vector2 const	volumeOfOuterSquareInRegularScreenSpace() const;
			
			Vector2 const	volumeOfPixel() const;
			
			
			
			Vector4 const	projectPoint(Vector4 const pointInRSS) const;			//!	Project a point from regular screen space into NDC.
			Vector4 const	unprojectPoint(Vector4 const pointInNDC) const;
			
			Bounds2 const	projectBounds(Bounds2 const boundsInRSS) const;			
			Bounds2 const	unprojectBounds(Bounds2 const boundsInNDC) const;
			
		private:
//				_Viewport_v1		_vp;
			Bounds2			_vp_bounds;
			Scalar			_vp_scale;
			
//				struct
//				{
//					Scalar			_aspect_ratio;
//					Vector2			_screen_vol;
//					Vector2			_in_sq_vol;
//					Vector2			_out_sq_vol;
//				}
//				cache;

			
			void			_assert_validity() const;
		};
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics___DevViewport__) */
