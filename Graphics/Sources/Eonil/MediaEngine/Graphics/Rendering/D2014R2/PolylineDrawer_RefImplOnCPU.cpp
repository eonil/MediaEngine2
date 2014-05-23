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
	resolve_volume_displacement_vector_length(Vector3 const& v1, Vector3 const& v2, Scalar const radius) -> Scalar
	{
		/*!
		 @code
		 
			 c
			 *
			 |\
			 | \
		  r  |  \  d
			 |   \
			 |    \
			 |     \
			 *------*
			 a      b
		 
		 
		 vector	v1	=	a~b
		 vector	v2	=	b~c
		 angle	a3	=	a~b~c
		 length	r	=	a~c
		 
		 sine(a1)	=	(r / d)
		 d			=	r / sine(a1)
		 
		 */
		auto const	a3	=	Vector3::Utility::angleBetweenVectorsOnPlane(v1, v2, {0,0,1});
		auto const	d	=	radius / std::sin(a3);
		
		return	d;
	}
	
	
	
	
	static inline auto
	resolve_stepping_edge(point const& p0, point const& p1, point const& p2, Scalar const& radius) -> VolumeQuad::SteppingEdge
	{
		/*!
		 
                 p4             p2
                  *-------------*
                 /             /
                /             /
               /             /  v2
              /             /
		     /             /
			*-------------*
	       p0            p1
                  v1
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
         
		 The line `v0~v1` builds a line volume stepping edge.
		 */
		
		auto const	v1	=	p1 - p0;
		auto const	v2	=	p2 - p1;
		auto const	a3	=	Vector3::Utility::angleBetweenVectorsOnPlane(v1, v2, {0,0,1});
		auto const	a4	=	a3/Scalar(2);
		
		auto const	m1	=	Matrix4::Utility::rotationWithAxisAngle(AxisAngle({0,0,1}, a4));
		auto const	dtl	=	resolve_volume_displacement_vector_length(v1, v2, radius);
		auto const	n0	=	m1.transform(-v2).norm();
		auto const	d0	=	n0 * dtl;
		auto const	d1	=	-n0 * dtl;
		auto const	q0	=	p1 + d0;
		auto const	q1	=	p1 + d1;

		VolumeQuad::SteppingEdge	e0	=	{};
		e0.left			=	q0;
		e0.right		=	q1;
		return	e0;
		
//		EONIL_DEBUG_ASSERT(p0 != p1);
//		EONIL_DEBUG_ASSERT(p1 != p2);
//		EONIL_DEBUG_ASSERT(p2 != p0);
//		
//		Matrix4 const	r0	=	Matrix4::Utility::rotationWithAxisAngle(AxisAngle({0,0,1}, M_PI_2));
//		
//		/*!
//		 
//                 p4             p2
//                  *-------------*
//                 /             /
//                /             /
//               /             /
//              /             /
//		     /             /
//			*-------------*
//	       p0            p1
//
//								p2
//							    *
//                               /
//				      v0      /
//                       *     /
//                        \   /
//                         \ /
//		 p0 *-------------* p1
//                           \
//                            \
//							 *
//							 v1
//         
//		 The line `v0~v1` builds a line volume stepping edge.
//		 */
//		
//		auto const	dt_1_2	=	p2 - p1;
//		auto const	p4		=	p0 + dt_1_2;
//		auto const	dt_1_4	=	p4 - p1;
//		
//		auto const	displacement_length	=	resolve_volume_displacement_vector_length(dt_1_2, dt_1_4, radius);
//
//		
//		auto const	is_para	=	dt_1_4.lengthSquare() == 0;
//		auto const	n0		=	is_para ? r0.transform(dt_1_2).norm() : dt_1_4.norm();
//		auto const	disp_l	=	n0 * radius;
//		auto const	v0		=	p1 + disp_l;
//		auto const	v1		=	p1 - disp_l;
//		
//		////
//		
//		VolumeQuad::SteppingEdge	result	=	{};
//		result.left		=	v0;
//		result.right	=	v1;
//		return	result;
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
	
	
	
//	static inline auto
//	transform_all(vec<PolylineDrawer_RefImplOnCPU::Instance> const instances)
	
}



auto
PolylineDrawer_RefImplOnCPU::drawInNDCSpace(const vec<Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::PolylineDrawer_RefImplOnCPU::Instance> &instances, const Scalar &radius, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector4 &color) const -> void
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
				_draw_one_in_context(copy1, radius, color);
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
				_draw_one_in_context(copy1, radius, color);
				break;
			}
			default:
			{
				_draw_one_in_context(inst0, radius, color);
				break;
			}
		}
	}
}


auto
PolylineDrawer_RefImplOnCPU::_draw_one_in_context(const Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::PolylineDrawer_RefImplOnCPU::Instance &polyline, Scalar const& radius, Vector4 const& color) const -> void
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
		auto const	tri	=	vo0.triangulate();
		_tri_drawer.drawTriangleList({tri.begin(), tri.end()}, color);
	}
}









EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END
