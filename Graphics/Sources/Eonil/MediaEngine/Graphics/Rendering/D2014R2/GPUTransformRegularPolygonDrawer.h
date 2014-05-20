//
//  GPUTransformRegularPolygonDrawer.h
//  Graphics
//
//  Created by Hoon H. on 3/20/14.
//
//

#ifndef __Graphics__GPUTrnasformRegularPolygonDrawer__
#define __Graphics__GPUTrnasformRegularPolygonDrawer__

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
			 Optimized dedicated regular polygon (2D) drawer.
			 
			 @discussion
			 Drawing of irregular polygon lines cost huge when drawing
			 because it needs exrea calculations to make proper geometry.
			 Unlike them, geometry of regular shapes can be solved a lot
			 cheaper.
			 
			 This draws regular circular shape with specificed segmentation.
			 You also can draw N-gon shapes such as triangles or hexagons.
			 
			 @classdesign
			 This object will draw many regular-polygons at once up to 
			 `capacity` number. Maximum capacity number is dependent on 
			 underlying hardware, so it's different over all platforms.
			 
			 If you pass wrong (too big, or too small) capacity number, 
			 then program will panic. It's recommended to use default 
			 number by not passing it.
			 
			 @note
			 This class is written for OpenGL ES 2.0 standard spec with no
			 extentions. That means this need to retain all duplicated 
			 polygon geometries for each instances in capacity. Some extention
			 can reduce this waste greatly. 
			 
				 https://developer.apple.com/library/ios/releasenotes/General/WhatsNewIniOS/Articles/iOS7.html#//apple_ref/doc/uid/TP40013162-SW37
				 https://www.khronos.org/registry/gles/extensions/EXT/EXT_instanced_arrays.txt
			 
			 @todo
			 Add conditional execution path for these extension support.
			 
			 -	`EXT_draw_instanced`
			 -	`GL_EXT_instanced_arrays`
			 
			 */
			class
			GPUTransformRegularPolygonDrawer
			{
				struct	Core;
				
				uptr<Core>	_core_ptr	{};
				
				static auto	_maximumCapacityOfCurrentPlatformForVaryingInstances() -> Size;			//!	Very expensive. (reads back from remote GL server)
				
			public:
				
				/*!
				 @note
				 This structure will be passed to GPU as is,
				 so shouldn't be modified without consideration of GLSL code.
				 */
				struct
				LineVolume
				{
					Scalar			inner		{};
					Scalar			outer		{};
					
					LineVolume() {}
					LineVolume(Scalar inner, Scalar outer) : inner(inner), outer(outer) {}
				};
				
				/*!
				 @note
				 This structure will be passed to GPU as is,
				 so shouldn't be modified without consideration of GLSL code.
				 */
				struct
				UniformInstance
				{
					Vector2			position	{};
				};
				
				/*!
				 @note
				 This structure will be passed to GPU as is,
				 so shouldn't be modified without consideration of GLSL code.
				 */
				struct
				VaryingInstance 
				{
					Vector2			position	{};
					LineVolume		boundary	{};
					Vector4			color		{};
				};
				
			public:
				GPUTransformRegularPolygonDrawer(Size const& segmentation);
				/*!
				 
				 @note
				 OpenGL ES 2.0 doesn't support geometry instancing, so this class will keep duplicated copy
				 of each circles for instancing.
				 
				 This amount of GPU memory will be pre-allocated;
				 
				 -	Vertexes:	4(bytes float) * 2(signed angle + index number) * 2(vertexes for each quad) * (segmentation + 2) * capacity

				 For example, if you 128 capacity of 128 segments will take 266KB.
				 Most of data is duplicated, but we cannot use vertex-indexing due to instance ID.
				 This wastes too much memory if capacity is high, so the capacity has hard limit of 256KB.
				 Instance count can be vary by the segmentation count. If you want just maximum allowed capacity,
				 use default(parameter-less) constructor.
				
				 @todo
				 If the underlying hardware supports geometry instancing, the memory consumption can be reduced
				 greatly.
				 
				 -	Vertexes:	4(bytes float) * 1(signed angle) * 2(vertexes for each quad) * (segmentation + 2)
				 
				 For example, 1KB for any capacity of 128 segments.
				 In this case, we don't need index buffer because indexing almost no data is duplicated.
				 
				 @param	
				 capacity
				 
				 Cannot be larger then maximum capacity (`_maximumCapacityOfCurrentPlatformForVaryingInstances`). I don't recommend to modify this parameter from client code.
				 */
				GPUTransformRegularPolygonDrawer(Size const& segmentation, Size const& capacity);
				~GPUTransformRegularPolygonDrawer();
				
				/*!
				 Performs batched drawing of circles.
				 
				 
				 If instance count < capacity, then everything willl be drawn at once (single draw call).
				 Otherwise, draw call count will be multiplied as much as needed.
				 */
				auto	draw(vec<VaryingInstance> const& instances, Matrix4 const& worldToScreenTransform, DisplayScreenFrame const& frame) const -> void;
				
				
				
			public:
			};
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__GPUTrnasformRegularPolygonDrawer__) */
