//
//  ____dbg____.h
//  Graphics
//
//  Created by Hoon H. on 14/7/6.
//
//

#pragma once
#include "common_of____internal_impl_of_opengl_es_2_0_driver____.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

#if	EONIL_DEBUG_MODE
static constexpr bool const		USE_RESOURCE_CLEANSING		=	true;
#else
static constexpr bool const		USE_RESOURCE_CLEANSING		=	false;
#endif

auto	assertWithReason(const bool condition) -> void;
auto	assertWithReason(const bool condition, const std::string reason) -> void;
auto	assertCurrentGLContextExistence() -> void;																			//!	All calles to GL needs proper current context which is platform specific. This check that platform specific GL context existence.
auto	assertNoGLError() -> void;																							//	Depends on `useStateValidation()`.
auto	assertNoGLErrorWithMessageDesignations(std::map<GLenum,std::string> const messageMap) -> void;						//!	@note	Depends on `useStateValidation()`.

auto	log(str const& message) -> void;
auto	description_with_attributes(str const& description, vec<std::pair<str,str>> const& attributes) -> str;
auto	description_of_object(str const& type, vec<std::pair<str,str>> const& attributes) -> str;





template<typename originT, typename destinationT>
auto
assertForSignedNumericRange(const originT value) -> void
{
	static_assert(std::is_signed<originT>::value, "Only for signed types.");
	//#pragma clang diagnostic push
	//#pragma clang diagnostic ignored	"-Wtype-limits"
	assertWithReason(value >= std::numeric_limits<destinationT>::min());
	assertWithReason(value <= std::numeric_limits<destinationT>::max());
	//#pragma clang diagnostic pop
}

template<typename originT, typename destinationT>
auto
assertForUnsignedNumericRange(const originT value) -> void
{
	static_assert(std::is_unsigned<originT>::value, "Only for unsigned types.");
	assertWithReason(value <= std::numeric_limits<destinationT>::max());
}


template <typename T>
auto
heximize(T const& v) -> str
{
	/*!
	 @todo	
	 implement this...
	 */
	return	std::to_string(v);
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END








#if EONIL_DEBUG_MODE
#define	EEGL_ASSERT(condexpr)							Eonil::MediaEngine::Graphics::____internal_impl_of_opengl_es_2_0_driver____::assertWithReason(condexpr);
#define	EEGL_ASSERT_WITH_REASON(condexpr,reason)		Eonil::MediaEngine::Graphics::____internal_impl_of_opengl_es_2_0_driver____::assertWithReason((condexpr),(reason));
#define	EEGL_ASSERT_NO_GL_ERROR()						Eonil::MediaEngine::Graphics::____internal_impl_of_opengl_es_2_0_driver____::assertNoGLError();
#else
#define	EEGL_ASSERT(condexpr)
#define	EEGL_ASSERT_WITH_REASON(condexpr,reason)
#define	EEGL_ASSERT_NO_GL_ERROR()
#endif
