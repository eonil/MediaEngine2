//
//  iOS.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//


#if	EONIL_MEDIA_ENGINE_TARGET_IOS
#import <OpenGLES/EAGL.h>
#include "iOS.h"
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
	
	namespace
	Platforms
	{

		bool const
		iOS::hasCurrentGLContext()
		{
			return	[EAGLContext currentContext] != nil;
		}

		
		
	}


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END
#endif