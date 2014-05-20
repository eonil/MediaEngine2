//
//  OSX.cpp
//  EonilGraphics
//
//  Created by Eonil on 7/28/13.
//
//

#include "OSX.h"

#import <OpenGL/OpenGL.h>
#import <AppKit/AppKit.h>

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Platforms
	{
		
		bool 
		OSX::hasCurrentGLContext()
		{
			return	[NSOpenGLContext currentContext] != nil;
		}
		
	}
	
}}}}
