//
//  ProgramVertexChannelingDescriptor.cpp
//  Graphics
//
//  Created by Hoon H. on 2/26/14.
//
//

#include "ProgramVertexChannelingDescriptor.h"
#include "../Program.h"
#include "../ProgramParameterLocation.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		namespace
		Utility
		{
			ProgramVertexChannelingDescriptor::ProgramVertexChannelingDescriptor()
			{
			}
			
			ProgramVertexChannelingDescriptor::ProgramVertexChannelingDescriptor(vec<Size> const& allChannelIndexes) : _chidxs(allChannelIndexes)
			{
			}
			
			
			
			auto ProgramVertexChannelingDescriptor::
			channelIndexForComponentIndex(Size const& componentIndex) const -> Size
			{
				return	_chidxs.at(componentIndex);
			}
			
			auto ProgramVertexChannelingDescriptor::
			allChannelIndexes() const -> vec<Size> const&
			{
				return	_chidxs;
			}
			
			
			
			auto ProgramVertexChannelingDescriptor::
			analyze(const Eonil::Improvisations::MediaEngine::Graphics::Server::Utility::VertexLayoutDescriptor &layout, const Eonil::Improvisations::MediaEngine::Graphics::Server::Program &program) -> ProgramVertexChannelingDescriptor
			{
				vec<Size>	chidxs{};
				
				for (Size i=0; i<layout.channelComponents().size(); i++)
				{
//					EONIL_DEBUG_ASSERT(not layout.channelComponents().at(i).name.empty());
					
					auto const&	comp	=	layout.channelComponents().at(i);
					Size		ch_idx	=	program.indexOfVertexAttributeSlotV1ForName(comp.name);
//					Size		ch_idx	=	program.vertexAttributeSlotForName(comp.name);
					chidxs.push_back(ch_idx);
				}
				
				return	{chidxs};
			}
			
			
			
			
			
		}
	}
	
}}}}

