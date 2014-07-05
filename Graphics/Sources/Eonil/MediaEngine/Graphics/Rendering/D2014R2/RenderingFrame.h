////
////  RenderingFrame.h
////  Graphics
////
////  Created by Hoon H. on 2/17/14.
////
////
//
//#ifndef __Graphics__RenderingFrame__
//#define __Graphics__RenderingFrame__
//
//#include "../../Common.h"
//#include "../../Server/Framebuffer.h"
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
//			
//			
//			
//			/*!
//			 An image storage as a unit for frame composition.
//			 
//			 @classdesign
//			 This supports only texture target. Because you cannot read from renderbuffer
//			 in shader, so renderbuffer cannot be used for composition source, and only 
//			 can be used final presentation target or temporary storage.
//			
//			 
//			 */
//			class
//			RenderingFrame final : public TrackableObject
//			{
//				uptr<Server::Framebuffer>	_core		{};
//				
//			public:
//				RenderingFrame();
//				RenderingFrame(RenderingFrame&&);
//				RenderingFrame(Server::Framebuffer&& buffer);
//				~RenderingFrame();
//				
//				auto	operator=(RenderingFrame&&) -> RenderingFrame& = default;
//				
//				auto	empty() const -> bool;
//				auto	buffer() const -> Server::Framebuffer const&;
//				
//			public:
////				static auto	frameWithSystemFrame() -> RenderingFrame;								//!	Creates a frame which renders to the system provided frame-buffer.
////				static auto	frameWithUserBuffer(Server::Framebuffer&& buffer) -> RenderingFrame;	//!	Creates a frame which renders to a user-created frame-buffer. Creates image frame will own the buffer.
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
//#endif /* defined(__Graphics__RenderingFrame__) */
