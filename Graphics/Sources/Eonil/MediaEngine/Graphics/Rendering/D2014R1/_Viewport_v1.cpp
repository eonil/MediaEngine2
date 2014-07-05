//
//  _Viewport_v1.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/16/13.
//
//

#include "_Viewport_v1.h"
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

namespace
Rendering
{
	namespace
	D2014R1
	{

	
	
		
		_Viewport_v1::_Viewport_v1(Bounds2 const boundsInWindow) : _b(boundsInWindow)
		{
		}
		
		
		Bounds2 const
		_Viewport_v1::boundsInWindow() const
		{
			return	_b;
		}
		
		
		Matrix4 const
		_Viewport_v1::projectionMatrix() const
		{
			Vector2	sz0	=	_b.size();
			Vector2	sz1	=	sz0 * 0.5;
			Matrix4	sm	=	Matrix4::Utility::scaleWithScalar(sz1.x, sz1.y, 1);
			
			Vector2	c0	=	_b.center();
			Matrix4	tm	=	Matrix4::Utility::translationWithScalars(c0.x, c0.y, 0);
			
			return	tm * sm;
		}
		Matrix4 const
		_Viewport_v1::unprojectionMatrix() const
		{
			return	projectionMatrix().inversion();
		}
	
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
}
	
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END




