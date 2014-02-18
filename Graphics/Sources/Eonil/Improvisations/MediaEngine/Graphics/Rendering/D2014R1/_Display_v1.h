//
//  _Display_v1.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/16/13.
//
//

#ifndef __EonilGraphics___Display_v1__
#define __EonilGraphics___Display_v1__

#include "_Regulator_v2.h"
#include "_Viewport_v1.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Rendering
	{
		namespace
		D2014R1
		{
			
			using namespace Eonil::Improvisations::MediaEngine::Graphics::Value;
			
			/*!
			 This is a composition of regulator and viewport.
			 By compositing them, this can provide direct transform between RSS -> window space.
			 Also provides several complex operations which need the two transforms.

			 @discussion
			 This is a tool to create space projection matrix. If you don't want to employ the concept 
			 of RSS, then you don't need to use this class.
			 */
			class
			_Display_v1
			{
			public:
				_Display_v1();
				_Display_v1(Bounds2 const boundsInWindow, Scalar const frameScale = 1);
				
				_Regulator_v2 const&	regulator() const;
				_Viewport_v1 const&		viewport() const;
				
	//			Rect const			boundsOfInnerSquare() const;			//!	Measured in pixels.
	//			Rect const			boundsOfOuterSquare() const;			//!	Measured in pixels.
				Vector2 const		volumeOfPixel() const;					//!	Get single pixel size in regular screen space.
				
				Matrix4 const		projectionMatrix() const;				//!	Creates a transform matrix which projects a point in RSS into window space.
				Matrix4 const		unprojectionMatrix() const;
				
				
			private:
				_Regulator_v2			_reg;
				_Viewport_v1			_vp;
			};
			
	
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
		
}}}}

#endif /* defined(__EonilGraphics___Display_v1__) */




