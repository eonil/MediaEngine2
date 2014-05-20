////
////  Describer.h
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 5/1/13.
////  Copyright (c) 2013 Eonil. All rights reserved.
////
//
//#ifndef __EonilGraphics__Describer__
//#define __EonilGraphics__Describer__
//
//#include	"../Server/Shader.h"
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		namespace
//		Debug
//		{
//			class
//			Doctor;
//			
//			using namespace	Eonil::Improvisations::MediaEngine::Graphics::Server;
//			
//			template<typename T>
//			struct
//			Describer
//			{
//				static std::string const
//				describe(T const& value)
//				{
//					return	Doctor::stringWithCFormat("<????: 0x%llx>", &value);
//				}
//			};
//		
//			template<> struct
//			Describer<VertexShader>
//			{
//				static String const
//				describe(VertexShader const& value)
//				{
//					return	value.description();
//				}
//			};
//		}
//	}
//}
//
//#endif /* defined(__EonilGraphics__Describer__) */
