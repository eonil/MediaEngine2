////
////  RegularCircleDrawer.h
////  Graphics
////
////  Created by Hoon H. on 2/17/14.
////
////
//
//#pragma once
//#include "RenderingD2014R2Common.h"
//#include "RegularPolygonDrawer.h"
//EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
//
//namespace
//Rendering
//{
//	namespace
//	D2014R2
//	{
//		
//		
//		
//		
//		/*!
//		 Draws filled/empty right circles and ellipses.
//		 
//		 @brief
//		 Some applications needs to draw a lot of right primitve shapes.
//		 This class support optimized way to draw circles.
//		 
//		 @classdesign
//		 This is implemented using multiple `RegularPolygonDrawer`s for
//		 each size levels.
//		 */
//		class
//		RegularCircleDrawer
//		{
//			uptr<Server::Program>				_shader		{};
//			
//		public:
//			using	RegularInstance		=	RegularPolygonDrawer::RegularInstance;
//			using	ColoringInstance	=	RegularPolygonDrawer::ColoringInstance;
////				using	RotatingInstance	=	RegularPolygonDrawer::RotatingInstance;
//			
//		public:
//			RegularCircleDrawer(sz const& numberOfSegments);
//			
//			/*!
//			 This draws 2x2 (radius = 1) sized circle at the origin with supplied transform.
//			 */
//			auto	drawInstances(vec<RegularInstance> const& instances) const -> void;
//			auto	drawInstances(vec<ColoringInstance> const& instances) const -> void;
////				auto	drawInstances(vec<RotatingInstance> const& instances) const -> void;
//		};
//		
//		
//		
//		
//		
//		
//		
//		
//	}
//}
//
//EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END
//
