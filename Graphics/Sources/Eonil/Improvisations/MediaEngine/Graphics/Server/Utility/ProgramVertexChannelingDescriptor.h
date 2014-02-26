//
//  ProgramVertexChannelingDescriptor.h
//  Graphics
//
//  Created by Hoon H. on 2/26/14.
//
//

#ifndef __Graphics__ProgramVertexChannelingDescriptor__
#define __Graphics__ProgramVertexChannelingDescriptor__

#include "VertexLayoutDescriptor.h"

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
				
				ProgramVertexChannelingDescriptor(vec<Size> const& allChannelIndexes);
				
			public:
				ProgramVertexChannelingDescriptor();
				
				auto	channelIndexForComponentIndex(Size const& componentIndex) const -> Size;
				auto	allChannelIndexes() const -> vec<Size> const&;
				
			public:
				static auto	analyze(VertexLayoutDescriptor const& layout, Program const& program) -> ProgramVertexChannelingDescriptor;
			};
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__ProgramVertexChannelingDescriptor__) */
