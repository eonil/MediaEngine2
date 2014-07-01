//
//  Prelude.h
//  Foundation
//
//  Created by Hoon H. on 14/7/2.
//
//

#pragma once
#include <string>
#include <iostream>
#include <Eonil/Common/age2/age2.h>





#define			EONIL_MEDIA_ENGINE_DEBUG_MODE	EONIL_DEBUG_MODE

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




#if				EONIL_MEDIA_ENGINE_DEBUG_MODE
#define			EONIL_MEDIA_ENGINE_DEBUG_LOG(msg)							{ Eonil::Improvisations::MediaEngine::Foundation::Debugging::Doctor::logMessage(msg); }
#else
#define			EONIL_MEDIA_ENGINE_DEBUG_LOG(msg)
#endif






#define			EONIL_MEDIA_ENGINE_DEPRECATE()								__attribute__((deprecated("This feature has been deprecated. No reason specified. Souce code may contain more informations.")))
#define			EONIL_MEDIA_ENGINE_DEPRECATE_WITH_MESSAGE(msg)				__attribute__((deprecated(msg)))											//!	If this doesn't work, then you need Clang 3.5+. @ref http://clang.llvm.org/docs/LanguageExtensions.html#messages-on-deprecated-and-unavailable-attributes








#define			EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_BEGIN				namespace Eonil { namespace MediaEngine { namespace Foundation {
#define			EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_END					} } }



















































EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_BEGIN
using namespace	Eonil::Common::age2;

static inline auto
err9_legacy_error_always(str const& message = "(none)") -> void
{
	std::cout << "err9_converted_legacy_assertion = " << message << "\n";
	Eonil::Common::age2::err3_UNRECOVERABLE_unexpected_inconsistent_program_state_DISCOVERED_and_seems_to_be_an_internal_logic_bug_always();
}

/*!
 Temporary forced legacy error.
 
 @todo
 Replace these into error1~3 by its roles.
 Take care that the condtiion is inverted.
 */
static inline auto
err9_converted_legacy_assertion(bool const cond, str const& message = "(none)") -> void
{
	std::cout << "err9_converted_legacy_assertion = " << message << "\n";
	if (not cond)
	{
		Eonil::Common::age2::err3_UNRECOVERABLE_unexpected_inconsistent_program_state_DISCOVERED_and_seems_to_be_an_internal_logic_bug_if(cond);
	}
}

#if	EONIL_DEBUG_MODE
static constexpr bool const		USE_DEBUGGING_ASSERTIONS		=	true;
#else
static constexpr bool const		USE_DEBUGGING_ASSERTIONS		=	false;
#endif

EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_END




















