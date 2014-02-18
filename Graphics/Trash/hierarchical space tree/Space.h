////
////  Space.h
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 4/30/13.
////  Copyright (c) 2013 Eonil. All rights reserved.
////
//
//#ifndef __EonilGraphics__Space__
//#define __EonilGraphics__Space__
//
//#include "Transform.h"
//#include "Presentation.h"
//#include "Point.h"
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		class
//		Point;
//		
//		/*!
//		 Owns points.
//		 */
//		class
//		Space
//		{
//		public:
//			Space(Maybe<Point const> const origin = nullptr);
//			
//			Maybe<Point const> const		origin() const;			//	Take care the point's transform is transform in point's container space.
//			
//			std::vector<Point const> const&	points() const;
//			std::vector<Point const>&		points();
////			Point&							spawnPoint();
//			
//		private:
//			Maybe<Point const> const		_op;
//			std::vector<Point const>		_ps;
//		};
//	}
//}
//
//#endif /* defined(__EonilGraphics__Space__) */
