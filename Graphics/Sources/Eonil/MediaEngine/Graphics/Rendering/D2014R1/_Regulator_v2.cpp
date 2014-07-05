//
//  _Regulator_v2.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/16/13.
//
//

#include "_Regulator_v2.h"
#include "../../Debugging/Doctor.h"
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

namespace
Rendering
{
	namespace
	D2014R1
	{

		
		
			
		_Regulator_v2::_Regulator_v2() : _Regulator_v2(0)
		{
		}
		_Regulator_v2::_Regulator_v2(Scalar const aspectRatio, Scalar const frameScale) : _aspect_ratio(aspectRatio), _viewport_scale(frameScale)
		{
			Debugging::Doctor::assertForZeroOrNormal(_aspect_ratio);
			Debugging::Doctor::assertForZeroOrNormal(_viewport_scale);
		}
		
		
		
		
		
		
		
		
		
		
		
		
		Scalar const
		_Regulator_v2::aspectRatio() const
		{
			_assert_validity();
			
			return	_aspect_ratio;
		}
		Matrix4 const
		_Regulator_v2::aspectRatioCompensationTransformMatrix() const
		{
			_assert_validity();
			
			Vector2	vol		=	volumeOfViewportInRegularScreenSpace();
			Vector3	scale0	=	Vector3(1.0f/vol.x, 1.0f/vol.y, 1.0f);
			Vector3	scale1	=	scale0 * _viewport_scale;		//	Global override.
			return	Matrix4::Utility::scaleWithVector(scale1);
			
//				_assert_validity();
//				
//				Vector2	vol		=	volumeOfViewportInRegularScreenSpace();
//				Vector3	scale0	=	Vector3(1.0f/vol.x, 1.0f/vol.y, 1.0f);
//				Vector3	scale1	=	scale0 * 2;						//	Multiply 2 because length of GL screen space is 2 (-1~+1).
//				Vector3	scale2	=	scale1 * _viewport_scale;		//	Global override.
//				return	Matrix4::Utility::scaleWithVector(scale2);
		}
		
		
		
		Bounds2 const
		_Regulator_v2::boundsOfViewportInRegularScreenSpace() const
		{
			_assert_validity();
			
			return	Bounds2(0, 0).boundsWithDisplacementOfEdges(volumeOfViewportInRegularScreenSpace() * 0.5);
		}
		Vector2 const
		_Regulator_v2::volumeOfViewportInRegularScreenSpace() const
		{
			_assert_validity();
			
			Scalar	aspect_ratio	=	aspectRatio();
			return	aspect_ratio < 1.0f ? Vector2(1.0f, 1.0f/aspect_ratio) : Vector2(aspect_ratio, 1.0f);
		}
		Vector2 const
		_Regulator_v2::volumeOfInnerSquareInRegularScreenSpace() const
		{
			_assert_validity();
			
			return	Vector2(1,1);
		}
		Vector2 const
		_Regulator_v2::volumeOfOuterSquareInRegularScreenSpace() const
		{
			_assert_validity();
			
			Scalar	aspect_ratio	=	aspectRatio();
			Vector2	vol		=	aspect_ratio < 1.0f ? Vector2(1.0f/aspect_ratio, 1.0f/aspect_ratio) : Vector2(aspect_ratio, aspect_ratio);
			return	vol;
		}
		
		
		
		
		
		
		
		
		Vector4 const
		_Regulator_v2::projectPoint(const Vector4 pointInRSS) const
		{
			return	aspectRatioCompensationTransformMatrix().transform(pointInRSS);
		}
		Vector4 const
		_Regulator_v2::unprojectPoint(const Vector4 pointInNDC) const
		{
			return	aspectRatioCompensationTransformMatrix().inversion().transform(pointInNDC);
		}
		
		Bounds2 const
		_Regulator_v2::projectBounds(const Bounds2 boundsInRSS) const
		{
			return	boundsInRSS.boundsWithTransformationByMatrix(aspectRatioCompensationTransformMatrix());
		}
		Bounds2 const
		_Regulator_v2::unprojectBounds(const Bounds2 boundsInNDC) const
		{
			return	boundsInNDC.boundsWithTransformationByMatrix(aspectRatioCompensationTransformMatrix().inversion());
		}
		
		
		
		
		void
		_Regulator_v2::_assert_validity() const
		{
			Debugging::Doctor::assertForZeroOrNormal(_aspect_ratio);
			Debugging::Doctor::assertForZeroOrNormal(_viewport_scale);
			
			err9_converted_legacy_assertion(_aspect_ratio != 0);
		}
		
		
		
		
		
	}
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END





