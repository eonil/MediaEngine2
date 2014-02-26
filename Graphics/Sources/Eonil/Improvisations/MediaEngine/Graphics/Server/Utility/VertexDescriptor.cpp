//
//  VertexDescriptor.cpp
//  Graphics
//
//  Created by Hoon H. on 2/19/14.
//
//

#include "VertexDescriptor.h"

#include "../../Stub/GL-Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		namespace
		Utility
		{
		

			
			
			
			
			auto VertexDescriptor::
			channelComponents() const -> vec<ChannelComponent> const&
			{
				return	_ch_comps;
			}
			
			auto VertexDescriptor::
			strideSize() const -> Size
			{
				return	_stride_size_in_bytes;
			}
			
			auto VertexDescriptor::
			appendScalarVectorChannel(Size const& scalarComponentCount) -> void
			{
				EONIL_DEBUG_ASSERT(scalarComponentCount <= 4);
				
				ChannelComponent	cc{};
				cc.type		=	ComponentType::FLOAT;
				cc.count	=	scalarComponentCount;
				cc.offset	=	_stride_size_in_bytes;
				_ch_comps.push_back(cc);
				_stride_size_in_bytes	+=	sizeof(Scalar) * scalarComponentCount;
			}
					
			
			
			
		

		}
	}
	
}}}}
