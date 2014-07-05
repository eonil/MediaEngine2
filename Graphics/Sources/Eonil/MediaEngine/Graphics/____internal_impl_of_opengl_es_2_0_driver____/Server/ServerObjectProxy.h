//
//  ServerObjectProxy.h
//  Graphics
//
//  Created by Hoon H. on 2/7/14.
//
//

#pragma once
#include "Declarations.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Server
{

	static inline constexpr auto
	NULL_GL_NAME() -> GLuint
	{
		return	0;
	}
	
	class
	ServerObjectProxy : public no_copy, public TrackableObject
	{
	public:
		ServerObjectProxy() = default;
		ServerObjectProxy(ServerObjectProxy const&) = default;
		ServerObjectProxy(ServerObjectProxy&&) = default;
		
		auto	operator=(ServerObjectProxy const&) -> ServerObjectProxy& = delete;
		auto	operator=(ServerObjectProxy&&) -> ServerObjectProxy& = default;
	};
	

	
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END

