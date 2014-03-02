//
//  DisplayScreenFrame.cpp
//  Graphics
//
//  Created by Hoon H. on 2/23/14.
//
//

#include "DisplayScreenFrame.h"
#include "../../Server/Machine.h"
#include "../D2014R1/_Display_v1.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{
			

			using	Display	=	D2014R1::_Display_v1;
			
			
			
			
			
			
			
			struct
			DisplayScreenFrame::Core
			{
				Bounds2			bounds		{};
				Display			display		{};
				
				Core(Bounds2 const& bounds) : bounds(bounds), display(bounds)
				{
				}
			};

			
			
	
			
			
			
			
			DisplayScreenFrame::DisplayScreenFrame(Bounds2 const& bounds) : _core_ptr(new Core(bounds))
			{
				Server::Machine::machine().setViewport(bounds);
			}
			DisplayScreenFrame::~DisplayScreenFrame()
			{
				Server::Machine::machine().unsetViewport();
			}
			
			
			
			
			auto DisplayScreenFrame::
			regulationTransformMatrix() const -> Matrix4
			{
				return	_core_ptr->display.regulator().aspectRatioCompensationTransformMatrix();
			}




		}
	}

}}}}