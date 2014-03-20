//
//  CPUTransformUniformPolylineImmediateDrawer.h
//  Graphics
//
//  Created by Hoon H. on 3/20/14.
//
//

#ifndef __Graphics__CPUTransformUniformPolylineImmediateDrawer__
#define __Graphics__CPUTransformUniformPolylineImmediateDrawer__

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
			 Draws filled, uniform solid poly-lines with color.
			 
			 @classdesign
			 This is designed for final production rendering.
			 This is highly optimized only for line drawing.
			 
			 
			 
			 @discussion
			 If you want dotted or dashed style polylines, then 
			 you have to define all each parts as separated 
			 segments.
			 
			 If you want any kind of varying lines, you have to
			 use another class, because this class is not 
			 optimized for that job.
			 */
			class
			CPUTransformUniformPolylineImmediateDrawer
			{
				struct	Core;
				
				uptr<Core>				_core_ptr	{};
				
			public:
				struct
				Stroke
				{
					vec<Vector3>		vertexes	{};
				};
				
				struct
				Drawing
				{
					vec<Stroke>			strokes		{};
					Vector4				color		{};
					Scalar				radius		{};
				};
				
//				/*!
//				 Defines how dashed lines will be drawn.
//				 If you want to draw a solid line, set
//				 this to `{+INFINITY,0}`. Otherwise, any
//				 INFINITY or 0 will not be allowed.
//				 */
//				struct
//				Stepping
//				{
//					Scalar	fillLength		{+INFINITY};
//					Scalar	emptyLength		{0};
//				};
				
			public:
				CPUTransformUniformPolylineImmediateDrawer();
				~CPUTransformUniformPolylineImmediateDrawer();
				
				auto	draw(Drawing const& data, Matrix4 const& worldToScreenTransform, DisplayScreenFrame const& frame) const -> void;
			};
			
			
			
			
			
			
			
			
			
			
			
			
			
//			/*!
//			 If you need to draw identical lines multiple times, this will 
//			 increase performance by saving transfering cost.
//			 
//			 This stores line data in GPU memory, modifying it will be *very*
//			 expensive.
//			 */
//			class
//			PolylineCachingDrawer
//			{
//			public:
//				using	GenericInstance	=	PolylineDrawer::GenericInstance;
//			public:
//				PolylineCachingDrawer();
////				/*!
////				 @param	segmentationHint
////				 GPU buffer will be aligned by this size to eliminate fragmentation.
////				 */
////				PolylineCachingDrawer(Size const& segmentationHint);
//				~PolylineCachingDrawer();
//				
//				
//				auto	insertLines(vec<PolylineDrawing::UniformInstance> const& lines) -> void;
//				auto	eraseLines(vec<PolylineDrawing::UniformInstance> const& lines) -> void;
//				
//				auto	resetContent(
//				auto	draw() const -> void;
//				
//				
//			private:
//				vec<GenericInstance>	_insts{};
//			};
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__CPUTransformUniformPolylineImmediateDrawer__) */
