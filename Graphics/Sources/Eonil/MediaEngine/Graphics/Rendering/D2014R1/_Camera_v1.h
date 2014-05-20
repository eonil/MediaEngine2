//
//  _Camera_v1.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/26/13.
//
//

#ifndef __EonilGraphics___Camera_v1__
#define __EonilGraphics___Camera_v1__

#include "../../LEGACY_Transform.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Rendering
	{
		namespace
		D2014R1
		{
		
		
			/*!
			 @brief
			 The term *space*, *scope*, *frame* is used to represent for these spaces.
			 
				world	-	Original space. (WORLD)
				scope	-	Space transformed by MODELVIEW. (view/observer/camera space)
				frame	-	NDC. Imagine 3D film. Scope transformed by PROJECTION and divided by `w`.
							Some people calls this as screen space, but it's duplicated with other term
							which means actual screen.
			 
			 NDC -> viewport transform will be defined by viewport object.
			 
			 @discussion
			 Camera doesn't employ classical concepts like FOV, up vector or target point. This is pretty
			 bare-bone camera, and visible volume and viewing angle is defined by frustum and transform.
			 
			 If you want to control camera with those classical parameters, then you have to build up the
			 frustum and transform parameters from the classical parameters yourself. 
			 
			 Camera is just a tool to create a final transform matrix. The renderer will just accept final
			 transform matrix, so you also can build any matrix with your own way.
			 
	//		 Also, you can create identity camera - which is same with no camera transform - by creating 
	//		 orthographic camera with all paramters to 1. And because you can utilize identity camera, 
	//		 renderer will not provide camera-less rendering mode.
			 
			 @note
			 If you employ the concept of RSS(regular screen space), then you should treat the *frame* 
			 space as RSS rather then NDC. You need to multiply `Regulator` matrix to get final NDC 
			 coordinates.
			 */
			struct
			EONIL_MEDIA_ENGINE_DEPRECATE()
			_Camera_v1
			{
				
				struct
				Range3
				{
					union
					{
						struct
						{
							Scalar		left;			//	-X
							Scalar		right;			//	+X
							Scalar		bottom;			//	-Y
							Scalar		top;			//	+Y
							Scalar		near;			//	-Z
							Scalar		far;			//	+Z
						};
					};
				};
				struct
				Projection 
				{
					enum
					CODE
					{
						PERSPECTIVE,
						ORTHOGRAPH,
					};
				};
				
				
				
				
				
				
	//				struct
	//				Lens
	//				{
	//					virtual Matrix4 const	projectionMatrix() const = 0;
	//					virtual Matrix4 const	unprojectionMatrix() const = 0;
	//				};
	//				struct
	//				PerspectiveLens final : public Lens
	//				{
	//					Scalar		left;
	//					Scalar		right;
	//					Scalar		top;
	//					Scalar		bottom;
	//					Scalar		near;
	//					Scalar		far;
	//					
	//					virtual Matrix4 const	projectionMatrix() const;
	//					virtual Matrix4 const	unprojectionMatrix() const;
	//				};
	//				struct
	//				OrthographicLens final : public Lens
	//				{
	//					
	//					virtual Matrix4 const	projectionMatrix() const;
	//					virtual Matrix4 const	unprojectionMatrix() const;
	//				};
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				_Camera_v1();
				
				_Transform_V1			transform	{};
				Range3					frame		{};
				Projection::CODE		projection	{};
				
				Matrix4 const			worldToScopeMatrix() const;			//!	Creates VIEW matrix.
				Matrix4 const			scopeToFrameMatrix() const;			//!	Creates PROJECTION matrix.
				Matrix4 const			worldToFrameMatrix() const;			//!	Creates VIEW * PROJECTION matrix.
				
				Matrix4 const			worldFromScopeMatrix() const;		//!	invert(VIEW)
				Matrix4 const			scopeFromFrameMatrix() const;		//!	invert(PROJECTION)
				Matrix4 const			worldFromFrameMatrix() const;		//!	invert(PROJECTION) * invert(VIEW)
				
				Vector4 const			transformPointInWorldToScope(Vector4 const p) const;		//!	`w` must be `1`.
				Vector4 const			transformPointInScopeToFrame(Vector4 const p) const;		//!	`w` must be `1`.
				Vector4 const			transformPointInWorldToFrame(Vector4 const p) const;		//!	`w` must be `1`.
				
				Vector4 const			transformPointInScopeFromFrame(Vector4 const p) const;		//!	`w` must be `1`.
				Vector4 const			transformPointInWorldFromScope(Vector4 const p) const;		//!	`w` must be `1`.
				Vector4 const			transformPointInWorldFromFrame(Vector4 const p) const;		//!	`w` must be `1`.
				
				
				
				
				////
				
	//			struct
	//			Utility
	//			{
	//				/*!
	//				 Creates an identity camera.
	//				 This is equal with no camera transform.
	//				 This is an orthographic camera with all parameters are set to +/-1. (near plane is -1, and far plane is +1)
	//				 */
	//				static auto	identity() const -> _Camera_v1;
	//			};
			};
				
				
				
			
			
		}
	}
	
}}}}

#endif /* defined(__EonilGraphics___Camera_v1__) */


