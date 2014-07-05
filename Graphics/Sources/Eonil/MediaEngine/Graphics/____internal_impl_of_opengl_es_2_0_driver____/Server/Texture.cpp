//
//  Texture.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "../Stub/GL.h"
#include "Texture.h"

//#include "../_DEV_/_TextTextureGenerator.h"
//#include "../Platform/NativeImage.h"

#include "TextureCoreUtil-Internal.h"







//#include "../Aliens/PlanarRGBAImageProxy.h"

#if	EONIL_MEDIA_ENGINE_TARGET_OSX || EONIL_MEDIA_ENGINE_TARGET_IOS
//#include "../Aliens/Apple/CoreGraphics/_PlanarRGBAImageProxy_Core_using_Apple_CoreGraphics.h"
//#include "../Aliens/Apple/CoreGraphics/_PlanarRGBAImageUtility.h"
#endif











INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Server
{
	using namespace Stub;
//		using namespace Conversion;
	using namespace Platform::D2014R1;
	
//		namespace
//		{
//			void
//			ASSERT_TEXTURE_INFO(GLKTextureInfo* ti)
//			{
//				EEGL_ASSERT_WITH_REASON([ti isKindOfClass:[GLKTextureInfo class]], "Couldn't load texture into `GLKTextureInfo` class.");
//				EEGL_ASSERT_WITH_REASON(isPOT(ti.width), "If the texture size is non-POT number, it won't work though it looks loaded.");
//				EEGL_ASSERT_WITH_REASON(isPOT(ti.height), "If the texture size is non-POT number, it won't work though it looks loaded.");
//				EEGL_ASSERT_WITH_REASON(ti.name != 0, "Texture was not created. Name is `0`.");
//			}
//		}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
				
	
	
	
	
	
	
	
	
	
	Texture2D::Core::Core()
	{
		name	=	eeglGenTexture();
	}
	Texture2D::Core::Core(GLuint const name) : name(name)
	{
	}
	Texture2D::Core::~Core()
	{
		eeglDeleteTexture(name);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	Texture2D::Texture2D() : _cptr(new Core())
	{
	}
	Texture2D::Texture2D(Core* const core) : _cptr(core)
	{
		/*!
		 Textures will not work without parameter setting.
		 There's initial value doesn't work.
		 */
		setParameters({});
	}
	Texture2D::Texture2D(Texture2D&& other) : _cptr(std::move(other._cptr))
	{
	}
	Texture2D::~Texture2D()
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(_cptr == nullptr or _cptr->name != NULL_GL_NAME());
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	auto Texture2D::
	empty() const -> bool
	{
		return	_cptr->name == NULL_GL_NAME();
	}
	
	auto Texture2D::
	name() const -> GLuint
	{
		_assertNonEmptyState();
		
		return	_cptr->name;
	}
	
	auto
	Texture2D::
	setParameters(const Server::Texture2D::Parameters &p1) -> void
	{
		eeglBindTexture(GL_TEXTURE_2D, name());
		eeglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GLint(p1.minificationFilter));
		eeglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GLint(p1.magnificationFilter));
		eeglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GLint(p1.horizontalWrapping));
		eeglTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GLint(p1.verticalWrapping));
		eeglUnbindTexture(GL_TEXTURE_2D);
	}
	
	
	
	
	void
	Texture2D::_assertNonEmptyState() const
	{
		EEGL_ASSERT(not empty());
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	auto
	Texture2D::Utility::textureWithPixels(GenericMemoryRange<const void> memory, const sz &width, const sz &height, bool const& flipInY) -> Texture2D
	{
		GLuint	name	=	eeglGenTexture();
		GLsizei	width2	=	toGLsizei(width);
		GLsizei	height2	=	toGLsizei(height);
		
		eeglBindTexture(GL_TEXTURE_2D, name);
		eeglTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, memory.begin());
		eeglUnbindTexture(GL_TEXTURE_2D);
		
		return	Texture2D(new Core(name));
	}
	
//		auto
//		Texture2D::Utility::_DEV_textureWithResourceAtPath(const std::string path) -> Texture2D
//		{
//			return	textureWithAlienImage(Aliens::PlanarRGBAImageProxy::proxyWithContentOfFileAtResourcePath(path));
//		}
//		
//		
//		
//		
//
//		
//		auto
//		Texture2D::Utility::textureWithAlienImage(const Aliens::PlanarRGBAImageProxy &image, bool const flipInY) -> Texture2D
//		{
//			CGImageRef	img1	=	image.rawPointer().alien;
////			GLuint		name	=	Aliens::NameByCreatingTextureFromCGImage(img1, flipInY);
//			GLuint		name	=	Aliens::NameByCreatingTextureFromCGImage2(img1);
//			
//			return		Texture2D(new Core(name));
//		}
//		auto
//		Texture2D::Utility::textureWithMemoryRangeContainingPNGData(GenericMemoryRange<const UInt8> memory, bool const flipInY) -> Texture2D
//		{
//			Aliens::PlanarRGBAImageProxy	img1	=	Aliens::PlanarRGBAImageProxy::proxyWithContentOfMemory(memory);
//			return	textureWithAlienImage(img1, flipInY);
//		}
//		auto
//		Texture2D::Utility::textureWithContentOfFileAtPath(const str &filepath) -> Texture2D
//		{
//			return	textureWithAlienImage(Aliens::PlanarRGBAImageProxy::proxyWithContentOfFileAtArbitraryPath(filepath));
//		}
	
	
	
	
	
	
	
	
			
	
	
	
	
	
	
	
	
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END




