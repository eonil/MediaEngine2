////
////  CPUTransformRegularPolygonDrawer.h
////  Graphics
////
////  Created by Hoon H. on 3/20/14.
////
////
//
//#ifndef __Graphics__CPUTrnasformRegularPolygonDrawer__
//#define __Graphics__CPUTrnasformRegularPolygonDrawer__
//
//#include "../../Common.h"
//#include "../../Server/Declarations.h"
//
//EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
//	
//	namespace
//	Rendering
//	{
//		namespace
//		D2014R2
//		{
//			using namespace	Server;
//			
//			
//			/*!
//			 Optimized dedicated regular polygon (2D) drawer.
//			 
//			 @discussion
//			 Drawing of irregular polygon lines cost huge when drawing
//			 because it needs exrea calculations to make proper geometry.
//			 Unlike them, geometry of regular shapes can be solved a lot
//			 cheaper.
//			 
//			 This draws regular circular shape with specificed segmentation.
//			 You also can draw N-gon shapes such as triangles or hexagons.
//			 */
//			class
//			CPUTransformRegularPolygonDrawer
//			{
//				struct	Core;
//				
//				uptr<Core>	_core_ptr	{};
//				
//			public:
//				
//				/*!
//				 @note
//				 This structure will be passed to GPU as is,
//				 so shouldn't be modified without consideration of GLSL code.
//				 */
//				struct
//				LineVolume
//				{
//					Scalar			inner		{};
//					Scalar			outer		{};
//					
//					LineVolume() {}
//					LineVolume(Scalar inner, Scalar outer) : inner(inner), outer(outer) {}
//				};
//				
//				/*!
//				 @note
//				 This structure will be passed to GPU as is,
//				 so shouldn't be modified without consideration of GLSL code.
//				 */
//				struct
//				UniformInstance
//				{
//					Vector2			position	{};
//				};
//				
//				/*!
//				 @note
//				 This structure will be passed to GPU as is,
//				 so shouldn't be modified without consideration of GLSL code.
//				 */
//				struct
//				VaryingInstance 
//				{
//					Vector2			position	{};
//					LineVolume		boundary	{};
//					Vector4			color		{};
//				};
//				
//			public:
//				/*!
//				 
//				 @note
//				 OpenGL ES 2.0 doesn't support geometry instancing, so this class will keep duplicated copy
//				 of each circles for instancing.
//				 
//				 This amount of GPU memory will be pre-allocated;
//				 
//				 -	Vertexes:	4(bytes float) * 2(signed angle + index number) * 2(vertexes for each quad) * segmentation
//				 -	Indexes:	2(bytes uint) * 2(indexes for each quad) * (segmentation + 1)
//
//				 For example, if you 128 capacity of 128 segments will take 2.5KB.
//				 */
//				CPUTransformRegularPolygonDrawer(Size const& segmentation);
//				~CPUTransformRegularPolygonDrawer();
//				
//				/*!
//				 If instance count < capacity, then everything willl be drawn at once (single draw call).
//				 Otherwise, draw call count will be multiplied as much as needed.
//				 */
//				auto	draw(vec<VaryingInstance> const& instances, Matrix4 const& worldToScreenTransform, DisplayScreenFrame const& frame) const -> void;
//				
//				
//				
//			public:
//			};
//			
//			
//			
//		}
//	}
//	
//}}}}
//
//#endif /* defined(__Graphics__CPUTrnasformRegularPolygonDrawer__) */
