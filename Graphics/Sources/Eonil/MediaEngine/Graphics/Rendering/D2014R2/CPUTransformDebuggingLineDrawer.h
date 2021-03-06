//
//  CPUTransformDebuggingLineDrawer.h
//  Graphics
//
//  Created by Hoon H. on 2/22/14.
//
//

#pragma once
#include "RenderingD2014R2Common.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN


/*!
 This is mainly designed for debugging information overlay.
 Doesn't fit to final product rendering due to no support for line width.
 (line width support is not required by the GL spec)
 */
class
CPUTransformDebuggingLineDrawer
{
	struct	Core;
	
	uptr<Core>	_core_ptr{};
	
public:
	struct
	Point
	{
		Vector4		location	{};		//	`w` must be always 1.
		Vector4		color		{};
		
		Point() {}
		Point(Vector3 const& location, Vector4 const& color) : location(location, 1), color(color) {}
		Point(Vector4 const& location, Vector4 const& color) : location(location), color(color) {}
	};
	struct
	Instance
	{
		Point		origination	{};
		Point		destination	{};
		
		Instance() {}
		Instance(Point const& origination, Point const& destination) : origination(origination), destination(destination) {}
	};
	
public:
	CPUTransformDebuggingLineDrawer();
	~CPUTransformDebuggingLineDrawer();
	
	/*!
	 @param	instances
	 All points must be placed in the world space.
	 
	 @param	worldToScreenTransform		
	 This must be a whole transform from world to final screen (NDC).
	 Take care that final destination space is NDC, not RSS.
	 */
	auto	drawInstances(vec<Instance> const& instances, Matrix4 const& worldToScreenTransform) const -> void;
};











EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END
