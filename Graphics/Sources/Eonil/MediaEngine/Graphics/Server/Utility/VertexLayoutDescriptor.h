//
//  VertexLayoutDescriptor.h
//  Graphics
//
//  Created by Hoon H. on 2/26/14.
//
//

#ifndef __Graphics__VertexLayoutDescriptor__
#define __Graphics__VertexLayoutDescriptor__

#include "../Machinery/VertexAttributeChannel.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
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
					Size			count	{0};
					Size			offset	{0};							//	In bytes.
				};
				
				
				
			public:
				auto	channelComponents() const -> vec<ChannelComponent> const&;
				auto	strideSize() const -> Size;
				
//				auto	appendScalarVectorChannel(Size const& scalarComponentCount) -> void;
				auto	appendScalarVectorChannel(str const& name, Size const& scalarComponentCount) -> void;
				
				
				
				
				
			private:
				vec<ChannelComponent>	_ch_comps				{};
				Size					_stride_size_in_bytes	{0};
			};
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__VertexLayoutDescriptor__) */
