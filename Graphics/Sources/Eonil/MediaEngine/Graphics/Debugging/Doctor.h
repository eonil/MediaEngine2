//
//  Doctor.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#pragma once
#include "../Common.h"
#include <unordered_map>
#include <unordered_set>
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

struct	_Transform_V1;

namespace
Rendering
{
	namespace
	D2014R1
	{
		struct	_DevCamera;
		struct	_Camera_v1;
	}
}

namespace
Debugging
{
	using namespace	Eonil::MediaEngine::Graphics::Rendering::D2014R1;
	
	
	

	class
	Doctor
	{	
	public:
		typedef	std::map<GLenum,std::string>		GLErrorMessageMap;
		
	public:
		static std::string const	stringWithCFormat(char const * const format, ...) __attribute__ ((format (printf, 1, 2)));
		
		static bool const			isDebugMode();
		static bool const			useLogging();
		
		static bool const			useStateValidation();		//	If this is `true`, library will perform state validation by querying current GL device state.
		static bool const			useResourceCleansing();		//	If this is `true`, library will perform unnecessary resource cleansing at proper time to ensure specific device state.
		static bool const			keepServerResourcesLocallyForDebugging();
		
		static bool const			doesPlatformSupportShaderPrecision();
		
		static void					log(std::string const message);
		static void					logWithFormat(char const * const format, ...) __attribute__ ((format (printf, 1, 2)));
		
		static void					exceptWithReason(std::string const reason) __attribute__((noreturn));
		
		static void					assertWithReason(bool const condition, std::string const reason = "Dynamic assertion failure.");			//!	@note	Depends on `useStateValidation()`.
		static void					assertForZeroOrNormal(float const v);
//			static void					assertNonZeroMatrix4(Value::Matrix4 const v);
		static void					assertVector4Validity(Vector4 const v);
		static void					assertMatrix4Validity(Matrix4 const v);
		
		
		template<typename originT, typename destinationT>
		static void					assertForSignedNumericRange(originT const value);
		template<typename originT, typename destinationT>
		static void					assertForUnsignedNumericRange(originT const value);
		
//			static void					assertCameraValidity(_DevCamera const v);
		EONIL_MEDIA_ENGINE_DEPRECATE() static void					assertCameraValidity(_Camera_v1 const v);
		EONIL_MEDIA_ENGINE_DEPRECATE() static void					assertTransformValidity(_Transform_V1 const v);
		
		
		
	public:
		static sz const				sizeOfGLType(GLenum const type);
		
		
		
		
		
		
		
		
		
		
		
	public:
		
//			/*!
//			 External registry for debugging/profiling or anything else then essential running information.
//			 
//			 @classdesign
//			 All object must have different examination object.
//			 No object can share examination object.
//			 
//			 @note
//			 Debugging/profiling info must be allocated on heap.
//			 Arguments are designed as pointer because pointing target memory should be explicitly visible.
//			 All methods are no-op on release build.
//			 */
//			template<typename OBJ, typename EXAM>
//			class
//			Examination
//			{
//			public:
//				Examination() = delete;
//				static void			setForObject(OBJ const* const ptrobj, EXAM const* const ptrexam);
//				static void			unsetForObject(OBJ const* const ptrobj);
//				
//				/*
//				 Query method should not be called in release build.
//				 Or program will crash.
//				 */
//				static EXAM const* const 	forObject(OBJ const* const ptrobj);
//				static OBJ const* const		resolveObjectForExamination(EXAM const* const ptrexam);
//				
//			private:
//				
//				static std::unordered_map<OBJ const*, EXAM const*>&	_map();
//				static std::unordered_map<EXAM const*, OBJ const*>&	_inverse_map();		//	For duplication check and inverse resolution.
//			};
		
		
		
		
		
		
		
		
		
	public:
		/*!
		 Creates a description for an object.
		 This is shortcut to `Describer<T>` class.
		 */
		template<typename T>
		static std::string const	describe(T const& object);
		
		template<typename T>
		static std::string const	describeVector(std::vector<T> const& vector);
		
		template<typename T>
		static std::string const	describeCollection(T const& object);
		
		template<typename T>
		static std::string const	describeTable(T const& object);
	};
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END




























#pragma mark	-	Numeric Range Assertions
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
namespace
Debugging
{
	template<typename originT, typename destinationT>
	void
	Doctor::assertForSignedNumericRange(const originT value)
	{
		static_assert(std::is_signed<originT>::value, "Only for signed types.");
		if (useStateValidation())
		{
//#pragma clang diagnostic push
//#pragma clang diagnostic ignored	"-Wtype-limits"
			assertWithReason(value >= std::numeric_limits<destinationT>::min());
			assertWithReason(value <= std::numeric_limits<destinationT>::max());
//#pragma clang diagnostic pop
		}
	}
	
	template<typename originT, typename destinationT>
	void
	Doctor::assertForUnsignedNumericRange(const originT value)
	{
		static_assert(std::is_unsigned<originT>::value, "Only for unsigned types.");
		if (useStateValidation())
		{
			assertWithReason(value <= std::numeric_limits<destinationT>::max());
		}
	}
}
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END







//
//#pragma mark	-	Examination Implementation
//EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
//	
//	namespace
//	Debugging
//	{
//		template<typename OBJ, typename EXAM>
//		void
//		Doctor::Examination<OBJ, EXAM>::setForObject(const OBJ *const ptrobj, const EXAM *const ptrexam)
//		{
//			if (Doctor::isDebugMode())
//			{
//				if (_map().find(ptrobj) != _map().end())
//				{
//					Doctor::exceptWithReason("The object is already registered to `Doctor::Examination` with some examination. If you wanna change the examination, unset it first.");
//				}
//				if (_inverse_map().find(ptrexam) != _inverse_map().end())
//				{
//					Doctor::exceptWithReason("The examination is already registered for some other object. Examination cannot be shared between object. Use separated examination object.");
//				}
//				
//				_map()[ptrobj]			=	ptrexam;
//				_inverse_map()[ptrexam]	=	ptrobj;
//			}
//		}
//		template<typename OBJ, typename EXAM>
//		void
//		Doctor::Examination<OBJ, EXAM>::unsetForObject(const OBJ *const ptrobj)
//		{
//			if (Doctor::isDebugMode())
//			{
//				std::unordered_map<OBJ const*, EXAM const*>&	m	=	_map();
//				
//				std::vector<OBJ const*>	ps1;
//				std::vector<EXAM const*> ps2;
////					OBJ const*	ps1[m.size()];
////					EXAM const*	ps2[m.size()];
//				
////					int i =0;
//				for (std::pair<OBJ const*, EXAM const*> const& p : m)
//				{
////						ps1[i]	=	p.first;
////						ps2[i]	=	p.second;
//					ps1.push_back(p.first);
//					ps2.push_back(p.second);
////						i++;
//				}
//				
//				if (_map().find(ptrobj) == _map().end())
//				{
//					Doctor::exceptWithReason("The object is not yet registered to `Doctor::Examination` with any examination.");
//				}
//				
//				_inverse_map().erase(_map().at(ptrobj));
//				_map().erase(ptrobj);
//			}
//		}
//		
//		
//		
//		
//		template<typename OBJ, typename EXAM>
//		EXAM const* const
//		Doctor::Examination<OBJ, EXAM>::forObject(const OBJ *const ptrobj)
//		{
//			if (Doctor::isDebugMode())
//			{
//				if (_map().find(ptrobj) == _map().end())
//				{
//					Doctor::exceptWithReason("The object is not registered to `Doctor::Examination`.");
//				}
//				return	_map().at(ptrobj);
//			}
//			else
//			{
//				Doctor::exceptWithReason("This method should not be called in release build.");
//				return	nullptr;
//			}
//		}
//		
//		template<typename OBJ, typename EXAM>
//		OBJ const* const
//		Doctor::Examination<OBJ, EXAM>::resolveObjectForExamination(const EXAM *const ptrexam)
//		{
//			if (Doctor::isDebugMode())
//			{
//				if (_inverse_map().find(ptrexam) == _inverse_map().end())
//				{
//					Doctor::exceptWithReason("The examination is not yet registered for any object.");
//				}
//				
//				return	_inverse_map().at(ptrexam);
//			}
//			else
//			{
//				Doctor::exceptWithReason("This method should not be called in release build.");
//				return	nullptr;
//			}
//		}
//		
//		template<typename OBJ, typename EXAM>
//		std::unordered_map<OBJ const*, EXAM const*>&
//		Doctor::Examination<OBJ, EXAM>::_map()
//		{
//			static	std::unordered_map<OBJ const*, EXAM const*>	_m;
//			return	_m;
//		}
//		template<typename OBJ, typename EXAM>
//		std::unordered_map<EXAM const*, OBJ const*>&
//		Doctor::Examination<OBJ, EXAM>::_inverse_map()
//		{
//			static	std::unordered_map<EXAM const*, OBJ const*>	_m;
//			return	_m;
//		}
//		
//		
//		
//		
//		
//		
//		
//	}
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
//}}}}
//
//
//
































//#pragma mark	-	Description Implementation
//#include "../Server/Program.h"
//#include "../Server/ProgramSlotV1.h"
//EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
//namespace
//Debugging
//{
//	template<typename T>
//	std::string const
//	Doctor::describe(const T &object)
//	{
//		return	stringWithCFormat("(???? (address 0x%llx))", uint64_t(uintptr_t(&object)));
//	}
//	template<typename T>
//	std::string const
//	Doctor::describeVector(const std::vector<T> &vector)
//	{
//		std::string	str	=	"";
//		for (T const& v : vector)
//		{
//			str			+=	"\t";
//			str			+=	describe<T>(v);
//			str			+=	"\n";
//		}
//		return	stringWithCFormat("(std::vector<?> (address 0x%llx) (\n%s\n))", uint64_t(uintptr_t(&vector)), str.c_str());
//	}
//}
//EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END
//	







