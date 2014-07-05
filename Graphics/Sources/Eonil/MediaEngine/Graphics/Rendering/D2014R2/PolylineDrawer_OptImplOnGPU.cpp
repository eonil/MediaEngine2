////
////  PolylineDrawer_OptImplOnGPU.cpp
////  Graphics
////
////  Created by Hoon H. on 14/5/24.
////
////
//
//#include "PolylineDrawer_OptImplOnGPU.h"
//#include "CPUTransformTriangleDrawer.h"
//#include "PolylineDrawer_Algorithms.h"
//EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN
//
//
//
//
///*!
// See reference CPU based implementation for details.
// */
//
//
//auto
//PolylineDrawer_OptImplOnGPU::draw(const Matrix4 &transform, const vec<Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::PolylineDrawer_OptImplOnGPU::Instance> &instances, const Scalar &radius, const Vector4 &color) const -> void
//{
//	
//	for (auto const& inst0: instances)
//	{
//		switch (inst0.points.size())
//		{
//			case 0:
//			{
//				//	No drawing.
//				break;
//			}
//			case 1:
//			{
//				EONIL_DEBUG_ASSERT_WITH_MESSAGE(false, "Poly-line point must be at least 2.");
//				break;
//			}
//			default:
//			{
//				/*!
//				 Add caps on both ends.
//				 */
//				
//				Vector3		p0		=	inst0.points.at(0);
//				Vector3		p1		=	inst0.points.at(1);
//				Vector3		p2		=	inst0.points.at(inst0.points.size()-2);
//				Vector3		p3		=	inst0.points.at(inst0.points.size()-1);
//				Vector3		dt_0_1	=	p1 - p0;
//				Vector3		dt_2_3	=	p3 - p2;
//				
//				Instance	copy1	=	{};
//				copy1.points.push_back(p0 - dt_0_1);
//				for (auto const& p: inst0.points)
//				{
//					copy1.points.push_back(p);
//				}
//				copy1.points.push_back(inst0.points.back() + dt_2_3);
//				
//				_draw_one_in_context(transform, copy1, radius, color);
//				break;
//			}
//		}
//	}
//}
//
//
//auto
//PolylineDrawer_OptImplOnGPU::_draw_one_in_context(const Matrix4 &transform, const Rendering::D2014R2::PolylineDrawer_OptImplOnGPU::Instance &polyline, Scalar const& radius, Vector4 const& color) const -> void
//{
//	EONIL_DEBUG_ASSERT(polyline.points.size() >= 4);
//	
//	Size const	num_segs	=	polyline.points.size() - 2 - 1;
//	
//	for (Size i=0; i<num_segs; i++)
//	{
//		auto const&	p0	=	polyline.points.at(i+0);
//		auto const&	p1	=	polyline.points.at(i+1);
//		auto const&	p2	=	polyline.points.at(i+2);
//		auto const&	p3	=	polyline.points.at(i+3);
//		
//		auto const	vo0	=	PolylineDrawer_Algorithms::volumize_single_segment(p0, p1, p2, p3, radius);
//		auto	ts	=	vo0.triangulate();
//		for (auto& t: ts)
//		{
//			for (auto& p: t.points)
//			{
//				p	=	transform.transform(p);
//			}
//		}
//		_tri_drawer.drawTriangleList({ts.begin(), ts.end()}, color);
//	}
//}
//
//
//
//
//
//
//
//
//
//EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END
