//
//  Doctor.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include	"Doctor.h"

#include	<sstream>
#include	<Eonil/Improvisations/MediaEngine/Foundation/Foundation.h>
#include	<Eonil/Improvisations/MediaEngine/Mathematics/Geometry/Conversion/Unions.h>

#include	"../Transform.h"
#include	"../Rendering/D2014R1/_Camera_v1.h"

#if			EONIL_MEDIA_ENGINE_TARGET_IOS
#include	"../Platform/iOS.h"
#elif		EONIL_MEDIA_ENGINE_TARGET_OSX
#include	"../Platform/OSX.h"
#endif

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Debugging
	{
		
		
		void
		Doctor::exceptWithReason(const std::string reason)
		{
			Eonil::Improvisations::MediaEngine::Foundation::Debugging::Doctor::exceptWithReason(reason, "EXCEPTION", "EonilGraphics");
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
			return	Eonil::Improvisations::MediaEngine::Foundation::Debugging::Doctor::isDebugMode();
		}
		bool const
		Doctor::useLogging()
		{
			return	Eonil::Improvisations::MediaEngine::Foundation::Debugging::Doctor::useLogging();
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
			Eonil::Improvisations::MediaEngine::Foundation::Debugging::Doctor::logMessage(message, "EonilGraphics");
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
			if (useStateValidation() and not condition)
			{
				Eonil::Improvisations::MediaEngine::Foundation::Debugging::Doctor::exceptWithReason(reason, "ASSERTION", "EonilGraphics");
			}
		}
		
		void
		Doctor::assertCurrentGLContextExistence()
		{
#if		EONIL_MEDIA_ENGINE_TARGET_IOS
			assertWithReason(Platforms::iOS::hasCurrentGLContext(), "There's no GL context currently bounds.");
#elif	EONIL_MEDIA_ENGINE_TARGET_OSX
			assertWithReason(Platforms::OSX::hasCurrentGLContext(), "There's no GL context currently bounds.");
#else	
			static_assert(false, "Unknown, unsupported platform.");
#endif
		}
		void
		Doctor::assertNoGLError()
		{
			if (useStateValidation())
			{
				assertNoGLErrorWithMessageDesignations(std::map<GLenum,std::string>());
			}
		}
		void
		Doctor::assertNoGLErrorWithMessageDesignations(const std::map<GLenum, std::string> messageMap)
		{
			if (useStateValidation())
			{
				/*
				 GL error can be stacked multiple times.
				 Pump them all out.
				 */
				
				Size			c	=	0;
				GLenum			err	=	GL_NO_ERROR;
			
				while ((err = glGetError()) != GL_NO_ERROR)
				{
					if (messageMap.find(err) == messageMap.end())
					{
						//#define GL_INVALID_ENUM                   0x0500
						//#define GL_INVALID_VALUE                  0x0501
						//#define GL_INVALID_OPERATION              0x0502
						//#define GL_OUT_OF_MEMORY                  0x0505
						
						std::stringstream	ss;
						ss << "A GL error occured: 0x" << std::hex << err << " (message undesignated)";
						std::string const	msg	=	ss.str();
						log(msg);
						
						//						std::string const	s1	=	std::hex << err;
						//						std::string const	num	=	stringWithCFormat("0x%X", err);
						//						std::string const	msg	=	stringWithCFormat("A GL error occured: %s (message undesignated)", num.c_str());
						//						log(msg);
					}
					else
					{
						std::string const	msg	=	messageMap.at(err);
						log("A GL error occured: " + msg);
					}
					c++;
				}
				assertWithReason(c == 0, "GL error shouldn't be detected.");
			}
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
		Doctor::assertVector4Validity(const Value::Vector4 v)
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
		Doctor::assertMatrix4Validity(const Value::Matrix4 v)
		{
			if (Doctor::useStateValidation())
			{
				for (Size i=0; i<16; i++)
				{
					assertForZeroOrNormal(Value::Conversion::FLOAT32x16(v).components[i]);
				}
			}
		}
		void
		Doctor::assertTransformValidity(Transform const v)
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
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		Size const
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
	
	
}}}}






















namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Debugging
	{
		
		
		
		template<>
		std::string const
		Doctor::describe(const Server::Program &object)
		{
			return	stringWithCFormat("(Program (address 0x%llx) (name %llu) (uniform values (%s)) (vertex attributes (%s)))",
									  uint64_t(uintptr_t(&object)),
									  uint64_t(object.name()),
									  describeVector(object.allUniformValueSlotV1s()).c_str(),
									  describeVector(object.allVertexAttributeSlotV1s()).c_str()
									  );
		}
		
		
		
		template<>
		std::string const
		Doctor::describe(const Server::UniformValueSlotV1 &object)
		{
			return	stringWithCFormat("(UniformValueSlotV1 (address 0x%llx) (index %llu) (name \"%s\") (location %lli))",
									  uint64_t(uintptr_t(&object)),
									  uint64_t(object.index()),
									  object.name().c_str(),
									  int64_t(object.location()));
		}
		template<>
		std::string const
		Doctor::describe(const Server::VertexAttributeSlotV1 &object)
		{
			return	stringWithCFormat("(VertexAttributeSlotV1 (address 0x%llx) (index %llu) (name \"%s\") (location %lli))",
									  uint64_t(uintptr_t(&object)),
									  uint64_t(object.index()),
									  object.name().c_str(),
									  int64_t(object.location()));
		}
		
		

		
	}
	
}}}}



