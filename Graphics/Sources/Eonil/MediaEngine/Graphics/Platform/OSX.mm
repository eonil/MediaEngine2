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
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

namespace
Platforms
{
	
	bool 
	OSX::hasCurrentGLContext()
	{
		return	[NSOpenGLContext currentContext] != nil;
	}
	
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END

