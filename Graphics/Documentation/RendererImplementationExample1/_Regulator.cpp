//
//  _Regulator.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/21/13.
//
//

#include "_Regulator.h"


#include "../Debugging/Doctor.h"


namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	_DEV_
	{
		_Regulator::_Regulator()
		{
		}
		_Regulator::_Regulator(Bounds2 const bounds, Scalar const scale)
		{
			_vp_bounds	=	bounds;
			_vp_scale	=	scale;
		}
//				
//				_aspect_ratio		=	scene.viewportBounds.width() / scene.viewportBounds.height();
//				_screen_vol			=	aspect_ratio < 1.0f ? Vector2(1.0f/aspect_ratio) : Vector2(aspect_ratio, 1.0f);
//				_in_sq_vol			=	Vector2(1.0f, 1.0f);
//				_out_sq_vol			=	longer_vertical ? Vector2(1.0f/aspect_ratio, 1.0f/aspect_ratio) : Vector2(aspect_ratio, aspect_ratio);
//			}

		
		Bounds2 const
		_Regulator::boundsOfViewport() const
		{
			_assert_validity();
			
			return	_vp_bounds;
		}
		
//			Rect const
//			_Regulator::boundsOfInnerSquare() const
//			{
//				Scalar	aspect_ratio	=	aspectRatio();
//				Vector2	inner_bounds	=	Vector2(<#Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector2 &&#>)
//			}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		Scalar const
		_Regulator::aspectRatio() const
		{
			_assert_validity();
			
			return	_vp_bounds.aspectRatio();
//				return	_vp_bounds.width() / _vp_bounds.height();
		}
		Matrix4 const
		_Regulator::aspectRatioCompensationTransformMatrix() const
		{
			_assert_validity();
			
			Vector2	vol		=	volumeOfViewportInRegularScreenSpace();
			Vector3	scale0	=	Vector3(1.0f/vol.x, 1.0f/vol.y, 1.0f);
			Vector3	scale1	=	scale0 * 2;				//	Multiply 2 because length of GL screen space is 2 (-1~+1).
			Vector3	scale2	=	scale1 * _vp_scale;		//	Global override.
			return	Matrix4::Utility::scaleWithVector(scale2);
		}
		
		Vector2 const
		_Regulator::volumeOfViewportInRegularScreenSpace() const
		{
			_assert_validity();
			
			Scalar	aspect_ratio	=	aspectRatio();
			return	aspect_ratio < 1.0f ? Vector2(1.0f, 1.0f/aspect_ratio) : Vector2(aspect_ratio, 1.0f);
		}
		Vector2 const
		_Regulator::volumeOfInnerSquareInRegularScreenSpace() const
		{
			_assert_validity();
			
			return	Vector2(1,1);
		}
		Vector2 const
		_Regulator::volumeOfOuterSquareInRegularScreenSpace() const
		{
			_assert_validity();
			
			Scalar	aspect_ratio	=	aspectRatio();
			Vector2	vol		=	aspect_ratio < 1.0f ? Vector2(1.0f/aspect_ratio, 1.0f/aspect_ratio) : Vector2(aspect_ratio, aspect_ratio);
			return	vol;
		}
		
		Vector2 const
		_Regulator::volumeOfPixel() const
		{
			_assert_validity();
			
			Vector2	sz		=	_vp_bounds.size();
			Vector2	vp_vol	=	volumeOfViewportInRegularScreenSpace();
			return	Vector2(vp_vol.x / sz.x, vp_vol.y / sz.y);
		}
		
		
		
		
		
		
		Vector4 const
		_Regulator::projectPoint(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector4 pointInRSS) const
		{
			return	aspectRatioCompensationTransformMatrix().transform(pointInRSS);
		}
		Vector4 const
		_Regulator::unprojectPoint(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector4 pointInNDC) const
		{
			return	aspectRatioCompensationTransformMatrix().inversion().transform(pointInNDC);
		}
		
		Bounds2 const
		_Regulator::projectBounds(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Bounds2 boundsInRSS) const
		{
			return	boundsInRSS.boundsWithTransformationByMatrix(aspectRatioCompensationTransformMatrix());
		}
		Bounds2 const
		_Regulator::unprojectBounds(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Bounds2 boundsInNDC) const
		{
			return	boundsInNDC.boundsWithTransformationByMatrix(aspectRatioCompensationTransformMatrix().inversion());
		}
		
		
		
		
		void
		_Regulator::_assert_validity() const
		{
			Debugging::Doctor::assertForZeroOrNormal(_vp_scale);
//				Debugging::Doctor::assertForZeroOrNormal(_aspect_ratio);
//				Debugging::Doctor::assertForZeroOrNormal(_screen_vol.x);
//				Debugging::Doctor::assertForZeroOrNormal(_screen_vol.y);
//				Debugging::Doctor::assertForZeroOrNormal(_in_sq_vol.x);
//				Debugging::Doctor::assertForZeroOrNormal(_in_sq_vol.y);
//				Debugging::Doctor::assertForZeroOrNormal(_out_sq_vol.x);
//				Debugging::Doctor::assertForZeroOrNormal(_out_sq_vol.y);
			Debugging::Doctor::assertForZeroOrNormal(_vp_bounds.minimum.x);
			Debugging::Doctor::assertForZeroOrNormal(_vp_bounds.minimum.y);
			Debugging::Doctor::assertForZeroOrNormal(_vp_bounds.maximum.x);
			Debugging::Doctor::assertForZeroOrNormal(_vp_bounds.maximum.y);
		}
		
		
		
		
		
	}
	
	
	
	
	
	
	
	
}}}}





