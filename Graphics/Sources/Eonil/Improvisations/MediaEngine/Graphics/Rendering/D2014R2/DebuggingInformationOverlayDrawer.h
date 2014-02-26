//
//  DebuggingInformationOverlayDrawer.h
//  Graphics
//
//  Created by Hoon H. on 2/22/14.
//
//

#ifndef __Graphics__DebuggingInformationOverlayDrawer__
#define __Graphics__DebuggingInformationOverlayDrawer__

#include "../../Common.h"
#include "CPUTransformLineDrawer.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{			
			
			/*!
			 Performance is not concern.
			 All the transforms must be final transform. (from local to screen)
			 */
			class
			DebuggingInformationOverlayDrawer
			{
				CPUTransformLineDrawer	_line_drawer{};
				Scalar					_uni_scale{1};
				
			public:
				
				
			public:
				DebuggingInformationOverlayDrawer(Scalar const& objectUniformScale = 1);
				
				auto	objectUniformScale() const -> Scalar const&;
				auto	objectUniformScale() -> Scalar&;
				
				auto	drawNull(DisplayScreenFrame const& frame, Matrix4 const& transform, Vector3 const& radius = {1,1,1}) const -> void;
				
				auto	drawBox(DisplayScreenFrame const& frame, Matrix4 const& transform, Vector2 const& halfSize = {1,1}, Vector4 const& color = {1,1,1,1}) const -> void;
				auto	drawCube(DisplayScreenFrame const& frame, Matrix4 const& transform, Vector3 const& halfSize = {1,1,1}, Vector4 const& color = {1,1,1,1}) const -> void;

//				auto	drawCircle(Matrix4 const& transform, Vector2 const& radius = {1,1}) const -> void;
//				auto	drawSphere(Matrix4 const& transform, Vector3 const& radius = {1,1,1}) const -> void;
//				
//				auto	drawPixelGrid(Matrix4 const& transform, Vector2 const& cellHalfSize, Vector2 const& cellHalfCount) const -> void;
//				auto	drawVoxelGrid(Matrix4 const& transform, Vector3 const& cellHalfSize, Vector3 const& cellHalfCount) const -> void;
			};
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__DebuggingInformationOverlayDrawer__) */
