////
////  Point.cpp
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 6/3/13.
////
////
//
//#include "Point.h"
//#include "Space.h"
//#include "Debug/Doctor.h"
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		using namespace	Eonil::MediaEngine::Graphics::Debug;
//		
//		
//		
//		Point::Point(Space const& space) : _super(&space), _sub(new Space(Maybe<Point const>::Factory::valueByReferencingValue(this)))
//		{
//			EEGL_ASSERT_WITH_REASON(&space != nullptr, "Super-space shouldn't be null.");
//		}
//		Point::~Point()
//		{
//			delete 	_sub;
//		}
//		
//		Transform const
//		Point::transform() const
//		{
//			return	_t;
//		}
//		
//		void
//		Point::setTransform(const Transform t)
//		{
//			_t	=	t;
//		}
//		
//		Space const&
//		Point::space() const
//		{
//			return	*_super;
//		}
//		Space const&
//		Point::subspace() const
//		{
//			return	*_sub;
//		}
//		Space&
//		Point::subspace()
//		{
//			return	*_sub;
//		}
//	}
//}
