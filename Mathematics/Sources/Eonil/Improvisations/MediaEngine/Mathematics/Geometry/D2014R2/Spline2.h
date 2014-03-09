//
//  Spline2.h
//  Mathematics
//
//  Created by Hoon H. on 3/4/14.
//
//

#ifndef __Mathematics__Spline2__
#define __Mathematics__Spline2__


#include "../../Common.h"
#include "../Vector.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Mathematics {
	
	
	
	
	namespace
	Geometry
	{
		namespace
		D2014R2
		{
			/*!
			 API has no design. Move to regular namespace as soon as it has a nice design or
			 current design is clarified as best.
			 
			 @todo
			 Clarify parameter roles of each parameters ASAP.
			 */
			namespace
			SplineV2
			{
				using namespace	Value;
				
				auto	catmullRom(Vector1 const& p0, Vector1 const& p1, Vector1 const& p2, Vector1 const& p3, Scalar const& time) -> Vector1;
				auto	catmullRom(Vector2 const& p0, Vector2 const& p1, Vector2 const& p2, Vector2 const& p3, Scalar const& time) -> Vector2;
				auto	catmullRom(Vector3 const& p0, Vector3 const& p1, Vector3 const& p2, Vector3 const& p3, Scalar const& time) -> Vector3;
				auto	catmullRom(Vector4 const& p0, Vector4 const& p1, Vector4 const& p2, Vector4 const& p3, Scalar const& time) -> Vector4;
				
				auto	cubic(Vector1 const& p0, Vector1 const& p1, Vector1 const& p2, Vector1 const& p3, Scalar const& time) -> Vector1;
				auto	cubic(Vector2 const& p0, Vector2 const& p1, Vector2 const& p2, Vector2 const& p3, Scalar const& time) -> Vector2;
				auto	cubic(Vector3 const& p0, Vector3 const& p1, Vector3 const& p2, Vector3 const& p3, Scalar const& time) -> Vector3;
				auto	cubic(Vector4 const& p0, Vector4 const& p1, Vector4 const& p2, Vector4 const& p3, Scalar const& time) -> Vector4;
				
				auto	hermite(Vector1 const& p0, Vector1 const& p1, Vector1 const& p2, Vector1 const& p3, Scalar const& time) -> Vector1;
				auto	hermite(Vector2 const& p0, Vector2 const& p1, Vector2 const& p2, Vector2 const& p3, Scalar const& time) -> Vector2;
				auto	hermite(Vector3 const& p0, Vector3 const& p1, Vector3 const& p2, Vector3 const& p3, Scalar const& time) -> Vector3;
				auto	hermite(Vector4 const& p0, Vector4 const& p1, Vector4 const& p2, Vector4 const& p3, Scalar const& time) -> Vector4;
				
				
				
				
				
				
				
				
				
				
				
				
				
			}
		}
	}
	
	
	
	
}}}}

#endif /* defined(__Mathematics__Spline2__) */
