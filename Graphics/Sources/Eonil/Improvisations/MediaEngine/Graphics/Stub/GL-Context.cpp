//
//  GL-Context.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "GL-Context.h"




namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Stub
	{
		
		
		
		
		EEGL_INLINE void
		eeglViewport(GLint const x, GLint const y, GLsizei const width, GLsizei const height)
		{
			EEGL_ASSERT(x >= 0);
			EEGL_ASSERT(y >= 0);
			EEGL_ASSERT(width >= 0);
			EEGL_ASSERT(height >= 0);
			if (Doctor::useStateValidation())
			{
				GLint	params[2];
				eeglGetIntegerv(GL_MAX_VIEWPORT_DIMS, params);
				EEGL_ASSERT(x <= params[0]);
				EEGL_ASSERT(y <= params[1]);
				EEGL_ASSERT(width <= params[0]);
				EEGL_ASSERT(height <= params[1]);
			}
			
			glViewport(x, y, width, height);
			EEGL_ASSERT_NO_GL_ERROR();
		}

		EEGL_INLINE void
		eeglScissor(GLint const x, GLint const y, GLsizei const width, GLsizei const height)
		{
			EEGL_ASSERT(x >= 0);
			EEGL_ASSERT(y >= 0);
			EEGL_ASSERT(width >= 0);
			EEGL_ASSERT(height >= 0);
			if (Doctor::useStateValidation())
			{
				GLint	params[4];
				eeglGetIntegerv(GL_VIEWPORT, params);		//	Scissor box must be within the current viewport.
				EEGL_ASSERT(x >= params[0]);
				EEGL_ASSERT(y >= params[1]);
				EEGL_ASSERT(width <= params[2]);
				EEGL_ASSERT(height <= params[3]);
			}
			
			glScissor(x, y, width, height);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		////
		
		static std::vector<GLenum> const
		GL_VALID_CAPS()
		{
			static std::vector<GLenum> const	caps	=
			{
				GL_BLEND,
				GL_CULL_FACE,
				GL_DEPTH_TEST,
				GL_DITHER,
				GL_POLYGON_OFFSET_FILL,
				GL_SAMPLE_ALPHA_TO_COVERAGE,
				GL_SAMPLE_COVERAGE,
				GL_SCISSOR_TEST,
				GL_STENCIL_TEST,
			};
			return	caps;
		}
		template<typename T>
		bool const
		DoesVectorContainValue(std::vector<T> const vec, T const v)
		{
			return	std::find(vec.begin(), vec.end(), v) != vec.end();
		}
		
		EEGL_INLINE void
		eeglEnable(GLenum const cap)
		{
			EEGL_ASSERT(DoesVectorContainValue(GL_VALID_CAPS(), cap));
			EEGL_ASSERT(glIsEnabled(cap) == GL_FALSE);
			glEnable(cap);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglDisable(GLenum const cap)
		{
			EEGL_ASSERT(DoesVectorContainValue(GL_VALID_CAPS(), cap));
			EEGL_ASSERT(glIsEnabled(cap) == GL_TRUE);
			glDisable(cap);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_INLINE GLboolean const
		eeglIsEnabled(GLenum const cap)
		{
			EEGL_ASSERT(DoesVectorContainValue(GL_VALID_CAPS(), cap));
			GLboolean	v	=	glIsEnabled(cap);
			EEGL_ASSERT_NO_GL_ERROR();
			
			return		v;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		////	State
		
		static bool const
		IS_VALID_BLEND_SOURCE(GLenum const sfactor)
		{
			return
			sfactor == GL_ZERO or
			sfactor == GL_ONE or
			sfactor == GL_SRC_COLOR or
			sfactor == GL_ONE_MINUS_SRC_COLOR or
			sfactor == GL_DST_COLOR or
			sfactor == GL_ONE_MINUS_DST_COLOR or
			sfactor == GL_SRC_ALPHA or
			sfactor == GL_ONE_MINUS_SRC_ALPHA or
			sfactor == GL_DST_ALPHA or
			sfactor == GL_ONE_MINUS_DST_ALPHA or
			sfactor == GL_CONSTANT_COLOR or
			sfactor == GL_ONE_MINUS_CONSTANT_COLOR or
			sfactor == GL_CONSTANT_ALPHA or
			sfactor == GL_ONE_MINUS_CONSTANT_ALPHA or
			sfactor == GL_SRC_ALPHA_SATURATE
			;
		}
		static bool const
		IS_VALID_BLEND_DESTINATION(GLenum const dfactor)
		{
			return
			dfactor == GL_ZERO or
			dfactor == GL_ONE or
			dfactor == GL_SRC_COLOR or
			dfactor == GL_ONE_MINUS_SRC_COLOR or
			dfactor == GL_DST_COLOR or
			dfactor == GL_ONE_MINUS_DST_COLOR or
			dfactor == GL_SRC_ALPHA or
			dfactor == GL_ONE_MINUS_SRC_ALPHA or
			dfactor == GL_DST_ALPHA or
			dfactor == GL_ONE_MINUS_DST_ALPHA or
			dfactor == GL_CONSTANT_COLOR or
			dfactor == GL_ONE_MINUS_CONSTANT_COLOR or
			dfactor == GL_CONSTANT_ALPHA or
			dfactor == GL_ONE_MINUS_CONSTANT_ALPHA
//				dfactor == GL_SRC_ALPHA_SATURATE			//	Not supported as destination.
			;
		}
		static bool const
		IS_VALID_BLEND_MODE(GLenum const mode)
		{
			return
			mode == GL_FUNC_ADD or
			mode == GL_FUNC_SUBTRACT or
			mode == GL_FUNC_REVERSE_SUBTRACT
			;
		}
		
		EEGL_INLINE void
		eeglBlendFunc(GLenum const sfactor, GLenum const dfactor)
		{
			EEGL_ASSERT(IS_VALID_BLEND_SOURCE(sfactor));
			EEGL_ASSERT(IS_VALID_BLEND_DESTINATION(dfactor));
			
			glBlendFunc(sfactor, dfactor);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglBlendEquation(GLenum const mode)
		{
			EEGL_ASSERT(IS_VALID_BLEND_MODE(mode));
			
			glBlendEquation(mode);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglBlendColor(GLclampf const red, GLclampf const green, GLclampf const blue, GLclampf const alpha)
		{
			EEGL_ASSERT(red >= 0.0f and red <= 1.0f);
			EEGL_ASSERT(green >= 0.0f and green <= 1.0f);
			EEGL_ASSERT(blue >= 0.0f and blue <= 1.0f);
			EEGL_ASSERT(alpha >= 0.0f and alpha <= 1.0f);
			
			glBlendColor(red, green, blue, alpha);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglBlendEquationSeparate(GLenum const modeRGB, GLenum const modeAlpha)
		{
			EEGL_ASSERT(IS_VALID_BLEND_MODE(modeRGB));
			EEGL_ASSERT(IS_VALID_BLEND_MODE(modeAlpha));
			
			glBlendEquationSeparate(modeRGB, modeAlpha);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglBlendFuncSeparate(GLenum const srcRGB, GLenum const dstRGB, GLenum const srcAlpha, GLenum const dstAlpha)
		{
			EEGL_ASSERT(IS_VALID_BLEND_SOURCE(srcRGB));
			EEGL_ASSERT(IS_VALID_BLEND_SOURCE(srcAlpha));
			EEGL_ASSERT(IS_VALID_BLEND_DESTINATION(dstRGB));
			EEGL_ASSERT(IS_VALID_BLEND_DESTINATION(dstAlpha));
			
			glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		EEGL_INLINE void
		eeglDepthFunc(GLenum const func)
		{
			EEGL_ASSERT(func == GL_NEVER or
								  func == GL_LESS or
								  func == GL_EQUAL or
								  func == GL_LEQUAL or
								  func == GL_GREATER or
								  func == GL_NOTEQUAL or
								  func == GL_GEQUAL or
								  func == GL_ALWAYS
								  );
			
			glDepthFunc(func);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglDepthRangef(GLclampf const nearVal, GLclampf const farVal)
		{
			glDepthRangef(nearVal, farVal);
//				glDepthRange(nearVal, farVal);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		////	Texturing.
		
		EEGL_INLINE void
		eeglActiveTexture(GLenum const texture)
		{
			EEGL_ASSERT(texture >= GL_TEXTURE0 && texture < (GL_TEXTURE0 + eeglGetInteger(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)));
			
			glActiveTexture(texture);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		////	Vertex channeling.
		
		EEGL_INLINE void
		eeglEnableVertexAttribArray(GLuint const index)
		{
			EEGL_ASSERT(index < eeglGetInteger(GL_MAX_VERTEX_ATTRIBS));
			glEnableVertexAttribArray(index);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_INLINE void
		eeglDisableVertexAttribArray(GLuint const index)
		{
			EEGL_ASSERT(index < eeglGetInteger(GL_MAX_VERTEX_ATTRIBS));
			glDisableVertexAttribArray(index);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_INLINE void
		eeglVertexAttribPointer(GLuint const indx, GLint const size, GLenum const type, GLboolean const normalized, GLsizei const stride, GLvoid const * const ptr)
		{
			EEGL_ASSERT((size == 1) or
				   (size == 2) or
				   (size == 3) or
				   (size == 4));
			
#if	EONIL_MEDIA_ENGINE_TARGET_MINIMUM
//				EEGL_ASSERT((type == GL_BYTE) or
//					   (type == GL_UNSIGNED_BYTE) or
//					   (type == GL_SHORT) or
//					   (type == GL_UNSIGNED_SHORT) or
//					   (type == GL_FLOAT));
#else
#if	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
			EEGL_ASSERT((type == GL_BYTE) or
				   (type == GL_UNSIGNED_BYTE) or
				   (type == GL_SHORT) or
				   (type == GL_UNSIGNED_SHORT) or
				   (type == GL_FLOAT) or
				   (type == GL_FIXED));
#endif
#endif
			
			EEGL_ASSERT((normalized == GL_TRUE) or
				   (normalized == GL_FALSE));
				   
			if (Doctor::useStateValidation())
			{
//					Size const	vsz	=	stride == 0 ? (Doctor::sizeOfGLType(type) * size) : stride;
			}
			
			glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
		}
		
		
		
		
		
		
		
		
		////	Drawing.
		
		EEGL_INLINE void
		eeglClear (GLbitfield const mask)
		{
			EEGL_ASSERT(((mask & GL_COLOR_BUFFER_BIT) +
				   (mask & GL_DEPTH_BUFFER_BIT) +
				   (mask & GL_STENCIL_BUFFER_BIT)) > 0);
			glClear(mask);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_INLINE void
		eeglClearDepthf(GLclampf depth)
		{
			EEGL_ASSERT(depth >=0 and depth <= 1);
			glClearDepthf(depth);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_INLINE void
		eeglClearColor (GLclampf const red, GLclampf const green, GLclampf const blue, GLclampf const alpha)
		{
			EEGL_ASSERT(red >= 0.0f && red <=1.0f);
			EEGL_ASSERT(green >= 0.0f && green <=1.0f);
			EEGL_ASSERT(blue >= 0.0f && blue <=1.0f);
			EEGL_ASSERT(alpha >= 0.0f && alpha <=1.0f);
			glClearColor(red, green, blue, alpha);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_INLINE void
		eeglDrawArrays(GLenum const mode, GLint const first, GLsizei const count)
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
			 If this function crashes while executing, it's mostly because of bad vertex data.
			 Regardless of where it is. (client or server) So check the data integrity first.
			 
			 Detection or assertion for the bad data is very hard and really inefficient. (even for debug
			 build!) So I am not currently implementing it.
			 */
			glDrawArrays(mode, first, count);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_INLINE void
		eeglDrawElement(GLenum const mode, GLsizei const count, GLenum const type, GLvoid const * const indices)
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
			
			/*!
			 CRASH NOTE
			 ==========
			 If this function crashes while executing, it's mostly because of bad vertex/index data.
			 Regardless of where it is. (client or server) So check the data integrity first.
			 
			 Detection or assertion for the bad data is very hard and really inefficient. (even for debug
			 build!) So I am not currently implementing it.
			 */
			glDrawElements(mode, count, type, indices);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
	}







}}}}