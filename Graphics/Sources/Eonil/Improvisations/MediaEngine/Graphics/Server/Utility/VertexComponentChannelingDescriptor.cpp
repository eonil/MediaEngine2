//
//  VertexComponentChannelingDescriptor.cpp
//  Graphics
//
//  Created by Hoon H. on 3/27/14.
//
//

#include "VertexComponentChannelingDescriptor.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
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
				
				for (Size i=0; i<layout.channelComponents().size(); i++)
				{
					EONIL_DEBUG_ASSERT(not layout.channelComponents().at(i).name.empty());
					
					auto const&		comp	=	layout.channelComponents().at(i);
					PROGRAM_SLOT	ch_slot	=	program.vertexAttributeSlotForName(comp.name);
					ch_slots.push_back(ch_slot);
				}
				
				return	{layout, ch_slots};
			}
			













		}
	}

}}}}