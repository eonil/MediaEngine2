//
//  PolylineDrawer_Algorithms.h
//  Graphics
//
//  Created by Hoon H. on 14/5/24.
//
//

#pragma once
#include "../RenderingCommon.h"
#include "CPUTransformTriangleDrawer.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN





class
PolylineDrawer_Algorithms final
{
public:

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
	
	
};






EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END

