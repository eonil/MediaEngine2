//
//  _PlanarRGBAImageProxy_Core_using_Apple_CoreGraphics.cpp
//  Graphics
//
//  Created by Hoon H. on 2/17/14.
//
//

#include "_PlanarRGBAImageProxy_Core_using_Apple_CoreGraphics.h"
#if EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX
#include	"_PlanarRGBAImageProxy_Core_using_Apple_CoreGraphics.h"
#import		<Foundation/Foundation.h>
#import		<ImageIO/ImageIO.h>
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

namespace
Aliens
{
	
	
	
	
	
	
	
	
	
	
	
	
	
	PlanarRGBAImageProxy::PlanarRGBAImageProxy()
	{
	}
	PlanarRGBAImageProxy::PlanarRGBAImageProxy(Core* core) : _cptr(core)
	{
	}
	PlanarRGBAImageProxy::PlanarRGBAImageProxy(PlanarRGBAImageProxy&& o)
	{
		std::swap(_cptr, o._cptr);
	}
	PlanarRGBAImageProxy::~PlanarRGBAImageProxy()
	{
	}
	
	
	auto
	PlanarRGBAImageProxy::operator=(PlanarRGBAImageProxy&& o) -> PlanarRGBAImageProxy&
	{
		std::swap(_cptr, o._cptr);
		return	*this;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
			
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	auto
	PlanarRGBAImageProxy::core() const -> Core const&
	{
		return	*_cptr;
	}
	auto
	PlanarRGBAImageProxy::rawPointer() const -> RawPointer const&
	{
		return	_cptr->rawPointer();
	}
	
	
	
	
	
	
	auto
	PlanarRGBAImageProxy::proxyByOwningRawPointer(PlanarRGBAImageProxy::RawPointer &&rawPointer) -> PlanarRGBAImageProxy
	{
		return	PlanarRGBAImageProxy(new Core(std::move(rawPointer)));
	}
	
	auto
	PlanarRGBAImageProxy::proxyWithContentOfFileAtArbitraryPath(const str &filepath) -> PlanarRGBAImageProxy
	{
		return	PlanarRGBAImageProxy(new Core(filepath));
	}
	auto
	PlanarRGBAImageProxy::proxyWithContentOfFileAtResourcePath(const str &resourcepath) -> PlanarRGBAImageProxy
	{
		NSString*	p0	=	[[NSString alloc] initWithUTF8String:resourcepath.c_str()];
		NSString*	p1	=	[p0 stringByDeletingPathExtension];
		NSString*	p2	=	[p0 pathExtension];
		NSString*	p3	=	[[NSBundle mainBundle] pathForResource:p1 ofType:p2];
		std::string	p4	=	p3.UTF8String;
		
		return	proxyWithContentOfFileAtArbitraryPath(p4);
	}
	
	
	auto
	PlanarRGBAImageProxy::proxyWithContentOfMemory(GenericMemoryRange<UInt8 const> memory) -> PlanarRGBAImageProxy
	{
		return	PlanarRGBAImageProxy(new Core(memory));
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*!
	 Returns an image with rc == 1. You're responsible to release the rc.
	 */
	auto PlanarRGBAImageProxy::Core::
	_makeupCGImageFromData(CFDataRef const& data) -> CGImageRef
	{
		@autoreleasepool
		{
			CGImageSourceRef	source	=	CGImageSourceCreateWithData(data, NULL);
			
			////
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion(CGImageSourceGetCount(source) == 1, "The image must be single frame PNG file.");
			}
			////
			
			CGImageRef			img		=	CGImageSourceCreateImageAtIndex(source, 0, NULL);		//	rc == +1.
			CFRelease(source);
			
//				auto	code	=	CGImageGetAlphaInfo(img) ;
			
			////
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion(CGImageGetAlphaInfo(img) == kCGImageAlphaLast, "The image must be a non-premultiplied RGBA image. (alpha channel at last)");
			}
			////
			
			return	img;
		}
	}
	auto PlanarRGBAImageProxy::Core::
	_makeupCGImageFromData(GenericMemoryRange<UInt8 const> memory) -> CGImageRef
	{
		@autoreleasepool
		{
			NSData*				d2		=	[NSData dataWithBytes:memory.begin() length:memory.size()];
			return	_makeupCGImageFromData((__bridge CFDataRef)d2);
		}
	}
	auto PlanarRGBAImageProxy::Core::
	_makeupCGImageFromData(str const& filepath) -> CGImageRef
	{
		@autoreleasepool
		{
			NSString*	s1	=	[NSString stringWithUTF8String:filepath.c_str()];
			NSData*		d2	=	[NSData dataWithContentsOfFile:s1];
			return	_makeupCGImageFromData((__bridge CFDataRef)d2);
		}
	}
	
	
	
	
	
	
	

	
	
	
	
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END
#endif // EONIL_MEDIA_ENGINE_TARGET_IOS || EONIL_MEDIA_ENGINE_TARGET_OSX
