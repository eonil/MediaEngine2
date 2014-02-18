////
////  Channeling.h
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 6/13/13.
////
////
//
//#ifndef __EonilGraphics__Channeling__
//#define __EonilGraphics__Channeling__
//
//#include "../Common.h"
//#include "Buffer.h"
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		namespace
//		Server
//		{
////			struct	Channeling;
////			struct	IndexChanneling;
////			struct	VertexChanneling;
////			
////			
////			
////			
////			
////			struct
////			Channeling
////			{
////				
////			};
//			
//			
//			
//			
//			
//			
//			
//			
//			struct
//			IndexChanneling
//			{	
//				struct
//				Type
//				{
//					Type() = delete;
//					
//					enum
//					CODE
//					{
//						UINT8	=	GL_UNSIGNED_BYTE,
//						UINT16	=	GL_UNSIGNED_SHORT,
//					};
//				};
//				
//				////
//				
//				struct
//				FromNowhere
//				{
//					Type::CODE			elementTypecode;
//					
//					FromNowhere(Type::CODE const type) : elementTypecode(type)
//					{
//					}
//				};
//				
//				struct
//				FromServerBuffer : public FromNowhere
//				{
//					ElementArrayBuffer	serverBuffer;
//					Size				dataOffset;
//					
//					FromServerBuffer(Type::CODE const type, ElementArrayBuffer const buffer, Size const offset = 0) : FromNowhere::FromNowhere(type), serverBuffer(buffer), dataOffset(offset)
//					{
//					}
//				};
//				
//				struct
//				FromClientMemory : public FromNowhere
//				{
//					void const*			clientMemory;
//					
//					FromClientMemory(Type::CODE const type, void const* address) : FromNowhere::FromNowhere(type), clientMemory(address)
//					{
//					}
//				};
//				
//				////
//				
//				struct
//				Utility
//				{
//					Utility() = delete;
//					
//					static IndexChanneling::FromServerBuffer const	channelingFromServerWithType(Type::CODE const type, ElementArrayBuffer const buffer, Size const offset);
//					static IndexChanneling::FromClientMemory const	channelingFromClientWithType(Type::CODE const type, void const* const memory);
//				};
//			};
//			
//			
//		}
//	}
//}
//
//#endif /* defined(__EonilGraphics__Channeling__) */
//
//
