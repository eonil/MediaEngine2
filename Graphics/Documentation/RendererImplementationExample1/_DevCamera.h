//
//  _DevCamera.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/18/13.
//
//

#ifndef __EonilGraphics___DevCamera__
#define __EonilGraphics___DevCamera__

#include "../Common.h"
#include "../Transform.h"

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

	namespace
	_DEV_
	{
		struct
		_DevLens
		{
			virtual Matrix4 const	projectionMatrix() const = 0;
			virtual Matrix4 const	unprojectionMatrix() const = 0;
		};
		struct
		_DevPerspectiveLens final : public _DevLens
		{
			Scalar		left;
			Scalar		right;
			Scalar		top;
			Scalar		bottom;
			Scalar		near;
			Scalar		far;
			
			virtual Matrix4 const	projectionMatrix() const;
			virtual Matrix4 const	unprojectionMatrix() const;
		};
		struct
		_DevOrthographicLens final : public _DevLens
		{
			
			virtual Matrix4 const	projectionMatrix() const;
			virtual Matrix4 const	unprojectionMatrix() const;
		};
		
		
		
		/*!
		 The term *space*, *scope*, *frame* is used to represent for these spaces.
		 
		 world	-	Original space. (WORLD)
		 scope	-	Space transformed by MODELVIEW. (view/observer/camera space)
		 frame	-	NDC. Imagine 3D film. Scope transformed by PROJECTION and divided by `w`.
		 Some people calls this as screen space, but it's duplicated with other term
		 which means actual screen.
		 
		 NDC -> viewport transform will be defined by viewport object.
		 
		 */
		struct
		_DevCamera
		{
			struct
			Range3
			{
				union
				{
					struct
					{
						Scalar		left;
						Scalar		right;
						Scalar		bottom;
						Scalar		top;
						Scalar		near;
						Scalar		far;
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
			
			_DevCamera();
			
			Transform		transform;
			Range3					frame;
			Projection::CODE		projection;
			
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
		};
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics___DevCamera__) */
