//
//  GL-Get.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__GL_Get__
#define __EonilGraphics__GL_Get__

#include "../Common.h"
#include "../Debugging/Doctor.h"
#include "GL-Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Stub
	{
		using namespace Eonil::Improvisations::MediaEngine::Graphics::Debugging;
		
		EEGL_STUB_API_DECO void			eeglGetBooleanv(GLenum const pname, GLboolean * const params);
		EEGL_STUB_API_DECO void			eeglGetFloatv(GLenum const pname, GLfloat * const params);
		EEGL_STUB_API_DECO void			eeglGetIntegerv(GLenum const pname, GLint * const params);
		
		EEGL_STUB_API_DECO GLboolean const			eeglGetBoolean(GLenum const pname);
		EEGL_STUB_API_DECO GLboolean const			eeglGetFloat(GLenum const pname);
		EEGL_STUB_API_DECO GLint const				eeglGetInteger(GLenum const pname);
		
		
		
		
		EEGL_STUB_API_DECO void					eeglGetFramebufferAttachmentParameteriv(GLenum const target, GLenum const attachment, GLenum const pname, GLint* const params);
		EEGL_STUB_API_DECO GLint const			eeglGetFramebufferAttachmentParameteri(GLenum const target, GLenum const attachment, GLenum const pname);
		
		EEGL_STUB_API_DECO void					eeglGetRenderbufferParameteriv(GLenum const target, GLenum const pname, GLint* const params);
		EEGL_STUB_API_DECO GLint const			eeglGetRenderbufferParameteri(GLenum const target, GLenum const pname);
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		

		
		
		
		
	}
	
}}}}

#endif /* defined(__EonilGraphics__GL_Get__) */
