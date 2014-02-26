//
//  CPUTransformLineDrawer.h
//  Graphics
//
//  Created by Hoon H. on 2/22/14.
//
//

#ifndef __Graphics__CPUTransformLineDrawer__
#define __Graphics__CPUTransformLineDrawer__

#include "../../Common.h"
#include "../../Server/Machinery/VertexAttributeChannel.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{
			using namespace	Server;
			
			
			/*!
			 This is mainly designed for debuggin information overlay.
			 Doesn't fit to final product rendering.
			 */
			class
			CPUTransformLineDrawer
			{
				uptr<Program>	_program_ptr		{nullptr};
				Size			_transform_idx	{0};
				
			public:
				struct
				Point
				{
					Vector4		location	{};		//	`w` must be always 1.
					Vector4		color		{};
					
					Point() {}
					Point(Vector3 const& location, Vector4 const& color) : location(location, 1), color(color) {}
					Point(Vector4 const& location, Vector4 const& color) : location(location), color(color) {}
				};
				struct
				Instance
				{
					Point		origination	{};
					Point		destination	{};
					
					Instance() {}
					Instance(Point const& origination, Point const& destination) : origination(origination), destination(destination) {}
				};
				
			public:
				CPUTransformLineDrawer();
				~CPUTransformLineDrawer();
				
				/*!
				 @param	instances
				 All points must be placed in the world space.
				 
				 @param	worldToScreenTransform		
				 This must be a whole transform from world to final screen (NDC).
				 Take care that final destination space is NDC, not RSS.
				 */
				auto	drawInstances(vec<Instance> const& instances, Matrix4 const& worldToScreenTransform, DisplayScreenFrame const& frame) const -> void;
			};
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__CPUTransformLineDrawer__) */
