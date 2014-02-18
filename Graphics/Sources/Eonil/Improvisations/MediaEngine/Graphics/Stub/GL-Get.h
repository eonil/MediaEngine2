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
		
		EEGL_INLINE void			eeglGetBooleanv(GLenum const pname, GLboolean * const params);
		EEGL_INLINE void			eeglGetFloatv(GLenum const pname, GLfloat * const params);
		EEGL_INLINE void			eeglGetIntegerv(GLenum const pname, GLint * const params);
		
		EEGL_INLINE GLboolean const			eeglGetBoolean(GLenum const pname);
		EEGL_INLINE GLboolean const			eeglGetFloat(GLenum const pname);
		EEGL_INLINE GLint const				eeglGetInteger(GLenum const pname);
		
		
		
		
		EEGL_INLINE void					eeglGetFramebufferAttachmentParameteriv(GLenum const target, GLenum const attachment, GLenum const pname, GLint* const params);
		EEGL_INLINE GLint const				eeglGetFramebufferAttachmentParameteri(GLenum const target, GLenum const attachment, GLenum const pname);
		
		EEGL_INLINE void					eeglGetRenderbufferParameteriv(GLenum const target, GLenum const pname, GLint* const params);
		EEGL_INLINE GLint const				eeglGetRenderbufferParameteri(GLenum const target, GLenum const pname);
	}
	
}}}}

#endif /* defined(__EonilGraphics__GL_Get__) */
