//
//  PolylineDrawer_RefImplOnCPU.cpp
//  Graphics
//
//  Created by Hoon H. on 14/5/23.
//
//

#include "PolylineDrawer_RefImplOnCPU.h"
#include "CPUTransformTriangleDrawer.h"
#include "PolylineDrawer_Algorithms.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN







auto
PolylineDrawer_RefImplOnCPU::draw(Matrix4 const& RSSToNDC, const vec<Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::PolylineDrawer_RefImplOnCPU::AssemblyInstance> &instances, const Scalar &radius, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector4 &color) const -> void
{
	for (auto const& inst0: instances)
	{
		EONIL_DEBUG_ASSERT_WITH_MESSAGE(inst0.passages.size() == 0, "Poly-line point must be at least 2.");

		vec<Vector3>	copy1	=	{};
		copy1.reserve(inst0.passages.size() + 2);
		copy1.push_back(inst0.origination);
		copy1.insert(copy1.end(), inst0.passages.begin(), inst0.passages.end());
		copy1.push_back(inst0.destination);
		_draw_single_stroke_in_context(RSSToNDC, copy1, radius, color);
	}
}
auto
PolylineDrawer_RefImplOnCPU::draw(Matrix4 const& RSSToNDC, const vec<Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::PolylineDrawer_RefImplOnCPU::StrokeInstance> &instances, const Scalar &radius, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector4 &color) const -> void
{
	for (auto const& inst0: instances)
	{
		switch (inst0.points.size())
		{
			case 0:
			{
				//	No drawing.
				break;
			}
			case 1:
			{
				EONIL_DEBUG_ASSERT_WITH_MESSAGE(false, "Poly-line point must be at least 2.");
				break;
			}
//			case 2:
//			{
//				Vector3		p0		=	inst0.points.at(0);
//				Vector3		p1		=	inst0.points.at(1);
//				Vector3		dt_0_1	=	p1 - p0;
//
//				Instance	copy1	=	{};
//				copy1.points.push_back(p0 - dt_0_1);
//				copy1.points.push_back(p0);
//				copy1.points.push_back(p1);
//				copy1.points.push_back(p1 + dt_0_1);
//				
//				_draw_one_in_context(transform, copy1, radius, color);
//				break;
//			}
//			case 3:
//			{
//				Vector3		p0		=	inst0.points.at(0);
//				Vector3		p1		=	inst0.points.at(1);
//				Vector3		p2		=	inst0.points.at(2);
//				Vector3		dt_0_1	=	p1 - p0;
//				Vector3		dt_1_2	=	p2 - p1;
//				
//				Instance	copy1	=	{};
//				copy1.points.push_back(p0 - dt_0_1);
//				copy1.points.push_back(p0);
//				copy1.points.push_back(p1);
//				copy1.points.push_back(p2);
//				copy1.points.push_back(p2 + dt_1_2);
//				
//				_draw_one_in_context(transform, copy1, radius, color);
//				break;
//			}
			default:
			{
				/*!
				 Add caps on both ends.
				 */
				
				Vector3		p0		=	inst0.points.at(0);
				Vector3		p1		=	inst0.points.at(1);
				Vector3		p2		=	inst0.points.at(inst0.points.size()-2);
				Vector3		p3		=	inst0.points.at(inst0.points.size()-1);
				Vector3		dt_0_1	=	p1 - p0;
				Vector3		dt_2_3	=	p3 - p2;
				
				vec<Vector3>	copy1	=	{};
				copy1.push_back(p0 - dt_0_1);
				for (auto const& p: inst0.points)
				{
					copy1.push_back(p);
				}
				copy1.push_back(inst0.points.back() + dt_2_3);
				
				_draw_single_stroke_in_context(RSSToNDC, copy1, radius, color);
				break;

			}
		}
	}
}


/*!
 @param
 points
 Must contain handle points (to adjust ending shape) on each end.
 */
auto
PolylineDrawer_RefImplOnCPU::_draw_single_stroke_in_context(Matrix4 const& RSSToNDC, const vec<Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector3> &points, const Scalar &radius, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector4 &color) const -> void
{
	EONIL_DEBUG_ASSERT(points.size() >= 4);

	
	
	/*!
	 Logic explanation.
	 
	 @code
		 
	    p0                         p3
		 *                         *
		  \                       /
		   \                     /
			\                   /
			 \                 /
			  \               /
			   *-------------*
                  p1             p2
     
		p0            q0           p3
		 *-------------*           *
		  \             \         /
		   \             \       /
			\             \     /
			 \             \   /
			  \             \ /
			   *-------------*
			  p1            p2

		p0          q1             p3
		 *           *-------------*
		  \         /             /
		   \       /             /
			\     /             /
			 \   /             /
			  \ /             /
			   *-------------*
			  p1            p2

	 
		p0                         p3
		 *                         *
		  \                       /
		   \      a0     b2      /
			\     *       *     /
			 \   /         \   /
			  \ /           \ /
			p1 *-------------* p2
			  /               \
			 /                 \
			*                   *
		   a1                   b3
	 
	 @endcode
	 */
	
	Size const	num_segs	=	points.size() - 2 - 1;
	
	for (Size i=0; i<num_segs; i++)
	{
		auto const&	p0	=	points.at(i+0);
		auto const&	p1	=	points.at(i+1);
		auto const&	p2	=	points.at(i+2);
		auto const&	p3	=	points.at(i+3);
		
		auto const	vo0	=	PolylineDrawer_Algorithms::volumize_single_segment(p0, p1, p2, p3, radius);
		auto	ts	=	vo0.triangulate();
		for (auto& t: ts)
		{
			for (auto& p: t.points)
			{
				p	=	RSSToNDC.transform(p);
			}
		}
		_tri_drawer.drawTriangleList({ts.begin(), ts.end()}, color);
	}
}









EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END
