//
//  VertexLayoutDescriptor.cpp
//  Graphics
//
//  Created by Hoon H. on 2/26/14.
//
//

#include "VertexLayoutDescriptor.h"

#include "../../Stub/GL-Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		namespace
		Utility
		{
			
			
			
			
			
			
			auto VertexLayoutDescriptor::
			channelComponents() const -> vec<ChannelComponent> const&
			{
				return	_ch_comps;
			}
			
			auto VertexLayoutDescriptor::
			strideSize() const -> Size
			{
				return	_stride_size_in_bytes;
			}
			
//			auto VertexLayoutDescriptor::
//			appendScalarVectorChannel(Size const& scalarComponentCount) -> void
//			{
//				EONIL_DEBUG_ASSERT(scalarComponentCount <= 4);
//				
//				ChannelComponent	cc{};
//				cc.type		=	ComponentType::FLOAT;
//				cc.count	=	scalarComponentCount;
//				cc.offset	=	_stride_size_in_bytes;
//				_ch_comps.push_back(cc);
//				_stride_size_in_bytes	+=	sizeof(Scalar) * scalarComponentCount;
//			}
			auto VertexLayoutDescriptor::
			appendScalarVectorChannel(str const& name, Size const& scalarComponentCount) -> void
			{
				EONIL_DEBUG_ASSERT(scalarComponentCount <= 4);
				
				ChannelComponent	cc{};
				cc.name		=	name;
				cc.type		=	ComponentType::FLOAT;
				cc.count	=	scalarComponentCount;
				cc.offset	=	_stride_size_in_bytes;
				_ch_comps.push_back(cc);
				_stride_size_in_bytes	+=	sizeof(Scalar) * scalarComponentCount;
			}

			
			
			
			
			
		}
	}
	
}}}}
