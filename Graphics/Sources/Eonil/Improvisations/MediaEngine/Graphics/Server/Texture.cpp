//
//  Texture.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "../Stub/GL.h"
#include "Texture.h"
#include "../Value/Conversion/GLNumbers.h"

//#include "../_DEV_/_TextTextureGenerator.h"
#include "../Platform/NativeImage.h"

#include "TextureCoreUtil-Internal.h"

#include <Eonil/Improvisations/MediaEngine/Mathematics/Geometry/Conversion/Unions.h>






#include "../Aliens/PlanarRGBAImageProxy.h"

#if	EONIL_MEDIA_ENGINE_TARGET_OSX || EONIL_MEDIA_ENGINE_TARGET_IOS
#include "../Aliens/Apple/CoreGraphics/_PlanarRGBAImageProxy_Core_using_Apple_CoreGraphics.h"
#include "../Aliens/Apple/CoreGraphics/_PlanarRGBAImageUtility.h"
#endif











namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Server
	{
		using namespace Stub;
		using namespace Conversion;
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
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
					
		
		
		
		
		
		
		
		
		
		PlanarTexture::Core::Core()
		{
			name	=	eeglGenTexture();
		}
		PlanarTexture::Core::Core(GLuint const name) : name(name)
		{
		}
		PlanarTexture::Core::~Core()
		{
			eeglDeleteTexture(name);
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		PlanarTexture::PlanarTexture() : _cptr(new Core())
		{
		}
		PlanarTexture::PlanarTexture(Core* const core) : _cptr(core)
		{
			eeglBindTexture(GL_TEXTURE_2D, name());
			{
				eeglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				eeglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				eeglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				eeglTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			}
			eeglUnbindTexture(GL_TEXTURE_2D);
		}
		PlanarTexture::PlanarTexture(PlanarTexture&& other) : _cptr(std::move(other._cptr))
		{
		}
		PlanarTexture::~PlanarTexture()
		{
			EONIL_DEBUG_ASSERT(_cptr == nullptr or _cptr->name != NULL_GL_NAME());
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		auto PlanarTexture::
		empty() const -> bool
		{
			return	_cptr->name == NULL_GL_NAME();
		}
		
		auto PlanarTexture::
		name() const -> GLuint
		{
			_assertNonEmptyState();
			
			return	_cptr->name;
		}
		
		void
		PlanarTexture::_assertNonEmptyState() const
		{
			EEGL_ASSERT(not empty());
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		auto
		PlanarTexture::Utility::textureWithPixels(GenericMemoryRange<const void> memory, const Size &width, const Size &height, bool const& flipInY) -> PlanarTexture
		{
			GLuint	name	=	eeglGenTexture();
			GLsizei	width2	=	toGLsizei(width);
			GLsizei	height2	=	toGLsizei(height);
			
			eeglBindTexture(GL_TEXTURE_2D, name);
			eeglTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, memory.begin());
			eeglUnbindTexture(GL_TEXTURE_2D);
			
			return	PlanarTexture(new Core(name));
		}
		
		auto
		PlanarTexture::Utility::_DEV_textureWithResourceAtPath(const std::string path) -> PlanarTexture
		{
			return	textureWithAlienImage(Aliens::PlanarRGBAImageProxy::proxyWithContentOfFileAtResourcePath(path));
		}
		
		
		
		

		
		auto
		PlanarTexture::Utility::textureWithAlienImage(const Aliens::PlanarRGBAImageProxy &image, bool const flipInY) -> PlanarTexture
		{
			CGImageRef	img1	=	image.rawPointer().alien;
//			GLuint		name	=	Aliens::NameByCreatingTextureFromCGImage(img1, flipInY);
			GLuint		name	=	Aliens::NameByCreatingTextureFromCGImage2(img1);
			
			return		PlanarTexture(new Core(name));
		}
		auto
		PlanarTexture::Utility::textureWithMemoryRangeContainingPNGData(GenericMemoryRange<const UInt8> memory, bool const flipInY) -> PlanarTexture
		{
			Aliens::PlanarRGBAImageProxy	img1	=	Aliens::PlanarRGBAImageProxy::proxyWithContentOfMemory(memory);
			return	textureWithAlienImage(img1, flipInY);
		}
		auto
		PlanarTexture::Utility::textureWithContentOfFileAtPath(const str &filepath) -> PlanarTexture
		{
			return	textureWithAlienImage(Aliens::PlanarRGBAImageProxy::proxyWithContentOfFileAtArbitraryPath(filepath));
		}
		
		
		
		
		
		
		
		
				
		
		
		
		
		
		
		
		
	}
	
}}}}



