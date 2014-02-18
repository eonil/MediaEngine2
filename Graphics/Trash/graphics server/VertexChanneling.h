////
////  VertexChanneling.h
////  EonilGraphics
////
////  Created by Eonil on 5/1/13.
////  Copyright (c) 2013 Eonil. All rights reserved.
////
//
//#ifndef __EonilGraphics__VertexChanneling__
//#define __EonilGraphics__VertexChanneling__
//
//#include	"Buffer.h"
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
//			struct
//			VertexChannelingFormat
//			{
//				enum
//				SIZE : GLint
//				{
//					ZERO	=	0,
//					ONE		=	1,
//					TWO		=	2,
//					THREE	=	3,
//					FOUR	=	4,
//				};
//				enum
//				TYPE : GLenum
//				{
//					NONE	=	0,
//					BYTE	=	GL_BYTE,
//					UBYTE	=	GL_UNSIGNED_BYTE,
//					SHORT	=	GL_SHORT,
//					USHORT	=	GL_UNSIGNED_SHORT,
//					FLOAT	=	GL_FLOAT,
//					#if	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
//					FIXED	=	GL_FIXED,
//					#endif
//				};
//				
//				SIZE			componentCount		=	ZERO;
//				TYPE			componentType		=	NONE;
//				GLboolean		normalization		=	GL_FALSE;
//				GLsizei			strideSizeInBytes	=	0;
//					
////				////
////					
////				struct
////				Utility
////				{
////					static VertexChannelingFormat const
////					vertexChannelingFormat(SIZE const componentCount, TYPE const componentType, GLboolean const normalization, GLsizei const strideSizeInBytes)
////					{
////						VertexChannelingFormat	vf;
////						vf.componentCount		=	componentCount;
////						vf.componentType		=	componentType;
////						vf.normalization		=	normalization;
////						vf.strideSizeInBytes	=	strideSizeInBytes;
////						return	vf;
////					}
////				};
//			};
//					
//			struct
//			VertexSourcingWithClientMemory
//			{
//				struct
//				ChannelingFormat : public VertexChannelingFormat
//				{
//					GLvoid const*	memoryAddress		=	NULL;		//	This is raw pointer rather than Data object because address may be overlap.
//					Size			memoryLength		=	0;			//	Explciit length for validation. Shoud I make this optional for debugging build?
//				};
//				std::vector<ChannelingFormat>	channelingFormats;
//			};
//			struct
//			VertexSourcingWithServerBuffer
//			{
//				struct
//				ChannelingFormat : public VertexChannelingFormat
//				{
//					GLvoid*		offsetInBuffer		=	(GLvoid*)-1;
//
//					Size const	bufferOffsetInBytes() const;
//					void		setBufferOffsetInBytes(Size const offsetInBytes);
////					
////					struct
////					Utility
////					{
////						
////					}
//				};
//				
//				std::vector<ChannelingFormat>	channelingFormats;
//				ArrayBuffer						dataBuffer;
//				
//				VertexSourcingWithServerBuffer(ArrayBuffer const dataBuffer);
//			};
//			
//
//
//			
//		}
//	}
//}
//#endif /* defined(__EonilGraphics__VertexChanneling__) */
//
//
//
