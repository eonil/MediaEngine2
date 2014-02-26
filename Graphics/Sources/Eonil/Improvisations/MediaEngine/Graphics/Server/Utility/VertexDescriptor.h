//
//  VertexDescriptor.h
//  Graphics
//
//  Created by Hoon H. on 2/19/14.
//
//

#ifndef __Graphics__VertexDescriptor__
#define __Graphics__VertexDescriptor__

#include "../Machinery/VertexAttributeChannel.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		namespace
		Utility
		{
			
			
			
			
			class
			VertexDescriptor
			{
			public:
				using	ComponentType	=	Machinery::VertexAttributeChannel::ComponentType;
				
				struct
				ChannelComponent
				{
					ComponentType	type	{ComponentType::FLOAT};
					Size			count	{0};
	//				Size			size	{0};	//	In bytes.
					Size			offset	{0};	//	In bytes.
				};
				
				
				
			public:
				auto	channelComponents() const -> vec<ChannelComponent> const&;
				auto	strideSize() const -> Size;
				
				auto	appendScalarVectorChannel(Size const& scalarComponentCount) -> void;
				
				
				
				
				
			private:
				vec<ChannelComponent>	_ch_comps				{};
				Size					_stride_size_in_bytes	{0};
			};
			
			
			
			
		
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__VertexDescriptor__) */
