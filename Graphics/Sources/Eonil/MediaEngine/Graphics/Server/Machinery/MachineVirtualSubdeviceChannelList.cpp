//
//  MachineVirtualSubdeviceChannelList.cpp
//  Graphics
//
//  Created by Hoon H. on 3/26/14.
//
//

#include "MachineVirtualSubdeviceChannelList.h"

#include "../ProgramParameterLocation.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		namespace
		Machinery
		{













			
			
			
			
			
			auto
			VertexAttributeChannelList::at(const Eonil::Improvisations::MediaEngine::Graphics::Server::ProgramVertexAttributeSlotProxy &slot) const -> local<VertexAttributeChannel const>
			{
				GLint	loc1	=	slot._param_loc._loc;
				EONIL_DEBUG_ASSERT(std::numeric_limits<Size>::max() <= loc1);
				EONIL_DEBUG_ASSERT(loc1 >= 0);
				
				Size	loc2	=	loc1;
				return	MachineVirtualSubdeviceChannelList<VertexAttributeChannel>::at(loc2);
			}
			auto
			VertexAttributeChannelList::at(const Eonil::Improvisations::MediaEngine::Graphics::Server::ProgramVertexAttributeSlotProxy &slot) -> local<VertexAttributeChannel>
			{
				GLint	loc1	=	slot._param_loc._loc;
				EONIL_DEBUG_ASSERT(loc1 <= std::numeric_limits<Size>::max());
				EONIL_DEBUG_ASSERT(loc1 >= 0);
				
				Size	loc2	=	loc1;
				return	MachineVirtualSubdeviceChannelList<VertexAttributeChannel>::at(loc2);
			}




		}
	}

}}}}