//
//  iOS.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//


#if	EONIL_MEDIA_ENGINE_TARGET_IOS

#include "iOS.h"

#import <OpenGLES/EAGL.h>

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Platforms
	{

		bool const
		iOS::hasCurrentGLContext()
		{
			return	[EAGLContext currentContext] != nil;
		}

		
		
	}


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}}}}

#endif