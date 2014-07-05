//
//  MachineVirtualSubdeviceChannelList.h
//  Graphics
//
//  Created by Hoon H. on 3/26/14.
//
//

#pragma once
#include "../Declarations.h"
#include "../Buffer.h"
#include "../LEGACY_Legacy2013Compat.h"
#include "../../../Value/StronglyTypingNumericValue.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

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
			
			auto	size() const -> sz;
			auto	at(sz const& index) const -> local<T const>;
			auto	at(sz const& index) -> local<T>;
		};
		
		template <typename T>
		MachineVirtualSubdeviceChannelList<T>::
		MachineVirtualSubdeviceChannelList(Machine* machine) : _machine(machine)
		{
		}
		
		template <typename T>
		auto
		MachineVirtualSubdeviceChannelList<T>::
		at(sz const& index) const -> local<T const>
		{
			return	{T(_machine, index)};
		}
		
		template <typename T>
		auto
		MachineVirtualSubdeviceChannelList<T>::
		at(sz const& index) -> local<T>
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

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END

