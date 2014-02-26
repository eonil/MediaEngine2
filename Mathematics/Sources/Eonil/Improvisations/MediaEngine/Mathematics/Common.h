//
//  Common.h
//  Mathematics
//
//  Created by Hoon H. on 2/9/14.
//
//

#ifndef __Mathematics__Common__
#define __Mathematics__Common__

#include	<Eonil/Improvisations/CommonUtility/CommonUtility.h>
#include	<Eonil/Improvisations/MediaEngine/Foundation/Foundation.h>

#if	EE_LANG_CPP

using		namespace Eonil::Improvisations::CommonUtility;


extern "C"
{
	typedef	float	EEScalar;
}

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Mathematics {
	
	namespace
	Value
	{
		using	Scalar	=	EEScalar;
		
		struct	Vector4;
		struct	Matrix4;
	}
	
	using namespace	Eonil::Improvisations::MediaEngine::Foundation;
	using namespace	Eonil::Improvisations::MediaEngine::Foundation::D2014R1;
	
}}}}







#if				EONIL_MEDIA_ENGINE_DEBUG_MODE
#	define		EONIL_MEDIA_ENGINE_MATH_ASSERT(condexpr)							Eonil::Improvisations::MediaEngine::Mathematics::Debugging::Doctor::assertWithReason(condexpr);
#	define		EONIL_MEDIA_ENGINE_MATH_ASSERT_WITH_REASON(condexpr,reason)			Eonil::Improvisations::MediaEngine::Mathematics::Debugging::Doctor::assertWithReason(condexpr,reason);
#else
#	define		EONIL_MEDIA_ENGINE_MATH_ASSERT(condexpr)
#	define		EONIL_MEDIA_ENGINE_MATH_ASSERT_WITH_REASON(condexpr,reason)			
#endif






#endif

#endif /* defined(__Mathematics__Common__) */
