//
//  GL-Renderbuffer.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/1/13.
//
//

#include "GL-Renderbuffer.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Stub
	{
		using namespace Eonil::Improvisations::MediaEngine::Graphics::Debugging;
		
		
		
		EEGL_STUB_API_DECO void
		eeglGenRenderbuffers(GLsizei const n, GLuint* const renderbuffers)
		{
			glGenRenderbuffers(n, renderbuffers);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_STUB_API_DECO void
		eeglDeleteRenderbuffers(GLsizei const n, GLuint const* const renderbuffers)
		{
			glDeleteRenderbuffers(n, renderbuffers);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_STUB_API_DECO GLuint const
		eeglGenRenderbuffer()
		{
			GLuint	n;
			eeglGenRenderbuffers(1, &n);
			return	n;
		}
		EEGL_STUB_API_DECO void
		eeglDeleteRenderbuffer(GLuint const renderbuffer)
		{
			eeglDeleteRenderbuffers(1, &renderbuffer);
		}
		
		
		
		
		
		EEGL_STUB_API_DECO void
		eeglBindRenderbuffer(GLenum const target, GLuint const renderbuffer)
		{
			EEGL_ASSERT(target == GL_RENDERBUFFER);
#if not EEGL_IGNORE_ZERO_RENDERBUFFER_NAME
			EEGL_ASSERT(renderbuffer != 0);
#endif
			glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_STUB_API_DECO void
		eeglUnbindRenderbuffer(GLenum const target)
		{
			EEGL_ASSERT(target == GL_RENDERBUFFER);

			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		
		
		
		
		
		EEGL_STUB_API_DECO void
		eeglRenderbufferStorage(GLenum const target, GLenum const internalformat, GLsizei const width, GLsizei const height)
		{
			EEGL_ASSERT(target == GL_RENDERBUFFER);
			EEGL_ASSERT(internalformat == GL_RGBA4 or
									 internalformat == GL_RGB565 or
									 internalformat == GL_RGB5_A1 or
									 internalformat == GL_DEPTH_COMPONENT16 or
									 internalformat == GL_STENCIL_INDEX8);
			
			EEGL_ASSERT(width > 0);		//	Extra check. Not by spec.
			EEGL_ASSERT(height > 0);		//	Extra check. Not by spec.
			
			glRenderbufferStorage(target, internalformat, width, height);
			EEGL_ASSERT_NO_GL_ERROR();
		}

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		EEGL_STUB_API_DECO GLboolean const
		eeglIsRenderbuffer(GLuint const renderbuffer)
		{
			GLboolean const	r	=	glIsRenderbuffer(renderbuffer);
			EEGL_ASSERT_NO_GL_ERROR();
			return	r;
		}
	}
	
	
	
}}}}

