//
//  MachineVirtualSubdeviceChannelList.h
//  Graphics
//
//  Created by Hoon H. on 3/26/14.
//
//

#ifndef __Graphics__MachineVirtualSubdeviceChannelList__
#define __Graphics__MachineVirtualSubdeviceChannelList__


#include "../../Common.h"
#include "../Declarations.h"
#include "../Buffer.h"
#include "../_Legacy2013Compat.h"
#include "../../Value/StronglyTypingNumericValue.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		namespace
		Machinery
		{
			/*!
			 A virtual channel list.
			 This is more close to a generator in a form of list.
			 */
			template <typename T>
			class
			MachineVirtualSubdeviceChannelList
			{
				Machine*	_machine	{nullptr};
				
			public:
				MachineVirtualSubdeviceChannelList(Machine* machine);
				
				auto	size() const -> Size;
				auto	at(Size const& index) const -> local<T const>;
				auto	at(Size const& index) -> local<T>;
			};
			
			template <typename T>
			MachineVirtualSubdeviceChannelList<T>::
			MachineVirtualSubdeviceChannelList(Machine* machine) : _machine(machine)
			{
			}
			
			template <typename T>
			auto
			MachineVirtualSubdeviceChannelList<T>::
			at(Size const& index) const -> local<T const>
			{
				return	{T(_machine, index)};
			}
			
			template <typename T>
			auto
			MachineVirtualSubdeviceChannelList<T>::
			at(Size const& index) -> local<T>
			{
				return	{T(_machine, index)};
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			class
			VertexAttributeChannelList : public MachineVirtualSubdeviceChannelList<VertexAttributeChannel>
			{
			public:
				using	MachineVirtualSubdeviceChannelList<VertexAttributeChannel>::MachineVirtualSubdeviceChannelList;
					
				auto	at(ProgramVertexAttributeSlotProxy const& slot) const -> local<VertexAttributeChannel const>;		//!	This is O(1) operation.
				auto	at(ProgramVertexAttributeSlotProxy const& slot) -> local<VertexAttributeChannel>;					//!	This is O(1) operation.
			};
			
			
			
			
//			class
//			IndexUnitChannelList : public MachineVirtualSubdeviceChannelList<IndexUnitChannel>
//			{
//			public:
//				using	MachineVirtualSubdeviceChannelList<VertexAttributeChannel>::MachineVirtualSubdeviceChannelList;
//			};
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__MachineVirtualSubdeviceChannelList__) */
