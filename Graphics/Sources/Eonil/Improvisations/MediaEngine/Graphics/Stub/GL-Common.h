//
//  GL-Common.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/28/13.
//
//

#ifndef __EonilGraphics__GL_Common__
#define __EonilGraphics__GL_Common__


/*!
 The issue about Apportable known to been fixed by the developers.
 Anyway it is not yet confirmed, so the code is kept by commentizing.
 */
///*!
// Apportable had insane update at 1.0.15 which returns `0` for valid 
// framebuffer/renderbuffer name. This disrupts all assertion system.
// 
// As a workaround, I had to put this flag not to perform related 
// assertions under Apportable environment. Remove these flags and get
// back related assertions if Apportable removes the insane behavior.
// */
//#if		EONIL_MEDIA_ENGINE_TARGET_APPORTABLE
//#define	EEGL_IGNORE_ZERO_FRAMEBUFFER_NAME	1
//#define	EEGL_IGNORE_ZERO_RENDERBUFFER_NAME	1
//#else
//#define	EEGL_IGNORE_ZERO_FRAMEBUFFER_NAME	0
//#define	EEGL_IGNORE_ZERO_RENDERBUFFER_NAME	0
//#endif

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Stub
	{
		
		/*
		 These are primitive type conversion (cast) operations.
		 Why do we need this? To be notified on bad(overflow, underflow...)
		 operations.
		 */
		auto	toGL(Size const& v) -> GLsizei;
		auto	fromGL(GLsizei const& v) -> Size;
		
		
		
		
		
	}
	
}}}}

#endif /* defined(__EonilGraphics__GL_Common__) */
