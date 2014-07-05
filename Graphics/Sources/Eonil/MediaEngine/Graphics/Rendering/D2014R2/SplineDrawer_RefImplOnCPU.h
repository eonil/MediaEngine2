//
//  SplineDrawer_RefImplOnCPU.h
//  Graphics
//
//  Created by Hoon H. on 14/5/24.
//
//

#pragma once
#include "RenderingD2014R2Common.h"
#include "PolylineDrawer.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN





//template <typename T>
class
SplineDrawer_RefImplOnCPU final
{
public:
	struct
	Instance : PolylineDrawer::AssemblyInstance
	{
	};
	 
public:
	auto	draw(Matrix4 const& RSSToNDC, vec<Instance> const& instances, Vector4 const& color) const -> void;
	
private:
	PolylineDrawer		_polyliine_drawer	=	{};
};


//template <typename T>
auto
SplineDrawer_RefImplOnCPU::
draw(Matrix4 const& RSSToNDC, vec<Instance> const& instances, Vector4 const& color) const -> void
{
	for (auto const inst0: instances)
	{
		for (auto const p: inst0.passages)
		{
		}
	}
}








EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END

