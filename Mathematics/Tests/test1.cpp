//
//  test1.cpp
//  Mathematics
//
//  Created by Hoon H. on 14/5/23.
//
//

#include "test1.h"
#include "Exceptions.h"
using namespace Eonil::Improvisations::MediaEngine::Mathematics;
using namespace Eonil::Improvisations::MediaEngine::Mathematics::Debugging;
using namespace Eonil::Improvisations::MediaEngine::Mathematics::Trigonometry;
using namespace Eonil::Improvisations::MediaEngine::Mathematics::Geometry;


namespace
{
	static inline auto
	test_assert(bool cond) -> void
	{
		if (not cond)
		{
			std::terminate();
		}
	}
	
	static inline auto
	test_assert_always_error(std::function<void(void)> const& proc) -> void
	{
		bool	ok	=	false;
		try
		{
			proc();
		}
		catch(Error const&)
		{
			ok	=	true;
		}
		
		test_assert(ok);
	}
	static inline auto
	test_assert_always_halt(std::function<void(void)> const& proc) -> void
	{
		bool	ok	=	false;
		try
		{
			proc();
		}
		catch(Halt const&)
		{
			ok	=	true;
		}
		
		test_assert(ok);
	}
}

auto
test1() -> void
{
//	{
//		Scalar	a1	=	NAN;
//		Scalar	a2	=	0;
//		test_assert(Doctor::isNaN(a1));
//		test_assert(not Doctor::isNaN(a2));
//	}
//	{
//		Vector4	a1	=	{0,0,0,NAN};
//		Vector4	a2	=	{0,0,0,0};
//		test_assert(Doctor::isNaN(a1));
//		test_assert(not Doctor::isNaN(a2));
//	}
	
	{
		Vector4	a1	=	{0,0,0,0};
		test_assert_always_halt([&](){ a1.norm(); });
	}
	{
		test_assert_always_error([](){ Vector3::Utility::angleBetweenVectorsOnPlane({1,0,0}, {1,0,0}, {0,0,0}); });
		test_assert_always_error([](){ Vector3::Utility::angleBetweenVectorsOnPlane({0,0,0}, {1,0,0}, {1,0,0}); });
		test_assert_always_error([](){ Vector3::Utility::angleBetweenVectorsOnPlane({1,0,0}, {0,0,0}, {1,0,0}); });
	}
	
	//	Angles.
	{
		/*
		 No need to calculate magnitude stuffs if the vectors are normalized.
		 */
		{
			Vector3	v1	=	{+1,0,0};
			Vector3	v2	=	Vector3{+1,+1,0}.norm();
			Scalar	dot	=	Vector3::Utility::dotProductionOfVectors(v1, v2);
			Scalar	a3	=	std::acos(dot);
			Scalar	a4	=	Vector3::Utility::angleBetweenVectors(v1, v2);
			Scalar	a5	=	Vector3::Utility::angleBetweenVectorsOnPlane(v1, v2, {0,0,1});
			test_assert(almost_equals(dot, 0.70710));
			test_assert(almost_equals(dot, -cosine(M_PI_4*3)));
			test_assert(almost_equals(a3, M_PI_4));
			test_assert(almost_equals(a3, a4));
			test_assert(almost_equals(a3, a5));
		}
		{
			Vector3	v1	=	{+1,0,0};
			Vector3	v2	=	{0,+1,0};
			Scalar	dot	=	Vector3::Utility::dotProductionOfVectors(v1, v2);
			Scalar	a3	=	std::acos(dot);
			Scalar	a4	=	Vector3::Utility::angleBetweenVectors(v1, v2);
			Scalar	a5	=	Vector3::Utility::angleBetweenVectorsOnPlane(v1, v2, {0,0,1});
			test_assert(almost_equals(dot, 0));
			test_assert(almost_equals(a3, M_PI_2));
			test_assert(almost_equals(a3, a4));
			test_assert(almost_equals(a3, a5));
		}
		{
			Vector3	v1	=	{+1,0,0};
			Vector3	v2	=	Vector3{-1,+1,0}.norm();
			Scalar	dot	=	Vector3::Utility::dotProductionOfVectors(v1, v2);
			Scalar	a3	=	std::acos(dot);
			Scalar	a4	=	Vector3::Utility::angleBetweenVectors(v1, v2);
			Scalar	a5	=	Vector3::Utility::angleBetweenVectorsOnPlane(v1, v2, {0,0,1});
			test_assert(almost_equals(dot, -0.70710));
			test_assert(almost_equals(dot, -cosine(M_PI_4)));
			test_assert(almost_equals(a3, M_PI_4*3));
			test_assert(almost_equals(a3, a4));
			test_assert(almost_equals(a3, a5));
		}
		{
			Vector3	v1	=	{+1,0,0};
			Vector3	v2	=	{-1,0,0};
			Scalar	dot	=	Vector3::Utility::dotProductionOfVectors(v1, v2);
			Scalar	a3	=	std::acos(dot);
			Scalar	a4	=	Vector3::Utility::angleBetweenVectors(v1, v2);
			Scalar	a5	=	Vector3::Utility::angleBetweenVectorsOnPlane(v1, v2, {0,0,1});
			test_assert(almost_equals(dot, -1));
			test_assert(almost_equals(a3, M_PI));
			test_assert(almost_equals(a3, a4));
			test_assert(almost_equals(a3, a5));
		}
		
		
		
		{
			Vector3	v1	=	{-1,0,0};
			Vector3	v2	=	{+1,0,0};
			Scalar	dot	=	Vector3::Utility::dotProductionOfVectors(v1, v2);
			Scalar	a3	=	std::acos(dot);
			Scalar	a4	=	Vector3::Utility::angleBetweenVectors(v1, v2);
			Scalar	a5	=	Vector3::Utility::angleBetweenVectorsOnPlane(v1, v2, {0,0,1});
			test_assert(almost_equals(dot, -1));
			test_assert(almost_equals(a3, M_PI));
			test_assert(almost_equals(a3, a4));
			test_assert(almost_equals(a3, a5));
		}
		{
			Vector3	v1	=	{+1,0,0};
			Vector3	v2	=	{0,-1,0};
			Scalar	dot	=	Vector3::Utility::dotProductionOfVectors(v1, v2);
			Scalar	a3	=	std::acos(dot);
			Scalar	a4	=	Vector3::Utility::angleBetweenVectors(v1, v2);
			Scalar	a5	=	Vector3::Utility::angleBetweenVectorsOnPlane(v1, v2, {0,0,1});
			test_assert(almost_equals(dot, 0));
			test_assert(almost_equals(a3, M_PI_2));
			test_assert(almost_equals(a3, a4));
			test_assert(almost_equals(-a3, a5));
		}
	}
//	{
//		Vector3	v1	=	{-1,0,0};
//		Vector3	v2	=	{+1,0,0};
//		Scalar	a3	=	Vector3::Utility::angleBetweenVectorsOnPlane(v1, v2, {0,0,1});
//		test_assert(almost_equals(a3, M_PI));
//	}
	{
		Matrix4	m1	=	Matrix4::Utility::rotationWithAxisAngle(AxisAngle({0,0,1}, M_PI_2));
		Vector3	v1	=	{0,1,0};
		Vector3	v2	=	m1.transform(v1);
		Vector3	v3	=	{-1,0,0};
		Scalar	s1	=	(v3 - v2).length();
		test_assert(s1 < 0.001);
	}
}










