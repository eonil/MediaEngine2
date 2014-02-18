////
////  Spline.cpp
////  Mathematics
////
////  Created by Hoon Hwangbo on 6/14/13.
////
////
//
//#include "Spline.h"
//
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		namespace
//		Value
//		{
//			
//			/*!
//			 TODO: Consider matrix form.
//			 
//			 @ref
//			 http://www.stanford.edu/class/cs248/assignments/assignment3.pdf
//			 */
//			Scalar const
//			CatmullRomSpline::sampleAtTime(const Scalar t) const
//			{
//				Scalar const	t2	=	t * t;
//				Scalar const	t3	=	t2 * t;
//				
//				Scalar const	P0	=	values[0];
//				Scalar const	P1	=	values[1];
//				Scalar const	P2	=	values[2];
//				Scalar const	P3	=	values[3];
//				
//				return	((P1*2) + (P2-P0) * t + (P0*2 - P1*5 + P2*4 - P3) * t2 + (P1*3 - P0 - P2*3 + P3) * t3) * 0.5f;
//			}
//			
//			
//			//
//			//			struct
//			//			CatmullRomSpline1 : public CatmullRomSpline<1>
//			//			{
//			//			};
//			//			struct
//			//			CatmullRomSpline2 : public CatmullRomSpline<2>
//			//			{
//			//			};
//			//			struct
//			//			CatmullRomSpline3 : public CatmullRomSpline<3>
//			//			{
//			//			};
//			//			struct
//			//			CatmullRomSpline4 : public CatmullRomSpline<4>
//			//			{
//			//			};
//		}
//	}
//}
//
