//
//  VertexLayoutDescriptor.h
//  Graphics
//
//  Created by Hoon H. on 2/26/14.
//
//

#pragma once
#include "../Machinery/VertexAttributeChannel.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Server
{
	namespace
	Utility
	{
		
		
		
		/*!
		 This is designed to make configuring vertex attribute channeling easier.
		 This is just a passive information set, but has full description for vertex 
		 layout and name of each components. Then you can configure all required program 
		 vertex attribution parameters only with this object.
		 */
		class
		VertexLayoutDescriptor
		{
		public:
			using	ComponentType	=	Machinery::VertexAttributeChannel::ComponentType;
			
			struct
			ChannelComponent
			{
				str				name	{};								//	Being empty is invalid. A component must have a name.
				ComponentType	type	{ComponentType::FLOAT};
				sz			count	{0};
				sz			offset	{0};							//	In bytes.
			};
			
			
			
		public:
			auto	channelComponents() const -> vec<ChannelComponent> const&;
			auto	strideSize() const -> sz;
			
//				auto	appendScalarVectorChannel(Size const& scalarComponentCount) -> void;
			auto	appendScalarVectorChannel(str const& name, sz const& scalarComponentCount) -> void;
			
			
			
			
			
		private:
			vec<ChannelComponent>	_ch_comps				{};
			sz						_stride_size_in_bytes	{0};
		};
		
		
		
		
		
		
		
		
	}
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END

