//
//  GL-Extensions.cpp
//  Graphics
//
//  Created by Hoon H. on 3/26/14.
//
//

#include "GL-Extensions.h"

#include "../Debugging/Doctor.h"
#include "GL-Context.h"
#include "GL-Program.h"
#include "GL-Framebuffer.h"
namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Stub
	{
		using namespace	Debugging;
		
		
		namespace
		ASSERTION
		{
	

		}
		
		

		
		
		
		
		
		
		
		
		
		EEGL_STUB_API_DECO void
		eeglVertexAttribDivisorEXT(GLuint const index, GLuint const divisor)
		{
			{
#if			EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
				glVertexAttribDivisorARB(index, divisor);
#elif		EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
				glVertexAttribDivisorEXT(index, divisor);
#else
#error			EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
#endif
			}
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		EEGL_STUB_API_DECO void
		eeglDrawArraysInstancedEXT(GLenum const mode, int const first, GLsizei const count, GLsizei const instanceCount)
		{
			EEGL_ASSERT((mode == GL_POINTS) or
						(mode == GL_LINE_STRIP) or
						(mode == GL_LINE_LOOP) or
						(mode == GL_LINES) or
						(mode == GL_TRIANGLE_STRIP) or
						(mode == GL_TRIANGLE_FAN) or
						(mode == GL_TRIANGLES));
			
			EEGL_ASSERT(count >= 0);
			
			////
			
			EEGL_ASSERT(eeglCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
			EEGL_ASSERT(eeglIsProgram(eeglGetInteger(GL_CURRENT_PROGRAM)));
			
			if (Doctor::useStateValidation())
			{
				GLint	params[4];
				eeglGetIntegerv(GL_VIEWPORT, params);
				EEGL_ASSERT(params[2] != 0);
				EEGL_ASSERT(params[3] != 0);
			}
			
			////
			
			/*!
			 CRASH NOTE
			 ==========
			 If this function crashes while being executed, it's mostly because of bad vertex data.
			 Regardless of where it is. (client or server) So check the data integrity first.
			 
			 Detection or assertion for the bad data from underlying GL state is very hard and really
			 inefficient. (even for heavy assertion mode!) So I am not currently implementing it.
			 */

			
#if		EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
			glDrawArraysInstanced(mode, first, count, instanceCount);
#elif	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
			glDrawArraysInstancedEXT(mode, first, count, instanceCount);
#else
#error		EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
#endif
			
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_STUB_API_DECO void
		eeglDrawElementsInstancedEXT(GLenum const mode, GLsizei const count, GLenum const type, const GLvoid * const indices, GLsizei const instanceCount)
		{
			EEGL_ASSERT((mode == GL_POINTS) or
						(mode == GL_LINE_STRIP) or
						(mode == GL_LINE_LOOP) or
						(mode == GL_LINES) or
						(mode == GL_TRIANGLE_STRIP) or
						(mode == GL_TRIANGLE_FAN) or
						(mode == GL_TRIANGLES));
			
			EEGL_ASSERT(count >= 0);
			
			EEGL_ASSERT((type == GL_UNSIGNED_BYTE) or
						(type == GL_UNSIGNED_SHORT));
			
			////
			
			EEGL_ASSERT(eeglCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
			EEGL_ASSERT(eeglIsProgram(eeglGetInteger(GL_CURRENT_PROGRAM)));
			
			if (Doctor::useStateValidation())
			{
				GLint	params[4];
				eeglGetIntegerv(GL_VIEWPORT, params);
				EEGL_ASSERT(params[2] != 0);
				EEGL_ASSERT(params[3] != 0);
			}
			
			////
			{
				
				/*!
				 CRASH NOTE
				 ==========
				 If this function crashes while being executed, it's mostly because of bad vertex/index data.
				 Regardless of where it is. (client or server) So check the data integrity first.
				 
				 Detection or assertion for the bad data is very hard and really inefficient. (even for debug
				 build!) So I am not currently implementing it.
				 */
				
#if			EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
				glDrawElementsInstanced(mode, count, type, indices, instanceCount);
#elif		EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
				glDrawElementsInstancedEXT(mode, count, type, indices, instanceCount);
#else
#error		EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
#endif
				
				EEGL_ASSERT_NO_GL_ERROR();
			}
			
		}
		

	
	}
	
}}}}