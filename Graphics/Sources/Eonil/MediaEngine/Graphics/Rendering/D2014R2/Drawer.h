////
////  Drawer.h
////  Graphics
////
////  Created by Hoon H. on 2/19/14.
////
////
//
//#ifndef __Graphics__Drawer__
//#define __Graphics__Drawer__
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
//			class
//			Geometry
//			{
//				
//			};
//			
//			
//			/*!
//			 Further abstraction of a `Server::ArrayBuffer`.
//			 */
//			class
//			Shape
//			{
//			protected:
//				Size	_starting_offset_in_bytes	{0};
//				Size	_primitive_count			{0};
//				
//				Server::DrawingMode		_drawing_mode;
//				
//			public:
//				
//			};
//			
//			class
//			ShapeInServerMemory : Shape
//			{
//				ptr<Server::ArrayBuffer>			_vtxs{};
//				ptr<Server::ElementArrayBuffer>		_idxs{};
//				
//			};
//			class
//			ShapeInClientMemory : Shape
//			{
//				
//			};
//			
//			
//			/*!
//			 Further abstraction of a `Server::Program`.
//			 */
//			class
//			Drawer
//			{
//				ptr<Server::Program>	_program	{};
//				
//			public:
//				auto	draw(ShapeInServerMemory const& shape) const -> void;
//				auto	draw(ShapeInClientMemory const& shape) const -> void;
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
//#endif /* defined(__Graphics__Drawer__) */
