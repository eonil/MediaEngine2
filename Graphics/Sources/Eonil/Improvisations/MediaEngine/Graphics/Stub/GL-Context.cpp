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
		
		namespace
		{
			template<typename T>
			static inline auto
			contains_target_in_samples(T const& target, vec<T> const& samples) -> bool
			{
				return	std::find(samples.begin(), samples.end(), target) != samples.end();
			}
			
			static inline auto
			is_valid_face(GLenum const face) -> bool
			{
				return
				contains_target_in_samples(face,
										   {
											   GL_FRONT,
											   GL_BACK,
											   GL_FRONT_AND_BACK,
										   });
			}
			
			static inline auto
			is_valid_func(GLenum const func) -> bool
			{
				return
				contains_target_in_samples(func,
										   {
											   GL_NEVER,
											   GL_LESS,
											   GL_LEQUAL,
											   GL_GREATER,
											   GL_GEQUAL,
											   GL_EQUAL,
											   GL_NOTEQUAL,
											   GL_ALWAYS,
										   });
			}
			
			static inline auto
			is_valid_stencil_test_op(GLenum const op) -> bool
			{
				return
				contains_target_in_samples(op,
										   {
											   GL_KEEP,
											   GL_ZERO,
											   GL_REPLACE,
											   GL_INCR,
											   GL_INCR_WRAP,
											   GL_DECR,
											   GL_DECR_WRAP,
											   GL_INVERT,
										   });
			}
			
			
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
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		EEGL_STUB_API_DECO void
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

		EEGL_STUB_API_DECO void
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
		
		EEGL_STUB_API_DECO void
		eeglEnable(GLenum const cap)
		{
			EEGL_ASSERT(DoesVectorContainValue(GL_VALID_CAPS(), cap));
			EEGL_ASSERT(glIsEnabled(cap) == GL_FALSE);
			glEnable(cap);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_STUB_API_DECO void
		eeglDisable(GLenum const cap)
		{
			EEGL_ASSERT(DoesVectorContainValue(GL_VALID_CAPS(), cap));
			EEGL_ASSERT(glIsEnabled(cap) == GL_TRUE);
			glDisable(cap);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_STUB_API_DECO GLboolean const
		eeglIsEnabled(GLenum const cap)
		{
			EEGL_ASSERT(DoesVectorContainValue(GL_VALID_CAPS(), cap));
			GLboolean	v	=	glIsEnabled(cap);
			EEGL_ASSERT_NO_GL_ERROR();
			
			return		v;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
#pragma mark	-	Per-Fragment Operations
		
		
		
		EEGL_STUB_API_DECO void
		eeglStencilFuncSeparate(GLenum const face, GLenum const func, GLint const ref, GLuint const mask)
		{
			EEGL_ASSERT(is_valid_face(face));
			EEGL_ASSERT(is_valid_func(func));
			EEGL_ASSERT(ref > 0);
			{
				glStencilFuncSeparate(face, func, ref, mask);
			}
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_STUB_API_DECO void
		eeglStencilOpSeparate(GLenum const face, GLenum const sfail, GLenum const dpfail, GLenum const dppass)
		{
			EEGL_ASSERT(is_valid_face(face));
			EEGL_ASSERT(is_valid_stencil_test_op(sfail));
			EEGL_ASSERT(is_valid_stencil_test_op(dpfail));
			EEGL_ASSERT(is_valid_stencil_test_op(dppass));
			{
				glStencilOpSeparate(face, sfail, dpfail, dppass);
			}
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		
		
		
		
		EEGL_STUB_API_DECO void
		eeglDepthFunc(GLenum const func)
		{
			EEGL_ASSERT(is_valid_func(func));
			{
				glDepthFunc(func);
			}
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_STUB_API_DECO void
		eeglDepthRangef(GLclampf const nearVal, GLclampf const farVal)
		{
			glDepthRangef(nearVal, farVal);
//			glDepthRange(nearVal, farVal);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		
		
		
		
		
		
		
		
		
		EEGL_STUB_API_DECO void
		eeglBlendFunc(GLenum const sfactor, GLenum const dfactor)
		{
			EEGL_ASSERT(IS_VALID_BLEND_SOURCE(sfactor));
			EEGL_ASSERT(IS_VALID_BLEND_DESTINATION(dfactor));
			
			glBlendFunc(sfactor, dfactor);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_STUB_API_DECO void
		eeglBlendEquation(GLenum const mode)
		{
			EEGL_ASSERT(IS_VALID_BLEND_MODE(mode));
			
			glBlendEquation(mode);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_STUB_API_DECO void
		eeglBlendColor(GLclampf const red, GLclampf const green, GLclampf const blue, GLclampf const alpha)
		{
			EEGL_ASSERT(red >= 0.0f and red <= 1.0f);
			EEGL_ASSERT(green >= 0.0f and green <= 1.0f);
			EEGL_ASSERT(blue >= 0.0f and blue <= 1.0f);
			EEGL_ASSERT(alpha >= 0.0f and alpha <= 1.0f);
			
			glBlendColor(red, green, blue, alpha);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_STUB_API_DECO void
		eeglBlendEquationSeparate(GLenum const modeRGB, GLenum const modeAlpha)
		{
			EEGL_ASSERT(IS_VALID_BLEND_MODE(modeRGB));
			EEGL_ASSERT(IS_VALID_BLEND_MODE(modeAlpha));
			
			glBlendEquationSeparate(modeRGB, modeAlpha);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_STUB_API_DECO void
		eeglBlendFuncSeparate(GLenum const srcRGB, GLenum const dstRGB, GLenum const srcAlpha, GLenum const dstAlpha)
		{
			EEGL_ASSERT(IS_VALID_BLEND_SOURCE(srcRGB));
			EEGL_ASSERT(IS_VALID_BLEND_SOURCE(srcAlpha));
			EEGL_ASSERT(IS_VALID_BLEND_DESTINATION(dstRGB));
			EEGL_ASSERT(IS_VALID_BLEND_DESTINATION(dstAlpha));
			
			glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		////	Texturing.
		
		EEGL_STUB_API_DECO void
		eeglActiveTexture(GLenum const texture)
		{
			EEGL_ASSERT(texture >= GL_TEXTURE0 && texture < (GL_TEXTURE0 + eeglGetInteger(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)));
			
			glActiveTexture(texture);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		
		
		////	Vertex channeling.
		
		EEGL_STUB_API_DECO void
		eeglEnableVertexAttribArray(GLuint const index)
		{
			EEGL_ASSERT(index < eeglGetInteger(GL_MAX_VERTEX_ATTRIBS));
			glEnableVertexAttribArray(index);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_STUB_API_DECO void
		eeglDisableVertexAttribArray(GLuint const index)
		{
			EEGL_ASSERT(index < eeglGetInteger(GL_MAX_VERTEX_ATTRIBS));
			glDisableVertexAttribArray(index);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_STUB_API_DECO void
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
		
		EEGL_STUB_API_DECO void
		eeglClear (GLbitfield const mask)
		{
			EEGL_ASSERT(((mask & GL_COLOR_BUFFER_BIT) +
						 (mask & GL_DEPTH_BUFFER_BIT) +
						 (mask & GL_STENCIL_BUFFER_BIT)) > 0);
			{
				glClear(mask);
			}
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_STUB_API_DECO void
		eeglClearDepthf(GLclampf depth)
		{
			EEGL_ASSERT(depth >=0 and depth <= 1);
			{
#if	EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
				glClearDepth(depth);
#else
				glClearDepthf(depth);
#endif
			}
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_STUB_API_DECO void
		eeglClearColor (GLclampf const red, GLclampf const green, GLclampf const blue, GLclampf const alpha)
		{
			EEGL_ASSERT(red >= 0.0f && red <=1.0f);
			EEGL_ASSERT(green >= 0.0f && green <=1.0f);
			EEGL_ASSERT(blue >= 0.0f && blue <=1.0f);
			EEGL_ASSERT(alpha >= 0.0f && alpha <=1.0f);
			{
				glClearColor(red, green, blue, alpha);
			}
			EEGL_ASSERT_NO_GL_ERROR();
		}
		EEGL_STUB_API_DECO void
		eeglClearStencil(GLint const s)
		{
#if	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
			/*
			 I don't know why but desktop OpenGL 3.0+ doesn't support `GL_STENCIL_BITS` symbol.
			 So this marked as conditional only for OpenGL ES 2.0.
			 */
			EEGL_RUN_AS_ASSERTION
			({
				GLint	stencil_bits	=	eeglGetInteger(GL_STENCIL_BITS);
//				if (stencil_bits >= 64)
//				{
//					EEGL_ASSERT(s <= std::numeric_limits<int64_t>::max());
//				}
				if (stencil_bits >= 32)
				{
					EEGL_ASSERT(s <= std::numeric_limits<int32_t>::max());
				}
				if (stencil_bits >= 16)
				{
					EEGL_ASSERT(s <= std::numeric_limits<int16_t>::max());
				}
				if (stencil_bits >= 8)
				{
					EEGL_ASSERT(s <= std::numeric_limits<int8_t>::max());
				}
				if (stencil_bits >= 4)
				{
					EEGL_ASSERT(s <= (2*2*2*2));
				}
			});
#endif
			
			glClearStencil(s);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_STUB_API_DECO void
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
			 If this function crashes while being executed, it's mostly because of bad vertex data.
			 Regardless of where it is. (client or server) So check the data integrity first.
			 
			 Detection or assertion for the bad data is very hard and really inefficient. (even for debug
			 build!) So I am not currently implementing it.
			 */
			glDrawArrays(mode, first, count);
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
		EEGL_STUB_API_DECO void
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
			{
				
				/*!
				 CRASH NOTE
				 ==========
				 If this function crashes while being executed, it's mostly because of bad vertex/index data.
				 Regardless of where it is. (client or server) So check the data integrity first.
				 
				 Detection or assertion for the bad data is very hard and really inefficient. (even for debug
				 build!) So I am not currently implementing it.
				 */
				glDrawElements(mode, count, type, indices);
			}
			EEGL_ASSERT_NO_GL_ERROR();
		}
		
	}







}}}}