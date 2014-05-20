////
////  RenderingFrame.cpp
////  Graphics
////
////  Created by Hoon H. on 2/17/14.
////
////
//
//#include "RenderingFrame.h"
//
//#include "../../Server/Framebuffer.h"
//
//namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
//	
//	namespace
//	Rendering
//	{
//		namespace
//		D2014R2
//		{
//			
//			
//			RenderingFrame::RenderingFrame()
//			{
//			}
//			RenderingFrame::RenderingFrame(RenderingFrame&& o) : _core(std::move(o._core))
//			{
//			}
//			RenderingFrame::RenderingFrame(Server::Framebuffer&& buffer) : _core(new Server::Framebuffer(std::move(buffer)))
//			{
//			}
//			RenderingFrame::~RenderingFrame()
//			{
//			}
//			
//			auto RenderingFrame::
//			empty() const -> bool
//			{
//				return	_core == nullptr;
//			}
//			auto RenderingFrame::
//			buffer() const -> Server::Framebuffer const&
//			{
//				return	*_core;
//			}
//			
//			
//			
//			
//			auto RenderingFrame::
//			colorChannelTexture() const -> Server::PlanarTexture const -> 
//			
//			
//			
//			
//			
//			
//			
//		}
//	}
//	
//}}}}
