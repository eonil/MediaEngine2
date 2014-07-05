//
//  State.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/3/13.
//
//

#ifndef __EonilGraphics__State__
#define __EonilGraphics__State__

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
	
	/*!
	 Abstracts various graphics rendering state.
	 */
	struct
	State
	{
		struct
		Depth
		{
			bool	performTest;
			int		functionCode;
		};
		struct
		Stencil
		{
			bool	performTest;
			int		functionCode;
		};
		struct
		Blending
		{
			bool	performTest;
			int		functionCode;
		};
		
		Depth		depth;
		Stencil		stencil;
		Blending	blending;
	};
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics__State__) */
