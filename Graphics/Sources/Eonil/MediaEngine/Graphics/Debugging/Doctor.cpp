//
//  Doctor.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include	"Doctor.h"

#include	<sstream>
#include	<Eonil/MediaEngine/Foundation.h>

#include	"../LEGACY_Transform.h"
#include	"../Rendering/D2014R1/_Camera_v1.h"

#if			EONIL_MEDIA_ENGINE_TARGET_IOS
#include	"../Platform/iOS.h"
#elif		EONIL_MEDIA_ENGINE_TARGET_OSX
#include	"../Platform/OSX.h"
#endif

//#include	"../Server/ProgramParameterLocation.h"
//#include	"../Server/ProgramMetadata.h"


EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN






namespace
Debugging
{
	static auto
	EEGL_ASSERT(bool cond) -> void
	{
		Doctor::assertWithReason(cond);
	}
	
	
	
	
	void
	Doctor::exceptWithReason(const std::string reason)
	{
		log9_just_print_line(reason);
		err3_UNRECOVERABLE_unexpected_inconsistent_program_state_DISCOVERED_and_seems_to_be_an_internal_logic_bug_always();
//			Eonil::Improvisations::MediaEngine::Foundation::Debugging::Doctor::exceptWithReason(reason, "EXCEPTION", "EonilGraphics");
	}
	
	
	std::string const
	Doctor::stringWithCFormat(char const * const format, ...)
	{
		/*
		 Do not use once created va_list multiple times.
		 That's one-time use only. Create a new one again to use it again.
		 */
		
		std::string			str;
		
		va_list	vl;
		va_start(vl, format);
		size_t const	len		=	vsnprintf(NULL, 0, format, vl);
		//			printf("%lu\n", len);
		//			printf("%s#\n", format);
		va_end(vl);
		
		char			buf[len+1];
		
		va_start(vl, format);
		size_t const	len2	=	vsnprintf(buf, len+1, format, vl);
		//			printf("%lu\n", len2);
		//			printf("%s#\n", buf);
		
		EEGL_ASSERT(len >= len2);
		EEGL_ASSERT(buf[len2] == '\0');
		buf[len2]	=	'\0';
		str			=	buf;
		va_end(vl);
		
		return	str;
	}
	
	
	
	
	
	
	
	
//			void
//			log(const std::string message)
//			{
//				Eonil::Improvisations::MediaEngine::Foundation::Debugging::Doctor::logMessage(message, "EonilGraphics");
//			}

	
	
	
	
	bool const
	Doctor::isDebugMode()
	{
		return	USE_DEBUGGING_ASSERTIONS;
	}
	bool const
	Doctor::useLogging()
	{
		return	USE_DEBUGGING_ASSERTIONS;
	}
	
	bool const
	Doctor::useStateValidation()
	{
		return	isDebugMode();
	}
	bool const
	Doctor::useResourceCleansing()
	{
		return	isDebugMode();
	}
	bool const
	Doctor::keepServerResourcesLocallyForDebugging()
	{
		return	isDebugMode();
	}
	
	bool const
	Doctor::doesPlatformSupportShaderPrecision()
	{
#if EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
		return	true;
#else
		return	false;
#endif
	}
	
	
	
	
	
	void
	Doctor::log(const std::string message)
	{
		log9_just_print_line(message);
//			Eonil::Improvisations::MediaEngine::Foundation::Debugging::Doctor::logMessage(message, "EonilGraphics");
	}
	
	void
	Doctor::logWithFormat(char const* const format, ...)
	{
		if (useLogging())
		{
			va_list	vl;
			va_start(vl, format);
			{
				size_t	len		=	vsnprintf(NULL, 0, format, vl);
				char	buf[len+1];
				size_t	len2	=	vsnprintf(buf, len, format, vl);
				EEGL_ASSERT(len == len2);
				
				buf[len]		=	'\0';
				
				log(std::string(buf));
			}
			va_end(vl);
		}
	}
	
	
	
	void
	Doctor::assertWithReason(const bool condition, const std::string reason)
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(condition, reason);
		}
//			if (useStateValidation() and not condition)
//			{
//				Eonil::Improvisations::MediaEngine::Foundation::Debugging::Doctor::exceptWithReason(reason, "ASSERTION", "EonilGraphics");
//			}
	}
	
	void
	Doctor::assertForZeroOrNormal(const float v)
	{
		if (Doctor::useStateValidation())
		{
			assertWithReason(v == 0.0f or std::isnormal(v), "The floating-point value is niether `0` or `normal.`. It cannot be a subnormal, infinity or NaN.");
		}
	}
//			void
//			Doctor::assertNonZeroMatrix4(Value::Matrix4 const v)
//			{
//				if (useStateValidation())
//				{
//					bool	valitiy	=	false;
//					for (Size i=0; i<16; i++)
//					{
//						valitiy	|=	fabsf(Conversion::FLOAT32x16(v).components[i]) > std::numeric_limits<Scalar>::epsilon();
//					}
//					assertWithReason(valitiy, "Transform matrix is all-zero which will make ahh the shape coordinate to zero so invisible. This is valid, but prohibited because this happen usually only by missing setting the transform.");
//				}
//			}
	void
	Doctor::assertVector4Validity(const Vector4 v)
	{
		if (Doctor::useStateValidation())
		{
			assertForZeroOrNormal(v.x);
			assertForZeroOrNormal(v.y);
			assertForZeroOrNormal(v.z);
			assertForZeroOrNormal(v.w);
		}
	}
	void
	Doctor::assertMatrix4Validity(const Matrix4 v)
	{
		if (Doctor::useStateValidation())
		{
			Scalar const*	ss1	=	reinterpret_cast<Scalar const*>(&v);
			for (sz i=0; i<16; i++)
			{
				Scalar	s1	=	ss1[i];
				assertForZeroOrNormal(s1);
			}
		}
	}
	void
	Doctor::assertTransformValidity(_Transform_V1 const v)
	{
		if (Doctor::useStateValidation())
		{
			assertForZeroOrNormal(v._s.x);
			assertForZeroOrNormal(v._s.y);
			assertForZeroOrNormal(v._s.z);
			
			assertForZeroOrNormal(v._r.asAxisAngle().axis.x);
			assertForZeroOrNormal(v._r.asAxisAngle().axis.y);
			assertForZeroOrNormal(v._r.asAxisAngle().axis.z);
			assertForZeroOrNormal(v._r.asAxisAngle().angle);
			assertWithReason(v._r.asAxisAngle().axis.length() > std::numeric_limits<Scalar>::epsilon(), "Axis length must be exist.");
			
			assertForZeroOrNormal(v._t.x);
			assertForZeroOrNormal(v._t.y);
			assertForZeroOrNormal(v._t.y);
		}
	}
//		void
//		Doctor::assertCameraValidity(_DEV_::_DevCamera const v)
//		{
//			if (useStateValidation())
//			{
//				assertTransformValidity(v.transform);
//				assertForZeroOrNormal(v.frame.left);
//				assertForZeroOrNormal(v.frame.right);
//				assertForZeroOrNormal(v.frame.bottom);
//				assertForZeroOrNormal(v.frame.top);
//				assertForZeroOrNormal(v.frame.near);
//				assertForZeroOrNormal(v.frame.far);
//				
//				Scalar	w	=	v.frame.right - v.frame.left;
//				Scalar	h	=	v.frame.top - v.frame.bottom;
//				Scalar	d	=	v.frame.far - v.frame.near;
//				
//				assertWithReason(w > std::numeric_limits<Scalar>::epsilon(), "PROJECTION width must be largert than `0`.");
//				assertWithReason(h > std::numeric_limits<Scalar>::epsilon(), "PROJECTION height must be largert than `0`.");
//				assertWithReason(d > std::numeric_limits<Scalar>::epsilon(), "PROJECTION depth must be largert than `0`.");
//			}
//		}
	void
	Doctor::assertCameraValidity(_Camera_v1 const v)
	{
		if (useStateValidation())
		{
			assertTransformValidity(v.transform);
			assertForZeroOrNormal(v.frame.left);
			assertForZeroOrNormal(v.frame.right);
			assertForZeroOrNormal(v.frame.bottom);
			assertForZeroOrNormal(v.frame.top);
			assertForZeroOrNormal(v.frame.near);
			assertForZeroOrNormal(v.frame.far);
			
			Scalar	w	=	v.frame.right - v.frame.left;
			Scalar	h	=	v.frame.top - v.frame.bottom;
			Scalar	d	=	v.frame.far - v.frame.near;
			
			assertWithReason(w > std::numeric_limits<Scalar>::epsilon(), "PROJECTION width must be largert than `0`.");
			assertWithReason(h > std::numeric_limits<Scalar>::epsilon(), "PROJECTION height must be largert than `0`.");
			assertWithReason(d > std::numeric_limits<Scalar>::epsilon(), "PROJECTION depth must be largert than `0`.");
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	sz const
	Doctor::sizeOfGLType(GLenum const type)
	{
		if (type == GL_BYTE)			return	sizeof(GLbyte);
		if (type == GL_UNSIGNED_BYTE)	return	sizeof(GLubyte);
		if (type == GL_SHORT)			return	sizeof(GLshort);
		if (type == GL_UNSIGNED_SHORT)	return	sizeof(GLushort);
		#if	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
		if (type == GL_FIXED)			return	sizeof(GLfixed);
		#endif
		if (type == GL_FLOAT)			return	sizeof(GLfloat);
		
		exceptWithReason("Unrecognizable GL type.");
	}
	
	
	
	
	
	
	
	
	
	
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END






















//
//EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
//
//namespace
//Debugging
//{
//	
//	
//	
//	template<>
//	std::string const
//	Doctor::describe(const Server::Program &object)
//	{
//		Server::ProgramMetadata	pm{object.name()};
//		return	stringWithCFormat("(Program (address 0x%llx) (name %llu) (uniform values (%s)) (vertex attributes (%s)))",
//								  uint64_t(uintptr_t(&object)),
//								  uint64_t(object.name()),
//								  describeVector(pm.allProgramUniformValueSlotProxys()).c_str(),
//								  describeVector(pm.allProgramVertexAttributeSlotProxys()).c_str()
//								  );
//	}
//	
//	
//	
////		template<>
////		std::string const
////		Doctor::describe(const Server::ProgramUniformValueSlotProxyV1 &object)
////		{
////			return	stringWithCFormat("(ProgramUniformValueSlotProxyV1 (address 0x%llx) (index %llu) (name \"%s\") (location %lli))",
////									  uint64_t(uintptr_t(&object)),
////									  uint64_t(object.index()),
////									  object.name().c_str(),
////									  int64_t(object.location()));
////		}
////		
////		template<>
////		std::string const
////		Doctor::describe(const Server::ProgramVertexAttributeSlotProxyV1 &object)
////		{
////			return	stringWithCFormat("(ProgramVertexAttributeSlotProxyV1 (address 0x%llx) (index %llu) (name \"%s\") (location %lli))",
////									  uint64_t(uintptr_t(&object)),
////									  uint64_t(object.index()),
////									  object.name().c_str(),
////									  int64_t(object.location()));
////		}
//	
//	
//
//	
//	
//	
//	
//	
//	
//	
//	
//	
//	
//	
//	template<>
//	std::string const
//	Doctor::describe(const Server::ProgramMetadata::ParameterSlotDescription &object)
//	{
//		return	object.stringify();
//	}
//	
//}
//
//EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END
//
//


