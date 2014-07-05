//
//  Renderer.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__Renderer__
#define __EonilGraphics__Renderer__

#include "Scene.h"
#include "../Resource/Model.h"

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
	
	/*!
	 A renderer just performs single frame rendering.
	 
	 Model Resource Transferring
	 ---------------------------
	 Model resources need to be transferred to graphics server to be rendered.
	 Renderer will transfer resources when it needs them automatically. Anyway this
	 is temporary load, so it will be removed after rendering.
	 
	 If you want to keep those resources on graphics server, you should load them
	 explicitly. Also, this will enable preloading/postunloading of resources.
	 
	 This is implemented with reference counting. Renderer will hold reference to
	 preloaded resources, and will give up the ownership when you explicitly command
	 to unload them.
	 
	 
	 */
	class
	Renderer
	{
	public:
		static Renderer&	renderer();
		
	public:
		Renderer();
		~Renderer();
		
		void				clearFrame(Vector4 const color);
		void				render(Scene const scnee);							//	Render to final display. Output is dispatch and fotget. No way to get back the final output.
		
		void				preloadResourcesForModel(Model const& model);
		void				postunloadResourcesForModel(Model const& model);
	};
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics__Renderer__) */










