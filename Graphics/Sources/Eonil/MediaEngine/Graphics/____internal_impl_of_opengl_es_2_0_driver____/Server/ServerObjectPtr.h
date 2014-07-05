////
////  ServerObjectPtr.h
////  Graphics
////
////  Created by Hoon H. on 4/12/14.
////
////
//
//#ifndef __Graphics__ServerObjectPtr__
//#define __Graphics__ServerObjectPtr__
//
//#include "../Common.h"
//
//INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN
//	
//	namespace
//	Server
//	{
//		
//		class
//		ServerObjectName
//		{
//			
//		};
//		
//		/*!
//		 A pointer to an object in remote graphics server.
//		 
//		 @discussion
//		 This needs to be used conjunction with server-side object.
//		 */
//		template <typename T>
//		class
//		ServerObjectPtr : public local<T>
//		{
//		public:
//		};
//		
//		
//		class
//		ProgramName : public ServerObjectName
//		{
//			friend class	ServerObjectPtr<ProgramName>;
//		
//			
//		};
//
//		
//		
//		using	ConstProgram	=	ServerObjectPtr<ProgramName const>;
//		using	Program			=	ServerObjectPtr<ProgramName>;
//		
//		
//		
//		
//		
//	}
//	
//}}}}
//
//#endif /* defined(__Graphics__ServerObjectPtr__) */
