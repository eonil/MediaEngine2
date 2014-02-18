////
////  Spline.h
////  Mathematics
////
////  Created by Hoon Hwangbo on 6/14/13.
////
////
//
//#ifndef __Mathematics__Spline__
//#define __Mathematics__Spline__
//
//
//#include "../Common.h"
//#include "Vector.h"
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
////			namespace
////			{
////				template<Size const N> struct SampleTypeResolver {};
////				template<> struct SampleTypeResolver<1> { using Type = Scalar; };
////				template<> struct SampleTypeResolver<2> { using Type = Vector2; };
////				template<> struct SampleTypeResolver<3> { using Type = Vector3; };
////				template<> struct SampleTypeResolver<4> { using Type = Vector4; };
////				
////			}
//			
////			template<Size const C>
//			
//			struct
//			CatmullRomSpline
//			{
////				static_assert(C >= 1 and C <= 4, "");
//				//				static_assert((C == 1 and std::is_same<V, Scalar>::value) or C != 1, "If componet count is `1`, sample type must be `Scalar`.");
//				//				static_assert((C == 2 and std::is_same<V, Vector2>::value) or C != 2, "If componet count is `2`, sample type must be `Vector2`.");
//				//				static_assert((C == 3 and std::is_same<V, Vector3>::value) or C != 3, "If componet count is `3`, sample type must be `Vector3`.");
//				//				static_assert((C == 4 and std::is_same<V, Vector4>::value) or C != 4, "If componet count is `4`, sample type must be `Vector4`.");
//				
//				union
//				{
//					struct
//					{
//						Scalar	a, b, c, d;
//					};
//					struct
//					{
//						Scalar	beginHandle;
//						Scalar	beginPoint;
//						Scalar	endPoint;
//						Scalar	endHandle;
//					};
//					Scalar	values[4];
//				};
//				
//				Scalar const		sampleAtTime(Scalar const time) const;
//			};
//			
//			
//		}
//	}
//}
//
//
//
//#endif /* defined(__Mathematics__Spline__) */
