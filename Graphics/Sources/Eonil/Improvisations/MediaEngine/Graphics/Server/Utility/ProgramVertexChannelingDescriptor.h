//
//  ProgramVertexChannelingDescriptor.h
//  Graphics
//
//  Created by Hoon H. on 2/26/14.
//
//

#ifndef __Graphics__ProgramVertexChannelingDescriptor__
#define __Graphics__ProgramVertexChannelingDescriptor__

#include "../../Common.h"
#include "VertexLayoutDescriptor.h"

#include "../ProgramParameterLocation.h"		//	I don't know why the compiler wants definition of `VertexAttributeSlot`...

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		namespace
		Utility
		{
			/*!
			 Maps component -> channel by thier indexes.
			 */
			class
			ProgramVertexChannelingDescriptor
			{
				vec<Size>		_chidxs	{};
				
				[[deprecated]]
				ProgramVertexChannelingDescriptor(vec<Size> const& allChannelIndexes);
				
			public:
				[[deprecated]]
				ProgramVertexChannelingDescriptor();
				
				[[deprecated]]
				auto	channelIndexForComponentIndex(Size const& componentIndex) const -> Size;
				auto	allChannelIndexes() const -> vec<Size> const&;
				
			public:
				[[deprecated]]
				static auto	analyze(VertexLayoutDescriptor const& layout, Program const& program) -> ProgramVertexChannelingDescriptor;
			};
			

			
			
			
			
			/*!
			 Maps component -> vertex channel slot
			 */
			class
			ProgramVertexChannelingDescriptor2
			{
				using	SLOT	=	local<VertexAttributeSlot>;
				
				vec<SLOT>		_ch_slots;
				
				ProgramVertexChannelingDescriptor2(vec<SLOT> const& allChannelSlots);
				
			public:
				ProgramVertexChannelingDescriptor2();
				
				auto	channelSlotForComponentIndex(Size const& componentIndex) const -> SLOT;
				auto	allChannelSlots() const -> vec<SLOT> const&;
				
			public:
				static auto	analyze(VertexLayoutDescriptor const& layout, Program& program) -> ProgramVertexChannelingDescriptor2;
			};
			

			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__ProgramVertexChannelingDescriptor__) */
