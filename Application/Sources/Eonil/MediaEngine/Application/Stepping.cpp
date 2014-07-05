//
//  Stepping.cpp
//  Application
//
//  Created by Hoon H. on 2/23/14.
//
//

#include "Stepping.h"
EONIL_MEDIA_ENGINE_APPLICATION_NAMESPACE_BEGIN



Stepping::Stepping(DisplayScreenFrame const& frame) : _frame(&frame)
{
}

auto Stepping::
frame() const -> DisplayScreenFrame const&
{
	return	*_frame;
}








EONIL_MEDIA_ENGINE_APPLICATION_NAMESPACE_END
