//
//  RegularPolygonDrawer.h
//  Graphics
//
//  Created by Hoon H. on 2/17/14.
//
//

#ifndef __Graphics__RegularPolygonDrawer__
#define __Graphics__RegularPolygonDrawer__

#include "../../Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{
			
			
			
			
			/*!
			 Draws filled/empty regular polygons and ellipses.
			 
			 @brief
			 Some applications needs to draw a lot of regular primitve shapes.
			 This class support optimized way to draw them.
			 */
			class
			RegularPolygonDrawer
			{
				uptr<Server::Program>				_shader		{};
				
			public:
				struct
				RegularInstance
				{
					Vector3			translation	{};
					Scalar			scale		{};
				};
				
				struct
				ColoringInstance : RegularInstance
				{
					Vector4			color		{};
				};
				
//				struct
//				RotatingInstance : ColoringInstance
//				{
////					Quaternion		rotation	{};
//				};
				
			public:
				RegularPolygonDrawer(Size const& numberOfSegments);
				
				/*!
				 This draws 2x2 (radius = 1) sized circle at the origin with supplied transform.
				 */
				auto	drawInstances(vec<RegularInstance> const& instances) const -> void;
				auto	drawInstances(vec<ColoringInstance> const& instances) const -> void;
//				auto	drawInstances(vec<RotatingInstance> const& instances) const -> void;
			};
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__RegularPolygonDrawer__) */
