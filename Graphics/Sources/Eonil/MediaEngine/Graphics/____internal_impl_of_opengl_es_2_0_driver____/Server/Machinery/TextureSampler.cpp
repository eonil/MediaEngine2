//
//  TextureSampler.cpp
//  EonilGraphics
//
//  Created by Eonil on 5/1/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "TextureSampler.h"
#include "../../Stub/GL.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

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
		setTexture(Texture2D const& texture) -> void
		{
			if (USE_DEBUGGING_ASSERTIONS)
			{
				_dbg_cur_tex_ptr = ptr<Texture2D const>(&texture);
				err9_converted_legacy_assertion(texture.name() != 0, "Bad texture name. The texture is invalid.");
			}
			
			////
			
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
			
			if (USE_DEBUGGING_ASSERTIONS)
			{
				_dbg_cur_tex_ptr = nullptr;
			}
		}
		
	}
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END






