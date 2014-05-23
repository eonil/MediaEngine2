//
//  PolylineDrawer_RefImplOnCPU.cpp
//  Graphics
//
//  Created by Hoon H. on 14/5/23.
//
//

#include "PolylineDrawer_RefImplOnCPU.h"
#include "CPUTransformTriangleDrawer.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN




namespace
{
	using	point	=	Vector3;
	
	
	struct
	VolumeQuad
	{
		struct
		SteppingEdge
		{
			point		left	=	{};
			point		right	=	{};
		};
		
		SteppingEdge	origination	=	{};
		SteppingEdge	destination	=	{};
		
		////
		
		auto
		triangulate() const -> std::array<CPUTransformTriangleDrawer::Triangle, 2>
		{
			decltype(triangulate())	l0	=	{};
			l0.at(0).points.at(0)	=	origination.left;
			l0.at(0).points.at(1)	=	origination.right;
			l0.at(0).points.at(2)	=	destination.right;
			l0.at(1).points.at(0)	=	destination.right;
			l0.at(1).points.at(1)	=	destination.left;
			l0.at(1).points.at(2)	=	origination.left;
			return	l0;
		}
	};
	
	
	
	
	
	
	
	static inline auto
	resolve_volume_displacement_vector_length(Vector3 const& n1, Vector3 const& n3, Scalar const y) -> Scalar
	{
		/*!
		 @code
		 
			 c
			 *
			 |\
			 | \
		  y  |  \  d
			 |   \
			 |    \
			 |     \
			 *------*
			 a      b
		 
		 
		 vector	n1	=	normalize(a~b)
		 vector	n3	=	normalize(b~c)
		 angle	a3	=	a~b~c
		 length	y	=	a~c
		 
		 sine(a3)	=	y / d
		 d			=	y / sine(a3)
		 
		 */
		auto const	a3	=	Vector3::Utility::angleBetweenVectorsOnPlane(-n1, n3, {0,0,1});
		auto const	d	=	y / Trigonometry::sine(a3);
		
		return		d;
	}
	
	
	
	static inline auto
	perpendicular_2d(Vector3 const& a) -> Vector3
	{
//		Matrix4 const	m1	=	Matrix4::Utility::rotationWithAxisAngle(AxisAngle({0,0,1}, M_PI_2));
//		Vector3 const	b	=	m1.transform(a);
//		return	b;
		return	{-a.y, a.x, a.z};
	}
	
	
	static inline auto
	resolve_stepping_edge(point const& p0, point const& p1, point const& p2, Scalar const& radius) -> VolumeQuad::SteppingEdge
	{
		EONIL_DEBUG_ASSERT(p0 != p1);
		EONIL_DEBUG_ASSERT(p1 != p2);
		EONIL_DEBUG_ASSERT(p2 != p0);

		/*!
		 
             p4             p2
              *-------------*
             /             /  v2
			*-------------*
	       p0            p1
                  v1
		 
		 v1	=	p0~p1
		 v2	=	p1~p2
		 
					 n2
          *           *-----------*
           \         / \         /
            \ d3    /   \       /
             \     /     \     /
              \   /       \   /
		       \ /         \ /
			    *-----------*
              (0,0)         n1
		 
		 n1	=	p0~p1 (normalized)
		 n2	=	p1~p2 (normalized)
		 d3	=	n1~n2 (NOT normalized!)
		 n3	=	n1~n2 (normalized)
		 
								p2
							    *
                               /
				      q0      /
                       *     /
                        \   /
                         \ /
		 p0 *-------------* p1
                           \
                            \
							 *
							 q1
         
		 v3	=	p1~q0
		 n3	=	p1~q0 (normalized)
		 
		 The line `v0~v1` builds a line volume stepping edge.
		 
		 
		 
		 */
		
		auto const	v1	=	p1 - p0;
		auto const	v2	=	p2 - p1;
		auto const	n1	=	v1.norm();
		auto const	n2	=	v2.norm();
		
		auto const	d3	=	n2 - n1;
		auto const	par	=	almost_equals(d3, {0,0,0});		//	straight line...
		auto const	n3	=	(par ? perpendicular_2d(v1) : d3).norm();
		
		auto const	dtl	=	resolve_volume_displacement_vector_length(n1, n3, radius);
		auto const	d0	=	n3 * dtl;
		auto const	d1	=	-n3 * dtl;
		auto const	q0	=	p1 + d0;
		auto const	q1	=	p1 + d1;

		VolumeQuad::SteppingEdge	e0	=	{};
		e0.left			=	q0;
		e0.right		=	q1;
		return	e0;
	}
	
	
	
	
	
	
	
	/*!
	 Where you draw a line semgnet `p1~p2`,
	 
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
     
	 @endcode
	 
	 p0 = previous point. handle for p1.
	 p1 = starting point.
	 p2 = ending point.
	 p3 = next point. handle for p2.
	 
	 */
	static inline auto
	volumize_single_segment(point const& p0, point const& p1, point const& p2, point const& p3, Scalar const& radius) -> VolumeQuad
	{
		auto const	se0	=	resolve_stepping_edge(p0, p1, p2, radius);
		auto const	se1	=	resolve_stepping_edge(p1, p2, p3, radius);
		
		////
		
		VolumeQuad	result	=	{};
		result.origination	=	se0;
		result.destination	=	se1;
		return	result;
	}
	
	
}



auto
PolylineDrawer_RefImplOnCPU::draw(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Matrix4 &transform, const vec<Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::PolylineDrawer_RefImplOnCPU::Instance> &instances, const Scalar &radius, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector4 &color) const -> void
{
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
			case 2:
			{
				Vector3		p0		=	inst0.points.at(0);
				Vector3		p1		=	inst0.points.at(1);
				Vector3		dt_0_1	=	p1 - p0;

				Instance	copy1	=	{};
				copy1.points.push_back(p0 - dt_0_1);
				copy1.points.push_back(p0);
				copy1.points.push_back(p1);
				copy1.points.push_back(p1 + dt_0_1);
				_draw_one_in_context(transform, copy1, radius, color);
				break;
			}
			case 3:
			{
				Vector3		p0		=	inst0.points.at(0);
				Vector3		p1		=	inst0.points.at(1);
				Vector3		p2		=	inst0.points.at(2);
				Vector3		dt_0_1	=	p1 - p0;
				Vector3		dt_1_2	=	p2 - p1;
				
				Instance	copy1	=	{};
				copy1.points.push_back(p0 - dt_0_1);
				copy1.points.push_back(p0);
				copy1.points.push_back(p1);
				copy1.points.push_back(p2);
				copy1.points.push_back(p2 + dt_1_2);
				_draw_one_in_context(transform, copy1, radius, color);
				break;
			}
			default:
			{
				_draw_one_in_context(transform, inst0, radius, color);
				break;
			}
		}
	}
}


auto
PolylineDrawer_RefImplOnCPU::_draw_one_in_context(const Matrix4 &transform, const Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::PolylineDrawer_RefImplOnCPU::Instance &polyline, Scalar const& radius, Vector4 const& color) const -> void
{
	EONIL_DEBUG_ASSERT(polyline.points.size() >= 4);
	
	Size const	num_segs	=	polyline.points.size() - 2 - 1;
	
	for (Size i=0; i<num_segs; i++)
	{
		auto const&	p0	=	polyline.points.at(i+0);
		auto const&	p1	=	polyline.points.at(i+1);
		auto const&	p2	=	polyline.points.at(i+2);
		auto const&	p3	=	polyline.points.at(i+3);
		
		auto const	vo0	=	volumize_single_segment(p0, p1, p2, p3, radius);
		auto	ts	=	vo0.triangulate();
		for (auto& t: ts)
		{
			for (auto& p: t.points)
			{
				p	=	transform.transform(p);
			}
		}
		_tri_drawer.drawTriangleList({ts.begin(), ts.end()}, color);
	}
}









EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END
