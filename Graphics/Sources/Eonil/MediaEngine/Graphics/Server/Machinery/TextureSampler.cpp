//
//  TextureSampler.cpp
//  EonilGraphics
//
//  Created by Eonil on 5/1/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "TextureSampler.h"

#include "../../Stub/GL.h"


namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		namespace
		Machinery
		{
			using namespace Stub;
			
			TextureSampler::TextureSampler(GLenum const index) : _idx(index)
			{
			}
			
			
			GLenum const
			TextureSampler::index() const
			{
				return	_idx;
			}
						

			
			
			
			
			
			auto TextureSampler::
			setTexture(PlanarTexture const& texture) -> void
			{
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(_dbg_cur_tex_ptr = ptr<PlanarTexture const>(&texture));
				EEGL_ASSERT_WITH_REASON(texture.name() != 0, "Bad texture name. The texture is invalid.");
				
				eeglActiveTexture(GL_TEXTURE0 + _idx);
				eeglBindTexture(GL_TEXTURE_2D, texture.name());
			}
			auto TextureSampler::
			unsetTexture() -> void
			{
				/*
				 Texture sampler should be cleared if specified to be cleared.
				 */
				eeglActiveTexture(GL_TEXTURE0 + _idx);
				eeglUnbindTexture(GL_TEXTURE_2D);
				
				EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(_dbg_cur_tex_ptr = nullptr);
			}
			
		}
	}
	
	
	
	
}}}}






