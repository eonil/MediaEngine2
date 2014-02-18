////
////  Shot.h
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 6/3/13.
////
////
//
//#ifndef __EonilGraphics__Shot__
//#define __EonilGraphics__Shot__
//
//#include "State.h"
//#include "Camera.h"
//#include "Presentation.h"
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		/*!
//		 Represents a space captured by a camera.
//		 This is snapshot of a scene.
//		 
//		 Shot is limited only to single space with a single camera.
//		 If you want to present objects in multiple spaces, you have to project them into a single 
//		 space first by transforming them.
//		 
//		 A shot creates a layer. So a shot is combination of machine state and multiple presentations.
//		 Presentation is abstracted renderable entity. It can be a single transformed mesh or can be
//		 a cloud of multiple sprites. Or anything else. You can create custom renderable entity by
//		 subclassing Presentation class. There are these default presentation classes.
//		 
//		 -	SkinFigure
//		 -	SkeletalFigure
//		 
//		 */
//		struct
//		Shot
//		{
//			
//			Camera						camera;
//			std::vector<Presentation>	presentations;
//		};
//	}
//}
//
//
//#endif /* defined(__EonilGraphics__Shot__) */
