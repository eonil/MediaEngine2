//
//  NativeImage.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/24/13.
//
//

#include "NativeImage.h"
#include <CoreGraphics/CoreGraphics.h>

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Platform
	{
		namespace
		D2014R1
		{








			struct
			NativeImage::Core
			{
				void*	ptr;
				
				Core(void* ptr);
				~Core();
			};

			
			
			NativeImage::Core::Core(void* const ptr) : ptr(ptr)
			{
				CGImageRef	imgptr	=	(CGImageRef)ptr;
				CGImageRetain(imgptr);
			}
			NativeImage::Core::~Core()
			{
				CGImageRef	imgptr	=	(CGImageRef)ptr;
				CGImageRelease(imgptr);
			}
			
			void* const
			NativeImage::platformObject() const
			{
				return	_core == nullptr ? NULL : _core->ptr;
			}
			

			
			
			
			
			
			
			
			
			
			
			


			NativeImage::NativeImage(void* const platformObject) : _core(new Core(platformObject))
			{
			}
	
			
			
			
			
			
			
		}
	}
	
}}}}


