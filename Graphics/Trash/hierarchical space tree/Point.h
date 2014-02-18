////
////  Point.h
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 6/3/13.
////
////
//
//#ifndef __EonilGraphics__Point__
//#define __EonilGraphics__Point__
//
//#include "Transform.h"
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		class
//		Space;
//	
//		/*!
//		 Strictly tree structure.
//		 
//		 Owns sub-space.
//		 Owned objects are managed by this objects.
//		 */
//		class
//		Point
//		{
//		public:
//			Point(Space const& space);
//			~Point();
//			
//			Transform const		transform() const;
//			void				setTransform(Transform const t);
//			
//			Space const&		space() const;				//	Container space.
//			Space const&		subspace() const;			//	Derived space.
//			Space&				subspace();
//			
//		private:
//			Transform			_t;
//			Space const*		_super;
//			Space*				_sub;
//		};
//	}
//}
//
//#endif /* defined(__EonilGraphics__Point__) */
