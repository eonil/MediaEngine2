//
//  DisplayScreenFrame.cpp
//  Graphics
//
//  Created by Hoon H. on 2/23/14.
//
//

#include "DisplayScreenFrame.h"
#include "../../Server/Machine.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{
			
			

			
			
	
			
			
			
			
			DisplayScreenFrame::DisplayScreenFrame(Bounds2 const& bounds) : _bounds(bounds)
			{
				Server::Machine::machine().setViewport(bounds);
			}
			DisplayScreenFrame::~DisplayScreenFrame()
			{
				Server::Machine::machine().unsetViewport();
			}
			
			
			
			
			





		}
	}

}}}}