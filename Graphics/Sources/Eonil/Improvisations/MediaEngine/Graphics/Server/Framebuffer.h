//
//  Framebuffer.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__Framebuffer__
#define __EonilGraphics__Framebuffer__

#include "../Common.h"
#include "Declarations.h"
#include "ServerObjectProxy.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		
		
		
		
		
		
		
		
		
		/*!
		 @brief			
						Encapsulates a OpenGL ES 2.0 renderbuffer.
		 
		 
		 
		 @classdesign	
						You have to set all the required parameters at construction.
		 
		 
		 
		 @discussion
		 
		 
		 
		 @note			
						You should not delete a renderbuffer which is currently bound to a framebuffer. (asserted in debug build)
		 
		 
		 
		 @warning		
						This class has not been tested well. Because we don't have nice testing method on OpenGL API,
						we need much time to be sure on the reliability of this class. 
						Remove this warning when you feel ready.
		 */
		class
		Renderbuffer : public ServerObjectProxy
		{
			friend class	Framebuffer;
			
			GLuint			_name{NULL_GL_NAME()};
			
		public:
			enum class
			FORMAT : GLenum
			{
				RGBA4					=	GL_RGBA4,
				RGB565					=	GL_RGB565,
				RGB5A1					=	GL_RGB5_A1,
				DEPTH16					=	GL_DEPTH_COMPONENT16,
				STENCIL8				=	GL_STENCIL_INDEX8,
				
#if	EONIL_MEDIA_ENGINE_TARGET_OSX
				
#endif
				
#if	EONIL_MEDIA_ENGINE_TARGET_IOS
				
#endif
				
			};
			
		public:
			/*!
			 Creates an empty (invalid state) object.
			 */
			Renderbuffer() = default;
			
			/*!
			 Creates a valid renderbuffer object.
			 */
			Renderbuffer(FORMAT const& format, Size const& width, Size const& height);
			
			~Renderbuffer();
			
			auto	empty() const -> bool;
			auto	name() const -> GLuint;
		};
		
		
		
		

		
		
		
		
		
		
		
		
		
		
		
		
		
		/*!
		 @brief
		 Encapsulates OpenGL ES 2.0 *application provided* framebuffer object.
		 
		 
		 
		 @classdesign
		 This is explicitly application-provided-framebuffer-only.
		 
		 You can't use this to make final output framebuffer. Final display is done by
		 using platform specific framebuffer/renderbuffer setup, and the setup is very different
		 by the platforms. To eliminate this difference, I provided platform specific features, 
		 and you should use them to get final output framebuffer.
		 
		 Unlike bare GL design, this class is designed to minimize user error. For that,
		 this class tries to provide maximum immutability. For example, you need to provide all 
		 the requires parameters to create a *complete* framebuffer. As a result, a created 
		 framebuffer is always *fully initialized, and ready for use state*. You don't need to
		 worry about invalid state error. Framebuffer state is always complete, otherwise you 
		 will be notified an exception in debug build. (no check on release build)
		 
		 
		 
		 @discussion
		 This class does not support default-framebuffer semantics defined in GL ES 2.0
		 standard. (name = `0`) This is a limitation to provide consistency with other server
		 -side objects. Parameter-less construction of this class will provide empty (invalid)
		 object rather than a default object.
		 
		 In iOS, the system does not provide default framebuffer, and we always have to create
		 a framebuffer explicitly. So there's no zero-name default-framebuffer issue. OS X has
		 the concept of default framebuffer, and we need to deal with it. Anyway, you have to 
		 use low-level `eegl~` functions directly.
		 */
		class
		Framebuffer : public ServerObjectProxy
		{
		public:
			enum class
			TEXTURE_TARGET : GLenum
			{
				PLANE			=	GL_TEXTURE_2D,
				CUBE_POSITIVE_X	=	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				CUBE_POSITIVE_Y	=	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
				CUBE_POSITIVE_Z	=	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
				CUBE_NAGATIVE_X	=	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
				CUBE_NAGATIVE_Y	=	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
				CUBE_NAGATIVE_Z	=	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			};
			class
			ChannelStorage
			{
				friend class	Framebuffer;
				
				std::function<void(GLenum const& attachment)>	_run{nullptr};
				
			public:
				ChannelStorage() = default;
				ChannelStorage(Renderbuffer const& renderbuffer);
				ChannelStorage(PlanarTexture const& texture, TEXTURE_TARGET const& target, GLint const& level = 0);
				
				auto	empty() const -> bool;
			};
			struct
			Configuration
			{
				ChannelStorage	color	{};
				ChannelStorage	depth	{};
				ChannelStorage	stencil	{};
			};
			
			
			
			
//			struct
//			Channel
//			{
//				auto	setStorage(Renderbuffer const& renderbuffer) -> void;
//				auto	setStorage(PlanarTexture const& texture, TEXTURE_TARGET const& target, GLint const& level = 0) -> void;
//				auto	unsetStorage() -> void;
//			};
			
		public:
			Framebuffer() = default;						//!	Creates an empty instance. (invalid state)
			Framebuffer(Framebuffer&&) = default;
			
		public:
//			Framebuffer(ChannelStorage const& color);																	//!	Creates a ready-made framebuffer with the renderbuffers.
//			Framebuffer(ChannelStorage const& color, ChannelStorage const& depth);										//!	Creates a ready-made framebuffer with the renderbuffers.
//			Framebuffer(ChannelStorage const& color, ChannelStorage const& depth, ChannelStorage const& stencil);		//!	Creates a ready-made framebuffer with the renderbuffers.

			/*!
			 Creates a ready-made framebuffer with the renderbuffers.
			 Use empty instance for the channels that you don't want to create.
			 */
			Framebuffer(ChannelStorage const& color, ChannelStorage const& depth, ChannelStorage const& stencil);
			~Framebuffer();
			
			auto	name() const -> GLuint const&;
			
//			auto	setColorChannelStorage(ChannelStorage const& storage) -> void;
//			auto	unsetColorChannelStorage() -> void;
//			
//			auto	setDepthChannelStorage(ChannelStorage const& storage) -> void;
//			auto	unsetDepthChannelStorage() -> void;
//			
//			auto	setStencilChannelStorage(ChannelStorage const& storage) -> void;
//			auto	unsetStencilChannelStorage() -> void;
			
//		public:
//			static auto	presentationFramebuffer() -> Framebuffer;		//!	System provided framebuffer for screen display.
//			static auto	offscreenFramebuffer() -> Framebuffer;			//!	User created framebuffer for offscreen operations.
			
		private:
			/*!
			 Take care that `0` means default framebuffer rather than null state.
			 So it did not bound to `NULL_GL_NAME()`.
			 */
			GLuint				_name			{0};
			
			ChannelStorage		_dbg_color		{};
			ChannelStorage		_dbg_depth		{};
			ChannelStorage		_dbg_stencil	{};
		};
		
		
		
				
		
		

	}
	
}}}}

#endif /* defined(__EonilGraphics__Framebuffer__) */
