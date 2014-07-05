//
//  MachineVirtualSubdeviceChannelList.cpp
//  Graphics
//
//  Created by Hoon H. on 3/26/14.
//
//

#include "MachineVirtualSubdeviceChannelList.h"
#include "../ProgramParameterLocation.h"

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Server
{
	namespace
	Machinery
	{













		
		
		
		
		
		auto
		VertexAttributeChannelList::at(const ProgramVertexAttributeSlotProxy &slot) const -> local<VertexAttributeChannel const>
		{
			GLint	loc1	=	slot._param_loc._loc;
			
			////
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion(std::numeric_limits<sz>::max() <= loc1);
				err9_converted_legacy_assertion(loc1 >= 0);
			}
			////
			
			sz		loc2	=	loc1;
			return	MachineVirtualSubdeviceChannelList<VertexAttributeChannel>::at(loc2);
		}
		auto
		VertexAttributeChannelList::at(const ProgramVertexAttributeSlotProxy &slot) -> local<VertexAttributeChannel>
		{
			GLint	loc1	=	slot._param_loc._loc;
			
			////
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion(loc1 <= std::numeric_limits<sz>::max());
				err9_converted_legacy_assertion(loc1 >= 0);
			}
			////
			
			sz	loc2	=	loc1;
			return	MachineVirtualSubdeviceChannelList<VertexAttributeChannel>::at(loc2);
		}




	}
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END
