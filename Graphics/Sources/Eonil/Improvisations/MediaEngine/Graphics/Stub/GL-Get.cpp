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
		
		
		namespace
		{
			template<typename T>
			static inline auto
			contains_target_in_samples(T const& target, vec<T> const& samples) -> bool
			{
				return	std::find(samples.begin(), samples.end(), target) != samples.end();
			}
		}
		
		
		
		
		
		
		
		
		
		
		
		
		EEGL_STUB_API_DECO void
		eeglGetBooleanv(GLenum const pname, GLboolean * const params)
		{
			glGetBooleanv(pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_STUB_API_DECO void
		eeglGetFloatv(GLenum const pname, GLfloat * const params)
		{
			glGetFloatv(pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_STUB_API_DECO void
		eeglGetIntegerv(GLenum const pname, GLint * const params)
		{
//			GL_INVALID_ENUM	=	0x500;
			glGetIntegerv(pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		
		EEGL_STUB_API_DECO GLboolean const
		eeglGetBoolean(GLenum const pname)
		{
			GLboolean	value;
			eeglGetBooleanv(pname, &value);
			return		value;
		}
		
		EEGL_STUB_API_DECO GLboolean const
		eeglGetFloat(GLenum const pname)
		{
			GLfloat		value;
			eeglGetFloatv(pname, &value);
			return		value;
		}
		
		EEGL_STUB_API_DECO GLint const
		eeglGetInteger(GLenum const pname)
		{
			GLint		value;
			eeglGetIntegerv(pname, &value);
			return		value;
		}
		
		
		/*!
		 Returning strings are all NULL-terminated.
		 */
		EEGL_STUB_API_DECO GLubyte const*
		eeglGetString(GLenum const name)
		{
			EONIL_DEBUG_ASSERT(contains_target_in_samples(name,
			{
				GL_VENDOR,
				GL_RENDERER,
				GL_VERSION,
				GL_SHADING_LANGUAGE_VERSION,
				GL_EXTENSIONS,
			}));
			GLubyte const*	c_str1	=	glGetString(name);
			EEGL_ASSERT_NO_GL_ERROR();
			EONIL_DEBUG_ASSERT(c_str1 != NULL);		//!	Zero means error. @ref https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetString.xml
			return	c_str1;
		}
		
		
		
		
		
		
		
		
		
		
		
		EEGL_STUB_API_DECO void
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
//			EEGL_ASSERT(eeglGetInteger(GL_FRAMEBUFFER_BINDING) != 0);
//#endif
			
			glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_STUB_API_DECO GLint const
		eeglGetFramebufferAttachmentParameteri(GLenum const target, GLenum const attachment, GLenum const pname)
		{
			GLint	v;
			eeglGetFramebufferAttachmentParameteriv(target, attachment, pname, &v);
			return	v;
		}


		
		EEGL_STUB_API_DECO void
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
		EEGL_STUB_API_DECO GLint const
		eeglGetRenderbufferParameteri(GLenum const target, GLenum const pname)
		{
			GLint	v;
			eeglGetRenderbufferParameteriv(target, pname, &v);
			return	v;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		EEGL_STUB_API_DECO bool
		eeglGetVendorIsATI()
		{
			GLubyte const*	bytes1	=	eeglGetString(GL_VENDOR);
			char const*		bytes2	=	(char const*)bytes1;
			str				s3		=	str(bytes2, 3);				//	The vendor string may contain extra characters. Especially ATI have several variants, and checking only first three characters will be better.
			return	s3 == "ATI";
		}
	}
	
}}}}




