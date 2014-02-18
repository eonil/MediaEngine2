//
//  TextureSampler.h
//  EonilGraphics
//
//  Created by Eonil on 5/1/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__TextureSampler__
#define __EonilGraphics__TextureSampler__

#include "../../Common.h"
#include "../Texture.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		namespace
		Machinery
		{
			/*!
			 Abstraction of GL texture unit.
			 
			 @classdesign
			 This manages a texture bingind to a texture sampler.
			 This uses the specified texture object, but doesn't keep it alive, so you're
			 responsible to keep the texture object. Anyway, this supports shared ownership
			 debugging helper, so premature deallocation of resource will be notified to 
			 users.
			 */
			class
			TextureSampler
			{
				GLenum 					_idx;
				
			public:
				TextureSampler() = delete;					//!	Parameter-less construction prohibited. You must set an sampler index.
				TextureSampler(GLenum const index);			//!	@param	index	An index to a texture-sampler unit in GL interface.
				
				GLenum const			index() const;
				
//				auto	texture() const -> PlanarTexture const&;
				auto	setTexture(PlanarTexture const& texture) -> void;
				auto	unsetTexture() -> void;

				
				
				
				
			public:

				EONIL_MEDIA_ENGINE_DEBUG_ONLY_INLINE_FIELD(ptr<PlanarTexture const>, _dbg_cur_tex_ptr{nullptr});
			};
		}
	}
	

	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics__TextureSampler__) */
