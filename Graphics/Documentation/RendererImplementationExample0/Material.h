////
////  Material.h
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 6/16/13.
////
////
//
//#ifndef __EonilGraphics__Material__
//#define __EonilGraphics__Material__
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		/*!
//		 A material is prebound, immutable instance of a shader.
//		 
//		 @classdesign
//		 Shaders usually have multiple parameters. These values 
//		 need to be set before using the program. Anyway binding
//		 value is a mutating operation, which should be prohibited 
//		 at this level of abstraction. So material is created by
//		 binding a shader with all its parameters. What you have to
//		 do to draw a form is just combining them with a material.
//		 
//		 @note
//		 Forms are designed to have specific attributes for specific
//		 drawing method. Shaders can be vary within the designed 
//		 limit, but cannot be varied infinityly.
//		 
//		 So we need a way to specify compatibility between shaders 
//		 and materials. And this cannot be done without experiences.
//		 
//		 */
//		class
//		Material
//		{
//		public:
//			Material(Program const& program);
//		};
//	}
//}
//
//#endif /* defined(__EonilGraphics__Material__) */
