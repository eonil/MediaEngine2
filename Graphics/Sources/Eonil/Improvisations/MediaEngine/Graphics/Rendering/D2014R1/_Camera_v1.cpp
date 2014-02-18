//
//  _Camera_v1.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/26/13.
//
//

#include "_Camera_v1.h"

#include "../../Debugging/Doctor.h"




namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Rendering
	{
		namespace
		D2014R1
		{
			
		
			
			
				
			using namespace	Value;
			
			
			
			
			
			
			
			
			
			
			_Camera_v1::_Camera_v1()
			{
				transform.setScale(Vector3(1,1,1));
				transform.setRotation(Quaternion::Utility::identity());
				transform.setTranslation(Vector3(0,0,0));
				frame.left		=	-1;
				frame.right		=	+1;
				frame.bottom	=	-1;
				frame.top		=	+1;
				frame.near		=	1;
				frame.far		=	10;
				projection		=	Projection::CODE::PERSPECTIVE;
			}
			
			
			
			
			Matrix4 const
			_Camera_v1::worldToScopeMatrix() const
			{
				EEGL_RUN_AS_ASSERTION(Debugging::Doctor::assertCameraValidity(*this));
				EEGL_ASSERT_WITH_REASON(transform.scale().x != 0.0f, "Camera scale.x shouldn't be `0`.");
				EEGL_ASSERT_WITH_REASON(transform.scale().y != 0.0f, "Camera scale.y shouldn't be `0`.");
				EEGL_ASSERT_WITH_REASON(transform.scale().z != 0.0f, "Camera scale.z shouldn't be `0`.");
				
				Vector3	s0		=	transform.scale();
				Vector3	s1(1.0f/s0.x, 1.0f/s0.y, 1.0f/s0.z);
				Matrix4	sm		=	Matrix4::Utility::scaleWithVector(s1);
				
				Quaternion	r0	=	transform.rotation();
				Quaternion	r1	=	r0.inversion();
				Matrix4	rm		=	Matrix4::Utility::rotationWithQuaternion(r1);
				
				Vector3	t0		=	transform.translation();
				Vector3	t1		=	-t0;
				Matrix4	tm		=	Matrix4::Utility::translationWithVector(t1);
				
				Matrix4	VIEW	=	tm * rm * sm;		//	Must be multiplied in reverse order.
				return	VIEW;
			}
			Matrix4 const
			_Camera_v1::scopeToFrameMatrix() const
			{
				EEGL_RUN_AS_ASSERTION(Debugging::Doctor::assertCameraValidity(*this));
				
				switch (projection)
				{
					case
					Projection::CODE::PERSPECTIVE:
					{
						return	Matrix4::Utility::perspective(frame.left, frame.right, frame.bottom, frame.top, frame.near, frame.far);
					}
					case
					Projection::CODE::ORTHOGRAPH:
					{
						return	Matrix4::Utility::orthograph(frame.left, frame.right, frame.bottom, frame.top, frame.near, frame.far);
					}
				}
			}
			Matrix4 const
			_Camera_v1::worldToFrameMatrix() const
			{
				return	scopeToFrameMatrix() * worldToScopeMatrix();		//	Must be multiplied in reverse order.
			}
			
			
			
			Matrix4 const
			_Camera_v1::scopeFromFrameMatrix() const
			{
				Debugging::Doctor::assertCameraValidity(*this);
				
				return	scopeToFrameMatrix().inversion();
			}
			Matrix4 const
			_Camera_v1::worldFromScopeMatrix() const
			{
				Debugging::Doctor::assertCameraValidity(*this);
				
				return	worldToScopeMatrix().inversion();
			}
			Matrix4 const
			_Camera_v1::worldFromFrameMatrix() const
			{
				return	worldFromScopeMatrix() * scopeFromFrameMatrix();	//	Must be multiplied in reverse order.
			}
			
			
			
			
			Vector4 const
			_Camera_v1::transformPointInWorldToScope(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector4 p) const
			{
				return	worldToScopeMatrix().transform(p);
			}
			Vector4 const
			_Camera_v1::transformPointInScopeToFrame(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector4 p) const
			{
				return	scopeToFrameMatrix().transform(p);
			}
			Vector4 const
			_Camera_v1::transformPointInWorldToFrame(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector4 p) const
			{
				return	worldToFrameMatrix().transform(p);
			}
			
			
			
			Vector4 const
			_Camera_v1::transformPointInWorldFromScope(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector4 p) const
			{
				return	worldFromScopeMatrix().transform(p);
			}
			Vector4 const
			_Camera_v1::transformPointInScopeFromFrame(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector4 p) const
			{
				return	scopeFromFrameMatrix().transform(p);
			}
			Vector4 const
			_Camera_v1::transformPointInWorldFromFrame(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector4 p) const
			{
				return	worldFromFrameMatrix().transform(p);
			}
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}
