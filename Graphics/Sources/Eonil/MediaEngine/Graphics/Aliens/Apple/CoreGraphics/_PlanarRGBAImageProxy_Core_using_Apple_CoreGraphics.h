//
//  _PlanarRGBAImageProxy_Core_using_Apple_CoreGraphics.h
//  Graphics
//
//  Created by Hoon H. on 2/17/14.
//
//

#ifndef __Graphics___PlanarRGBAImageProxy_Core_using_Apple_CoreGraphics__
#define __Graphics___PlanarRGBAImageProxy_Core_using_Apple_CoreGraphics__

#if EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX







#include "../../PlanarRGBAImageProxy.h"

#include	<CoreFoundation/CoreFoundation.h>
#include	<CoreGraphics/CoreGraphics.h>


namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Aliens
	{
		
		
		
		struct
		PlanarRGBAImageProxy::RawPointer
		{
			CGImageRef	alien	{NULL};
			
			RawPointer() {}
			RawPointer(CGImageRef alien) : alien(alien) {}
		};

		
		
		
		
		/*!
		 Core is implemented using CoreGraphics and UIKit in iOS.
		 */
		class
		EONIL_MEDIA_ENGINE_DEPRECATE()
		PlanarRGBAImageProxy::Core
		{
			RawPointer	_rptr{};
			
			auto _makeupCGImageFromData(CFDataRef const& data) -> CGImageRef;
			auto _makeupCGImageFromData(GenericMemoryRange<UInt8 const> memory) -> CGImageRef;
			auto _makeupCGImageFromData(str const& filepath) -> CGImageRef;

			
			
		public:
			Core(RawPointer&& raw)
			{
				std::swap(_rptr, raw);		//	No change on refcount.
			}
			Core(GenericMemoryRange<UInt8 const> memory) : _rptr(_makeupCGImageFromData(memory))
			{
			}
			Core(str const& filepath) : _rptr(_makeupCGImageFromData(filepath))
			{
			}
			~Core()
			{
				CGImageRelease(_rptr.alien);
			}
			
			auto
			rawPointer() const -> RawPointer const&
			{
				return	_rptr;
			}
		};
		
		
		
		
		
	}
	
}}}}









#endif // EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX

#endif /* defined(__Graphics___PlanarRGBAImageProxy_Core_using_Apple_CoreGraphics__) */
