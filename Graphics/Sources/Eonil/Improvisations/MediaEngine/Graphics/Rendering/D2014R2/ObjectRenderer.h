//
//  ObjectRenderer.h
//  Graphics
//
//  Created by Hoon H. on 2/18/14.
//
//

#ifndef __Graphics__ObjectRenderer__
#define __Graphics__ObjectRenderer__

#include "../../Common.h"
#include "../../Server/Declarations.h"
#include "Scene.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{
			
			
			/*!
			 This performs alpha blending of multiple rendering-frame images.
			 
			 @discussion
			 This is different with object-level alpha-blending, and almost purely
			 pixel operation.
			 
			 The channels are not always required and can be missing by configuration.
			 Any trial to access missing channel will throw an exception.
			 */
			class
			ObjectRenderer final
			{
				uptr<Server::Framebuffer>		_image		{};
				
			public:
				ObjectRenderer();
				~ObjectRenderer();
				
			public:
				ObjectRenderer(Server::Framebuffer const& imageFrame);

				auto	imageFrame() const -> Server::Framebuffer const&;
				
				auto	render(Scene const& scene) -> void;
			};
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__ObjectRenderer__) */
