//
//  VertexComponentChannelingDescriptor.cpp
//  Graphics
//
//  Created by Hoon H. on 3/27/14.
//
//

#include "VertexComponentChannelingDescriptor.h"

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Server
{
	namespace
	Utility
	{
		
		
		
		
		
		VertexComponentChannelingDescriptor::VertexComponentChannelingDescriptor(VertexLayoutDescriptor const& sourceComponentLayout, vec<PROGRAM_SLOT> const& destinationSlots)
		:	_source_layout(sourceComponentLayout)
		,	_destination_slots(destinationSlots)
		{
		}
		
		auto
		VertexComponentChannelingDescriptor::
		sourceComponentLayout() const -> VertexLayoutDescriptor const&
		{
			return	_source_layout;
		}
		auto
		VertexComponentChannelingDescriptor::
		destinationSlots() const -> vec<PROGRAM_SLOT> const&
		{
			return	_destination_slots;
		}
		
		auto
		VertexComponentChannelingDescriptor::
		analyze(VertexLayoutDescriptor const& layout, Program& program) -> VertexComponentChannelingDescriptor
		{
			vec<PROGRAM_SLOT>	ch_slots{};
			
			for (sz i=0; i<layout.channelComponents().size(); i++)
			{
				if (USE_DEBUGGING_ASSERTIONS)
				{
					err9_converted_legacy_assertion(not layout.channelComponents().at(i).name.empty());
				}
				
				////
				
				auto const&		comp	=	layout.channelComponents().at(i);
				PROGRAM_SLOT	ch_slot	=	program.vertexAttributeSlotForName(comp.name);
				ch_slots.push_back(ch_slot);
			}
			
			return	{layout, ch_slots};
		}
		













	}
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END
