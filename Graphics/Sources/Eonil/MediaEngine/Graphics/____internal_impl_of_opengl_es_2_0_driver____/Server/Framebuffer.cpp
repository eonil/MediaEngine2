//
//  Framebuffer.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "Framebuffer.h"
#include "../Stub/GL-Framebuffer.h"
#include "../Stub/GL-Renderbuffer.h"
#include "Texture.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Server
{
	using namespace	Stub;
	
	
//		
//		namespace
//		{
//			static inline auto
//			_dbg_fb_rb_bindings() -> map<Framebuffer const*, vec<Renderbuffer const*>>
//			{
//				static map<Framebuffer const*, vec<Renderbuffer const*>>*	_m	{nullptr};
//				if (_m == nullptr)
//				{
//					_m	=	new map<Framebuffer const*, vec<Renderbuffer const*>> {};
//				}
//				return	*_m;
//			}
//			static inline auto
//			_dbg_fb_tx_bindings() -> map<Framebuffer const*, vec<Texture2D const*>>
//			{
//				static map<Framebuffer const*, vec<Texture2D const*>>*	_m	{nullptr};
//				if (_m == nullptr)
//				{
//					_m	=	new map<Framebuffer const*, vec<Texture2D const*>> {};
//				}
//				return	*_m;
//			}
//		}
	
	
	
	
	

	
	Renderbuffer::
	Renderbuffer(FORMAT const& format, sz const& width, sz const& height) : _name(eeglGenRenderbuffer())
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(_name != NULL_GL_NAME());
		}
		
		////
		
		eeglBindRenderbuffer(GL_RENDERBUFFER, _name);

		GLsizei	w	=	toGLsizei(width);
		GLsizei	h	=	toGLsizei(height);
		eeglRenderbufferStorage(GL_RENDERBUFFER, GLenum(format), w, h);
		eeglUnbindRenderbuffer(GL_RENDERBUFFER);
	}
	Renderbuffer::
	~Renderbuffer()
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(_name != NULL_GL_NAME());
		}

		////
		
		eeglDeleteRenderbuffer(_name);
	}
	
	
	auto Renderbuffer::
	empty() const -> bool
	{
		return	_name == NULL_GL_NAME();
	}
	auto Renderbuffer::
	name() const -> GLuint
	{
		return	_name;
	}
	
	
	
	
	
	
	
	
	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
//		Framebuffer::
//		Framebuffer(ChannelStorage const& color) : Framebuffer(color, {}, {})
//		{
//			
//		}
//		Framebuffer::
//		Framebuffer(ChannelStorage const& color, ChannelStorage const& depth) : Framebuffer(color, depth, {})
//		{
//			
//		}
	Framebuffer::
	Framebuffer(ChannelStorage const& color, ChannelStorage const& depth, ChannelStorage const& stencil) : _name(eeglGenFramebuffer())
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
//				err9_converted_legacy_assertion(not color.empty());
//				err9_converted_legacy_assertion(not depth.empty());
//				err9_converted_legacy_assertion(not stencil.empty());
			err9_converted_legacy_assertion(not (color.empty() and depth.empty() and stencil.empty()));
		}
		
		////
		
		eeglBindFramebuffer(GL_FRAMEBUFFER, _name);
		if (not color.empty())
		{
			_dbg_color		=	color;
			color._run(GL_COLOR_ATTACHMENT0);
		}
		if (not depth.empty())
		{
			_dbg_depth		=	depth;
			color._run(GL_DEPTH_ATTACHMENT);
		}
		if (not stencil.empty())
		{
			_dbg_stencil	=	stencil;
			color._run(GL_STENCIL_ATTACHMENT);
		}
		
		////
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(GL_FRAMEBUFFER_COMPLETE == eeglCheckFramebufferStatus(GL_FRAMEBUFFER));
		}
		////
		
		eeglUnbindFramebuffer(GL_FRAMEBUFFER);
	}
	Framebuffer::~Framebuffer()
	{
		if (_name != 0)
		{				
			/*
			 GL will automatically detach all renderbuffers from framebuffer when the frambuffer deleted.
			 */
			
			////
			if (USE_DEBUGGING_ASSERTIONS)
			{
				assertCurrentGLContextExistence();
			}
			////
			
			eeglDeleteFramebuffer(_name);
		}
	}
	auto Framebuffer::
	name() const -> GLuint const&
	{
		return	_name;
	}
	
	






	
	
	

	
	
	
	
	
	
	Framebuffer::ChannelStorage::
	ChannelStorage(Renderbuffer const& renderbuffer)
	{
		_run	=	[&renderbuffer](GLenum const& attachment)
		{
			ptr<Renderbuffer const>	rbptr	{&renderbuffer};
			eeglFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, rbptr->name());
		};
	}
	Framebuffer::ChannelStorage::
	ChannelStorage(Texture2D const& texture, TEXTURE_TARGET const& target, GLint const& level)
	{
		_run	=	[&texture, target, level](GLenum const& attachment)
		{
			ptr<Texture2D const>	txptr	{&texture};
			eeglFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GLenum(target), txptr->name(), level);
		};
	}
	
	
	auto Framebuffer::ChannelStorage::
	empty() const -> bool
	{
		return	_run == nullptr;
	}







}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END










