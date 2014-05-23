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
 @todo
 Find and test corner cases.
 
 -	If two points are very close...
 
 */
class
PolylineDrawer_RefImplOnCPU final
{
public:
	struct
	Instance
	{
		vec<Vector3>	points	=	{};
	};
	
public:
	/*!
	 All the point coordinates must be a location in NDC space. (must be pre-transformed)
	 Points are defined as 3D to draw Z-depth correctly. You can utilized depth-buffer features.
	 */
	auto	drawInNDCSpace(vec<Instance> const& instances, Scalar const& radius, Vector4 const& color) const -> void;
	
private:
	CPUTransformTriangleDrawer	_tri_drawer	=	{};
	
	auto	_draw_one_in_context(Instance const&, Scalar const& radius, Vector4 const& color) const -> void;
};






EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END
