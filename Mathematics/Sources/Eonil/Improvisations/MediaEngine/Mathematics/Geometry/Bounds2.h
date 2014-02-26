//
//  Bounds2.h
//  Mathematics
//
//  Created by Eonil on 5/1/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __Mathematics__Bounds2__
#define __Mathematics__Bounds2__

#include "../Common.h"

#if			EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX
extern "C"
{
#include	<CoreGraphics/CoreGraphics.h>
}
#endif



#include	"Vector.h"
#include	"Matrix.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Mathematics {

	namespace
	Value
	{			
		
		/*!
		 2D Axis Aligned Bounding Box.
		 
		 @discussion	Bounds can be NAN-state by setting all parameters to NAN.
						NAN-state bounds cannot operate anything. An exception will be thrown.
						If some parameter is NAN, that's illegal state, which is also an exception.
		 
		 @note			Take care that you cannot compare NAN state equality.
		 */
		struct
		Bounds2
		{
			Vector2		minimum;
			Vector2		maximum;
			
			/*!
			 Creates null-state. (all-NAN).
			 */
			Bounds2();
			/*!
			 Creates zero-sized bounding box.
			 */
			Bounds2(Scalar const x, Scalar const y);
			Bounds2(Vector2 const minimum, Vector2 const maximum);
			Bounds2(Scalar const minX, Scalar const minY, Scalar const maxX, Scalar const maxY);
			
			bool const		operator==(Bounds2 const& other) const;
			bool const		operator!=(Bounds2 const& other) const;
//				bool const		operator==(decltype(nullptr) const null) const;
//				bool const		operator!=(decltype(nullptr) const null) const;
			
//				Vector2
			
			Vector2 const	center() const;
			Vector2 const	size() const;
			Scalar const	aspectRatio() const;	//!	Width/height.
			Scalar const	width()	const __attribute((deprecated));			//!	@deprecated
			Scalar const	height() const __attribute((deprecated));			//!	@deprecated
			
			bool const		absolute() const;
			bool const		isNaN() const;			//!	Checks all-NAN bounds or not.
			bool const		isEmpty() const;
			bool const		isIntegral() const;
			Bounds2 const	integralBounds2ByRounding() const;
			
			bool const		containsPoint(const Vector2 point) const;
			bool const		intersectsWith(Bounds2 const bounds) const;
			Bounds2 const	intersectionWith(Bounds2 const bounds) const;	//!	Returns null if bounds are not intersects.
			Bounds2 const	boundsWithDisplacementOfEdges(Vector2 const f) const;
			Bounds2 const	boundsWithTransformationByMatrix(Matrix4 const m) const;
			
			
			void			displaceEdges(Vector2 const f);					//!	Move edges along its normal.
			void			displaceEdgesHorizontally(Scalar const f);		//!	Move edges along its normal.
			void			displaceEdgesVertically(Scalar const f);		//!	Move edges along its normal.
			void			transformByMatrix(Matrix4 const m);
			
			
			
			
			
			
			
			
			struct
			Utility
			{
				static Bounds2 const	NaN();		//!	All NaN bounds. This is signaling NaN to mark invalid value.
				static Bounds2 const	zero();		//!	All zero bounds.
				static Bounds2 const	infinity();	//!	All -/+ INFINITE bounds which has infinity volume.
				
				static Bounds2 const	boundsWithPointWithZeroSize(Vector2 const point);
				static Bounds2 const	boundsWithMinimumPointAndSize(Vector2 const point, Vector2 const size);
				static Bounds2 const	boundsWithMaximumPointAndSize(Vector2 const point, Vector2 const size);
				
			};
			
			
			
			//	Compatibility with Cocoa or Cocoa Touch.
#if			EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX
			CGRect const	CGRect() const;
//			static Bounds2 const boundsWithCGRect(CGRect const origin);
#endif
		};
	}
	
	
}}}}

#endif /* defined(__Mathematics__Bounds2__) */
