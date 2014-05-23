//
//  CPUTransformTriangleDrawer.h
//  Graphics
//
//  Created by Hoon H. on 14/5/23.
//
//

#pragma once
#include "../RenderingCommon.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN











/*!
 A triangle drawer which draws triangles in NDC space.
 
 @discussion
 All vertexes must be pre-transformed into NDC.
 
 Points are defined as 3D to output z-depth correctly to provide depth buffer features.
 If you don't use depth-buffer, just set `z` value to any. (I recommend zero).
 
 This is one of most basic drawers. Usually used for test or reference implementations.
 All triangles must be counter-clockwise. Clockwise triangles are not supported.
 */
class
CPUTransformTriangleDrawer
{
	struct	Core;
	
	uptr<Core>		_core_ptr	{};

public:
	using	tex2d	=	Server::PlanarTexture;
	
public:
	struct
	Triangle
	{
		std::array<Vector3, 3>	points	=	{};
	};
	
//	struct
//	CounterClockwiseWindingPointList
//	{
//		vec<Vector3>	points	=	{};
//	};
	
public:
	CPUTransformTriangleDrawer();
	~CPUTransformTriangleDrawer();
	
	/*!
	 @discussion
	 This consumes single draw call.
	 */
	auto	drawTriangleList(GenericMemoryRange<Triangle const> const& triangles, Vector4 const& color) const -> void;
	auto	drawTriangleList(GenericMemoryRange<Triangle const> const& triangles) const -> void;
	
//	/*!
//	 @discussion
//	 This consumes single draw call.
//	 */
//	auto	drawTriangleList(CounterClockwiseWindingPointList const& triangles, Vector4 const& color) const -> void;
};










EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END
