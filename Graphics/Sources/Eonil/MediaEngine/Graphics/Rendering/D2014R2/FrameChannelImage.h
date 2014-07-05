////
////  FrameChannelImage.h
////  Graphics
////
////  Created by Hoon H. on 2/17/14.
////
////
//
//#ifndef __Graphics__FrameChannelImage__
//#define __Graphics__FrameChannelImage__
//
//#include "../../Common.h"
//
//EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
//	
//	namespace
//	Rendering
//	{
//		namespace
//		D2014R2
//		{
//			
//			
//			/*!
//			 An image storage as a unit for frame composition.
//			 
//			 @classdesign
//			 Actual image storage can be one of texture or renderbuffer target.
//			 */
//			class
//			FrameChannelImage : public TrackableObject
//			{
//				struct	Core;
//				struct	RBCore;
//				struct	TXCore;
//				
//				uptr<Core>	_core{};
//				
//			public:
//				FrameChannelImage() = default;
//				FrameChannelImage(FrameChannelImage&&) = default;
//				FrameChannelImage(Server::Renderbuffer&& buffer);
//				FrameChannelImage(Server::PlanarTexture&& texture);
//				
//				auto	empty() const -> bool;
//				auto	buffer() const -> Server::Framebuffer const&;
//				
//			public:
//				//				static auto	frameWithSystemFrame() -> RenderingFrame;								//!	Creates a frame which renders to the system provided frame-buffer.
//				//				static auto	frameWithUserBuffer(Server::Framebuffer&& buffer) -> RenderingFrame;	//!	Creates a frame which renders to a user-created frame-buffer. Creates image frame will own the buffer.
//			};
//			
//			
//			
//			
//			
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
//
//#endif /* defined(__Graphics__FrameChannelImage__) */
