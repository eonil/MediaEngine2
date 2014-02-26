//
//  Stepping.cpp
//  Application
//
//  Created by Hoon H. on 2/23/14.
//
//

#include "Stepping.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Application {
	
	
	
	Stepping::Stepping(DisplayScreenFrame const& frame) : _frame(&frame)
	{
	}
	
	auto Stepping::
	frame() const -> DisplayScreenFrame const&
	{
		return	*_frame;
	}
	
	
	
	
	
	
	
	
}}}}
