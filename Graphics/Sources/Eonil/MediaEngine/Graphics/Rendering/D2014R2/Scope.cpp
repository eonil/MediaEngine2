//
//  Scope.cpp
//  TheMagnetismGame
//
//  Created by Hoon H. on 2014/05/18.
//  Copyright (c) 2014 Eonil Company. All rights reserved.
//

#include "Scope.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN











auto
TransformScope::state() const -> State const&
{
	return	_state;
}
auto
TransformScope::state() -> State&
{
	return	_state;
}

auto
TransformScope::transformationMatrix() const -> Matrix4
{
	return	_state.transform.matrix();
}














EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END
