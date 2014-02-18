////
////  Interpolation.cpp
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 6/14/13.
////
////
//
//#include "Interpolation.h"
//#include <GLKit/GLKit.h>
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		namespace
//		Algorithm
//		{
//			namespace
//			{
//				union
//				CONV4
//				{
//					GLKQuaternion	GLKQ;
//					Quaternion		EEQ;
//					glm::quat		GLMQ;
//					
//					CONV4(GLKQuaternion const q) : GLKQ(q) {}
//					CONV4(Quaternion const q) : EEQ(q) {}
//				}
//				__attribute__((aligned(16)));
//				
//				static_assert(sizeof(CONV4) == sizeof(Scalar) * 4, "");
//			}
//			
//			
//			
////			Scalar const
////			sampleUsingLinearInterpolation(Scalar const a, Scalar const b, Scalar const t)
////			{
//////				return	a + ((b - a) * t);
////				return	a * (1-t) + b * t;		//	Seem to have less error.
////			}
////			
////			
////			
////			Quaternion const
////			sampleUsingSphericalLinearInterpolation(Quaternion const a, Quaternion const b, Scalar const t)
////			{
////				return	CONV4(GLKQuaternionSlerp(CONV4(a).GLKQ, CONV4(a).GLKQ, t)).EEQ;
////			}
////			
////			
////			
////			Scalar const
////			sampleUsingCatmullRomSpline(Scalar const a, Scalar const b, Scalar const c, Scalar const d, Scalar const t)
////			{
////				/*
////				 TODO: Consider matrix form.
////				 
////				 @ref
////				 http://www.stanford.edu/class/cs248/assignments/assignment3.pdf
////				 */
////
//////				return	glm::catmullRom<Scalar>(a, b, c, d, t);
////				
////				Scalar const	t2	=	t * t;
////				Scalar const	t3	=	t2 * t;
////				
////				Scalar const	P0	=	a;
////				Scalar const	P1	=	b;
////				Scalar const	P2	=	c;
////				Scalar const	P3	=	d;
////				
////				return	((P1*2) + (P2-P0) * t + (P0*2 - P1*5 + P2*4 - P3) * t2 + (P1*3 - P0 - P2*3 + P3) * t3) * 0.5f;
////			}
////			
////			
////			Quaternion const
////			sampleUsingSphericalQuadraticInterpolation(Quaternion const a, Quaternion const b, Quaternion const b, Quaternion const d, Scalar const t)
////			{
////				/*!
////				 TODO: Implement this.
////				 http://willperone.net/Code/quaternion.php
////				 */
////							
////		
////				glm::squad(<#const detail::tquat<T> &q1#>, <#const detail::tquat<T> &q2#>, <#const detail::tquat<T> &s1#>, <#const detail::tquat<T> &s2#>, <#const T &h#>)
////			}
//		}
//	}
//}
//
