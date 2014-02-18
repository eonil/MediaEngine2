//
//  GL-Get.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "GL-Get.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Stub
	{
		using namespace Eonil::Improvisations::MediaEngine::Graphics::Debugging;
		
		EEGL_INLINE void
		eeglGetBooleanv(GLenum const pname, GLboolean * const params)
		{
			glGetBooleanv(pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglGetFloatv(GLenum const pname, GLfloat * const params)
		{
			glGetFloatv(pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglGetIntegerv(GLenum const pname, GLint * const params)
		{
			glGetIntegerv(pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		
		EEGL_INLINE GLboolean const
		eeglGetBoolean(GLenum const pname)
		{
			GLboolean	value;
			eeglGetBooleanv(pname, &value);
			return		value;
		}
		
		EEGL_INLINE GLboolean const
		eeglGetFloat(GLenum const pname)
		{
			GLfloat		value;
			eeglGetFloatv(pname, &value);
			return		value;
		}
		
		EEGL_INLINE GLint const
		eeglGetInteger(GLenum const pname)
		{
			GLint		value;
			eeglGetIntegerv(pname, &value);
			return		value;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		EEGL_INLINE void
		eeglGetFramebufferAttachmentParameteriv(GLenum const target, GLenum const attachment, GLenum const pname, GLint* const params)
		{
			EEGL_ASSERT(target == GL_FRAMEBUFFER);
			EEGL_ASSERT(attachment == GL_COLOR_ATTACHMENT0 or
									 attachment == GL_DEPTH_ATTACHMENT or
									 attachment == GL_STENCIL_ATTACHMENT);
			EEGL_ASSERT(pname == GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE or
									 pname == GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME or
									 pname == GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL or
									 pname == GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE);
			
//#if not EEGL_IGNORE_ZERO_FRAMEBUFFER_NAME
			EEGL_ASSERT(eeglGetInteger(GL_FRAMEBUFFER_BINDING) != 0);
//#endif
			
			glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_INLINE GLint const
		eeglGetFramebufferAttachmentParameteri(GLenum const target, GLenum const attachment, GLenum const pname)
		{
			GLint	v;
			eeglGetFramebufferAttachmentParameteriv(target, attachment, pname, &v);
			return	v;
		}


		
		EEGL_INLINE void
		eeglGetRenderbufferParameteriv(GLenum const target, GLenum const pname, GLint* const params)
		{
			EEGL_ASSERT(target == GL_RENDERBUFFER);
			EEGL_ASSERT(pname == GL_RENDERBUFFER_WIDTH or
									 pname == GL_RENDERBUFFER_HEIGHT or
									 pname == GL_RENDERBUFFER_INTERNAL_FORMAT or
									 pname == GL_RENDERBUFFER_RED_SIZE or
									 pname == GL_RENDERBUFFER_GREEN_SIZE or
									 pname == GL_RENDERBUFFER_BLUE_SIZE or
									 pname == GL_RENDERBUFFER_ALPHA_SIZE or
									 pname == GL_RENDERBUFFER_DEPTH_SIZE or
									 pname == GL_RENDERBUFFER_STENCIL_SIZE);
			
			glGetRenderbufferParameteriv(target, pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE GLint const
		eeglGetRenderbufferParameteri(GLenum const target, GLenum const pname)
		{
			GLint	v;
			eeglGetRenderbufferParameteriv(target, pname, &v);
			return	v;
		}
	}
	
}}}}




