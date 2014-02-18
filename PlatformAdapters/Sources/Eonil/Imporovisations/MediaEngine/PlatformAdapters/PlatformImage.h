//
//  NativeImage.h
//  PlatformAdapters
//
//  Created by Hoon H. on 2/6/14.
//
//

#ifndef __PlatformAdapters__NativeImage__
#define __PlatformAdapters__NativeImage__

#include "Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace PlatformAdapters {

	
	
	class
	NativeImage
	{
		struct	Core;
		
	public:
		auto	resolveAsGLTexture() const -> GLuint;
	};
	
	class
	NativeImageManager
	{
	public:
		auto	resolve(str const& filepath) -> NativeImage const&;
		auto	resolve(UniqueByteMemoryRange const& data) -> NativeImage const&;
		
	public:
		struct
		Utility
		{
			static	auto	defaultManager() -> NativeImageManager&;
		};
	};
	
	
	
	
	
	
		
	
}}}}



#endif /* defined(__PlatformAdapters__NativeImage__) */
