//
//  PlanarTexture.cpp
//  Graphics
//
//  Created by Hoon H. on 14/7/6.
//
//

#include "PlanarTexture.h"
#include "PlanarTexture____Core.h"
#include "RenderingD2014R2____internal____.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN





CrossPlatformAbstractTexture2DBox::CrossPlatformAbstractTexture2DBox(CrossPlatformAbstractTexture2DBox&& box) : _core(std::move(box._core))
{
}
CrossPlatformAbstractTexture2DBox::CrossPlatformAbstractTexture2DBox(Core&& core) : _core(uptr<Core>(new Core(std::move(core))))
{
}
CrossPlatformAbstractTexture2DBox::~CrossPlatformAbstractTexture2DBox()
{
}


auto
CrossPlatformAbstractTexture2DBox::Utility::textureWithPixels(GenericMemoryRange<const void> memory, const sz &width, const sz &height, bool const& flipInY) -> CrossPlatformAbstractTexture2DBox
{
	return	CrossPlatformAbstractTexture2DBox(Core(Server::Texture2D::Utility::textureWithPixels(memory, width, height, flipInY)));
}

auto
CrossPlatformAbstractTexture2DBox::core() const -> Core const&
{
	return	*_core;
}







EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END