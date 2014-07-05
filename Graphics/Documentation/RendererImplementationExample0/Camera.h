//
//  Camera.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__Camera__
#define __EonilGraphics__Camera__

#include "Common.h"

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

	/*!
	 Abstracts rendering view angle and projection information.
	 
	 @note
	 Camera defines view transform matrix.
	 View matrix is *how transform the world into the screen space*.
	 
	 Essentially, this is resolved by some kind of inverse of camera transform.
	 To get started, let's think in real-world camera. There's an apple,
	 and a camera which capturing it. If camera moves to left, the apple
	 in the shot will move to right. Transformation of the world is exactly
	 inverse to camera's transform. We can generalize this to all SRT
	 transforms, and finally, we get working free camera.
	 
	 This is different with inverted matrix. Because inverted matrix applied
	 in TRS order. The view matrix should be resolved by creating a new 
	 matrix by applying all inversed SRT in right order.
	 
	 Also, aspect-ratio need to be applied by multiplying proper scailing
	 matrix at last.
	 
	 View matrix from camera SRT is a lot more primitive, intuitive,
	 consistent and general than `gluLookAt`. The `gluLookAt` function is 
	 a way abbreviated, so it's not good as an assembly block.
	 
	 @note
	 SRT applying order may be confused. It should follow plain
	 SRT order. Because camera's target (= shot center) shouldn't be moved 
	 by scailing.
	 
	 @ref
	 http://www.songho.ca/opengl/gl_projectionmatrix.html
	 http://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml
	 */
	class
	Camera
	{
	public:
		Camera();
		Scalar const		aspectRatio() const;
//			Matrix const		resolveViewMatrix() const;
		
	public:
		void				setAspectRatio(Scalar const value);
		
	private:
		Scalar				_aspr;
	};
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics__Camera__) */
