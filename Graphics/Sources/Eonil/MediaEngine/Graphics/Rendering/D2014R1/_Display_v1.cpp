//
//  _Display_v1.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/16/13.
//
//

#include "_Display_v1.h"
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

namespace
Rendering
{
	namespace
	D2014R1
	{

		_Display_v1::_Display_v1() : _vp(Bounds2::Utility::NaN()), _reg(0, 0)
		{
		}
		_Display_v1::_Display_v1(Bounds2 const boundsInWindow, Scalar const frameScale) : _vp(boundsInWindow), _reg(boundsInWindow.aspectRatio(), frameScale)
		{
		}
		
		
		
		
		
		_Regulator_v2 const&
		_Display_v1::regulator() const
		{
			return	_reg;
		}
		_Viewport_v1 const&
		_Display_v1::viewport() const
		{
			return	_vp;
		}
		

		
		Vector2 const
		_Display_v1::volumeOfPixel() const
		{
			Vector2	vp_vol	=	_reg.volumeOfViewportInRegularScreenSpace();
			Bounds2	b0		=	_vp.boundsInWindow();
			Vector2	sz0		=	b0.size();
			return	Vector2(vp_vol.x / sz0.x, vp_vol.y / sz0.y);
		}
		
		
		
		
		
		
		
		
		
		
		
		Matrix4 const
		_Display_v1::projectionMatrix() const
		{
			Matrix4		regm	=	_reg.aspectRatioCompensationTransformMatrix();
			Matrix4		vpm		=	_vp.projectionMatrix();
			
			return		vpm * regm;
		}
		Matrix4 const
		_Display_v1::unprojectionMatrix() const
		{
			return	projectionMatrix().inversion();
		}
		
		
		
		

		
		
		
		
		
		
		
		
	}
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END

