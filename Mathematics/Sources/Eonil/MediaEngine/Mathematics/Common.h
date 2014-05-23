//
//  Common.h
//  Mathematics
//
//  Created by Hoon H. on 2/9/14.
//
//

#pragma once

#include	<Eonil/Improvisations/CommonUtility/CommonUtility.h>
#include	<Eonil/MediaEngine/Foundation.h>

#define	EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUG_MODE					EONIL_MEDIA_ENGINE_DEBUG_MODE
#define	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_MODE			EONIL_MEDIA_ENGINE_DEBUG_MODE

#include	<Eonil/CommonRealtimeGameAlgorithms.h>

#define	EONIL_MEDIA_ENGINE_MATHEMATICS_NAMESPACE_BEGIN				namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Mathematics {
#define	EONIL_MEDIA_ENGINE_MATHEMATICS_NAMESPACE_END				} } } }

#define	EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_BEGIN	namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Mathematics { namespace Debugging {
#define	EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_END		} } } } }

#define	EONIL_MEDIA_ENGINE_MATHEMATICS_TRIGONOMETRY_NAMESPACE_BEGIN	namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Mathematics { namespace Trigonometry {
#define	EONIL_MEDIA_ENGINE_MATHEMATICS_TRIGONOMETRY_NAMESPACE_END	} } } } }

#define	EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN		namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Mathematics { namespace Geometry {
#define	EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END		} } } } }





EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_BEGIN
struct	Doctor;
EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_END

EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN
using namespace	Eonil::Improvisations::CommonUtility;
using namespace	Eonil::Improvisations::MediaEngine::Foundation;
using namespace	Eonil::Improvisations::MediaEngine::Foundation::D2014R1;
/*!
 Currently, the type of scalar is defined as 32-bit float,
 but it's not fixed to 32-bit float, and can be changed later.
 Do not assume `Scalar` to be `float_t`, and always use `Scalar`.
 */
using	Scalar	=	float_t;
using	Vector1	=	Scalar;
struct	Vector2;
struct	Vector3;
struct	Vector4;
struct	Quaternion;
struct	AxisAngle;
struct	Matrix4;
struct	Bounds2;
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END








#if				EONIL_MEDIA_ENGINE_DEBUG_MODE
#	define		EONIL_MEDIA_ENGINE_MATH_ASSERT(condexpr)							Eonil::Improvisations::MediaEngine::Mathematics::Debugging::Doctor::assertWithReason(condexpr);
#	define		EONIL_MEDIA_ENGINE_MATH_ASSERT_WITH_REASON(condexpr,reason)			Eonil::Improvisations::MediaEngine::Mathematics::Debugging::Doctor::assertWithReason(condexpr,reason);
#else
#	define		EONIL_MEDIA_ENGINE_MATH_ASSERT(condexpr)
#	define		EONIL_MEDIA_ENGINE_MATH_ASSERT_WITH_REASON(condexpr,reason)			
#endif









