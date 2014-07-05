//
//  _Viewport_v1.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/16/13.
//
//

#pragma once
#include "../../Common.h"
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
namespace
Rendering
{
	namespace
	D2014R1
	{
		using namespace	Geometry;
	
		
		/*!
		 @discussion			
		 
		 Handles NDC to window space transform.
		 
		 Because this is out of GL pipeline, this won't be used in shaders.
		 Anyway this is required when we convert points in between NDC and window space.
		 Also to set `glViewport` and `glScissor` parameters which needs window space
		 coordinates.
		 
			NDC -(viewport)-> window space
		 
		 Currently this treats client window coordinate is Y-flipped - so we need to flip
		 vertically.
		 */
		class
		_Viewport_v1
		{
		public:
			
			/*!
			 Y is always down in OpenGL coordinate system. If your client window coordinate system is using Y-up
			 system, figure it out how you can convert it into Y-down to use in GL.
			 */
			_Viewport_v1(Bounds2 const boundsInWindow);
			
			Bounds2 const		boundsInWindow() const;
			
			Matrix4 const		projectionMatrix() const;		//!	A transform matrix which transforms a point in NDC into window space.
			Matrix4 const		unprojectionMatrix() const;
			
		private:
			Bounds2				_b;
		};
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
}
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END
