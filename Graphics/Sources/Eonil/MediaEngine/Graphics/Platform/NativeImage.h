//
//  PlatformImage.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/24/13.
//
//

#pragma once
#include "../Common.h"
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

namespace
Platform
{
	namespace
	D2014R1
	{

		
		
		
		
		
		
		
		
		
		
		/*!
		 Represents platform-native image object.
		 
		 @classdesign
		 
		 @discussion
		 This class is designed to provide access to platform-specific
		 
		 @note
		 DEPRECATED.
		 Switch to `Aliens::PlanarRGBAImageProxy` class ASAP.
		 */
		class
		NativeImage
		{
			struct	Core;
			std::shared_ptr<Core>	_core;
			
		public:
			NativeImage(void* const platformObject) __attribute__((deprecated));
			
			void* const	platformObject() const __attribute__((deprecated));		//!	Gets stored platform image object. You shoudn't manage ownership of this object is managed by this class.
		};
		
		


		
		
		
		
		
		
	}
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END
