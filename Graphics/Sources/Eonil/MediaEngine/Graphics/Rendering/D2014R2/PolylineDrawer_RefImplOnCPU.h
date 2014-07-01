//
//  PolylineDrawer_RefImplOnCPU.h
//  Graphics
//
//  Created by Hoon H. on 14/5/23.
//
//

#pragma once
#include "../RenderingCommon.h"
#include "CPUTransformTriangleDrawer.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN






/*!
 Draws a connected stroke with sharp joints.
 
 @todo
 Find and test corner cases.
 
 -	Result undefined if there's some duplicated points.
 
 */
class
PolylineDrawer_RefImplOnCPU final
{
public:
	/*!
	 Provides simple poly-line instancing.
	 Each end will be automaticalled derived.
	 */
	struct
	StrokeInstance
	{
		vec<Vector3>	points			=	{};
	};
	
	/*!
	 Provides full control to adjust end-cap connectivity.
	 */
	struct
	AssemblyInstance
	{
		Vector3			origination		=	{};
		Vector3			destination		=	{};
		vec<Vector3>	passages		=	{};
	};
	
public:
	
	/*!
	 All the point coordinates must be a location in world space.
	 Points are defined as 3D to draw Z-depth correctly. You can utilized depth-buffer features.
	 
	 @param
	 transform
	 World-to-NDC transform.
	 */
	auto	draw(Matrix4 const& RSSToNDC, vec<AssemblyInstance> const& instances, Scalar const& radius, Vector4 const& color) const -> void;
	
	/*!
	 All the point coordinates must be a location in world space.
	 Points are defined as 3D to draw Z-depth correctly. You can utilized depth-buffer features.
	 
	 @param	
	 transform
	 World-to-NDC transform.
	 */
	auto	draw(Matrix4 const& RSSToNDC, vec<StrokeInstance> const& instances, Scalar const& radius, Vector4 const& color) const -> void;
	
private:
	CPUTransformTriangleDrawer	_tri_drawer	=	{};
	
	auto	_draw_single_stroke_in_context(Matrix4 const& RSSToNDC, vec<Vector3> const& points, Scalar const& radius, Vector4 const& color) const -> void;
	
};






EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END
