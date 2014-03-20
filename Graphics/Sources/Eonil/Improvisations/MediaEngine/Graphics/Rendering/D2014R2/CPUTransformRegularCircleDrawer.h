//
//  CPUTransformRegularCircleDrawer.h
//  Graphics
//
//  Created by Hoon H. on 3/20/14.
//
//

#ifndef __Graphics__CPUTransformRegularCircleDrawer__
#define __Graphics__CPUTransformRegularCircleDrawer__

#include "../../Common.h"
#include "../../Server/Declarations.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{
			using namespace	Server;
			
			
			/*!
			 Optimized dedicated circle (2D) drawer.
			 
			 @discussion
			 Drawing of irregular polygon lines cost huge when drawing
			 because it needs exrea calculations to make proper geometry.
			 Unlike them, geometry of regular shapes can be solved a lot 
			 cheaper.
			 
			 This draws regular circular shape with specificed segmentation.
			 You also can draw N-gon shapes such as triangles or hexagons.
			 */
			class
			CPUTransformRegularCircleDrawer
			{
			public:
				struct
				Instance
				{
					Size	segments		{};
					Scalar	radius			{};
					Scalar	thickness		{};		//!	Half size rom the shape center.
				};
				
			public:
				auto	draw(vec<Instance> const& instances, Matrix4 const& transform) const -> void;
			};
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__CPUTransformRegularCircleDrawer__) */
