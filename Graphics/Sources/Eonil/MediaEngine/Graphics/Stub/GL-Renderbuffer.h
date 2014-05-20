//
//  GL-Renderbuffer.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/1/13.
//
//

#ifndef __EonilGraphics__GL_Renderbuffer__
#define __EonilGraphics__GL_Renderbuffer__


#include "../Common.h"
#include "GL-Common.h"
#include "../Debugging/Doctor.h"


namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Stub
	{
		using namespace Eonil::Improvisations::MediaEngine::Graphics::Debugging;
		
		EEGL_STUB_API_DECO void			eeglGenRenderbuffers(GLsizei const n, GLuint* const renderbuffers);
		EEGL_STUB_API_DECO void			eeglDeleteRenderbuffers(GLsizei const n, GLuint const* const renderbuffers);
		
		EEGL_STUB_API_DECO GLuint const	eeglGenRenderbuffer();
		EEGL_STUB_API_DECO void			eeglDeleteRenderbuffer(GLuint const renderbuffer);
		
		EEGL_STUB_API_DECO void			eeglBindRenderbuffer(GLenum const target, GLuint const renderbuffer);
		EEGL_STUB_API_DECO void			eeglUnbindRenderbuffer(GLenum const target);
		
		EEGL_STUB_API_DECO void			eeglRenderbufferStorage(GLenum const target, GLenum const internalformat, GLsizei const width, GLsizei const height);
		
		
		
		
		
		
		
		EEGL_STUB_API_DECO GLboolean const	eeglIsRenderbuffer(GLuint const renderbuffer);
		
	}
	
}}}}

#endif /* defined(__EonilGraphics__GL_Renderbuffer__) */





