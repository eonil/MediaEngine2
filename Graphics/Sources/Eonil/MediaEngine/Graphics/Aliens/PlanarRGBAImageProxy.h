//
//  PlanarRGBAImageProxy.h
//  Graphics
//
//  Created by Hoon H. on 2/17/14.
//
//

#pragma once
#include "../Common.h"
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

namespace
Aliens
{
	/*!
	 Represents default 2D RGBA image object implemented using platform specific feature.
	 
	 @classdesign
	 This classs is mainly used to support text-drawing. So this is editable by default,
	 and expected to be placed in system-memory rather than VRAM. Anyway, the mutation
	 may be implemented by recreating a whole new image, so efficiency is not guaranteed.
	 
	 @deprecated
	 This is depending on platform-specific image facility, and has been deprecated.
	 Use `Eonil::Aliens::PNG` feature in Aliens library instead of.
	 */
	class
	EONIL_MEDIA_ENGINE_DEPRECATE()
	PlanarRGBAImageProxy
	{
		struct	Core;
		
		uptr<Core>	_cptr{nullptr};
		
		PlanarRGBAImageProxy(Core* core);
		
		auto	core() const -> Core const&;
		
	public:
		PlanarRGBAImageProxy();
		PlanarRGBAImageProxy(PlanarRGBAImageProxy const&) = delete;
		PlanarRGBAImageProxy(PlanarRGBAImageProxy&&);
		~PlanarRGBAImageProxy();
		
		auto	operator=(PlanarRGBAImageProxy&& o) -> PlanarRGBAImageProxy&;
		
		struct
		RawPointer;
		
		auto	rawPointer() const -> RawPointer const&;
		
	public:
		static auto	proxyByOwningRawPointer(RawPointer&& rawPointer) -> PlanarRGBAImageProxy;						//!	Newrly created image proxy object will take the ownership for the underlying alien pointer.
		static auto	proxyWithContentOfFileAtArbitraryPath(str const& filepath) -> PlanarRGBAImageProxy;				//!	The file must be a PNG file. Other format may be supported implicitly by the underlying platform feature, but that's unsupported behavior and not guaranteed. (I will not care about other formats)
		static auto	proxyWithContentOfFileAtResourcePath(str const& resourcepath) -> PlanarRGBAImageProxy;
		static auto	proxyWithContentOfMemory(GenericMemoryRange<uint8_t const> memory) -> PlanarRGBAImageProxy;		//!	The memory block must contain PNG encoded binary data.
	};
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END
