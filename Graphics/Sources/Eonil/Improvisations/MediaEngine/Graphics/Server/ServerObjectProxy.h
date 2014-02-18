//
//  ServerObjectProxy.h
//  Graphics
//
//  Created by Hoon H. on 2/7/14.
//
//

#ifndef __Graphics__ServerObjectProxy__
#define __Graphics__ServerObjectProxy__

#include "../Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
	
		static inline constexpr auto
		NULL_GL_NAME() -> GLuint
		{
			return	0;
		}
		
		class
		ServerObjectProxy : public NoCopyButMoveObject, public TrackableObject
		{
		public:
			ServerObjectProxy() = default;
			ServerObjectProxy(ServerObjectProxy const&) = default;
			ServerObjectProxy(ServerObjectProxy&&) = default;
		};
		

		
	}
	
}}}}

#endif /* defined(__Graphics__ServerObjectProxy__) */
