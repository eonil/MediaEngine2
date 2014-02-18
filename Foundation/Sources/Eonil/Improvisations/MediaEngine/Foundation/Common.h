//
//  Common.h
//  Foundation
//
//  Created by Hoon H. on 2/5/14.
//
//

#ifndef __Foundation__Common__
#define __Foundation__Common__


#include	<Eonil/Improvisations/CommonUtility/CommonUtility.h>






/*
 Infer `EONIL_MEDIA_ENGINE_DEBUG_MODE` flag by `DEBUG` flag if the flag was lacked.
 */
#ifndef						EONIL_MEDIA_ENGINE_DEBUG_MODE
#	ifdef					DEBUG
#		if					DEBUG == 1
#			define			EONIL_MEDIA_ENGINE_DEBUG_MODE	1
#			pragma message	"The preprocessor flag `EONIL_MEDIA_ENGINE_DEBUG_MODE` was not defined, and inferred to debug-mode by value of `DEBUG` flag. Anyway this is ad-hoc ingerence, and not regular solution. You should set the flag for precise control."
#		endif
#		if					DEBUG == 0
#			define			EONIL_MEDIA_ENGINE_DEBUG_MODE	0
#			pragma message	"The preprocessor flag `EONIL_MEDIA_ENGINE_DEBUG_MODE` was not defined, and inferred to release-mode by value of of `DEBUG` flag. Anyway this is ad-hoc ingerence, and not regular solution. You should set the flag for precise control."
#		endif
#	endif
#	ifndef					DEBUG
#		define				EONIL_MEDIA_ENGINE_DEBUG_MODE	0
#		pragma message		"The preprocessor flag `EONIL_MEDIA_ENGINE_DEBUG_MODE` was not defined, and inferred to release-mode by lack of `DEBUG` flag. Anyway this is ad-hoc ingerence, and not regular solution. You should set the flag for precise control."
#	endif
#endif





#ifndef			EONIL_MEDIA_ENGINE_DEBUG_MODE
#	error		"You must define `EONIL_MEDIA_ENGINE_DEBUG_MODE` preprocessor macro to one of `0` or `1`."
#endif



#if				EONIL_MEDIA_ENGINE_DEBUG_MODE
#	pragma		message "DEBUG BUILD!"
#else
#	pragma		message "RELEASE BUILD!"
#endif



#if				EONIL_MEDIA_ENGINE_DEBUG_MODE
#	define		EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(stmt)						{ if (Eonil::Improvisations::MediaEngine::Foundation::Debugging::Doctor::isDebugMode()) { stmt;} }
#	define		EE_ASSERT(cond)												{ EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(Eonil::Improvisations::MediaEngine::Foundation::Debugging::Doctor::assertWithReason(cond)) }
#	define		EE_ASSERT_WITH_REASON(cond,reason)							{ EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(Eonil::Improvisations::MediaEngine::Foundation::Debugging::Doctor::assertWithReason((cond), (reason))) }
#else
#	define		EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(stmt)
#	define		EE_ASSERT(cond)
#	define		EE_ASSERT_WITH_REASON(cond,reason)
#endif




#if				EONIL_MEDIA_ENGINE_DEBUG_MODE
#	define		EONIL_MEDIA_ENGINE_DEBUG_ONLY_INLINE_FIELD(type,name)		type name;
#else
#	define		EONIL_MEDIA_ENGINE_DEBUG_ONLY_INLINE_FIELD(type,name)
#endif









#define			EONIL_MEDIA_ENGINE_DEPRECATE()								__attribute__((deprecated("This feature has been deprecated.")))
#define			EONIL_MEDIA_ENGINE_DEPRECATE_WITH_MESSAGE(msg)				__attribute__((deprecated(msg)))											//!	If this doesn't work, then you need Clang 3.5+. @ref http://clang.llvm.org/docs/LanguageExtensions.html#messages-on-deprecated-and-unavailable-attributes











namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Foundation {

	using namespace	Eonil::Improvisations::CommonUtility;
	
	inline namespace
	D2014R1
	{
		using namespace	Eonil::Improvisations::CommonUtility;
	}
	
	
	
	
	
	
	
}}}}



#endif /* defined(__Foundation__Common__) */
