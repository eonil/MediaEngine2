//
//  _PackA.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/26/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "_PackA.h"







namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Transcoding
	{
		
		
		
		
		
		
		
		
		
		
			

		
		_PackA::_PackA() : _code(Type::CODE::NONE), _ptr(nullptr)
		{
		}
		_PackA::_PackA(decltype(nullptr) const null) : _code(Type::CODE::NONE), _ptr(nullptr)
		{
		}
		
		
		_PackA::_PackA(Legacy2013SharedMemory const v) : _code(Type::CODE::DATA), _ptr(new Legacy2013SharedMemory(v))
		{
		}
		_PackA::_PackA(std::string const v) : _code(Type::CODE::STRING), _ptr(new std::string(v))
		{
		}
		_PackA::_PackA(uint32_t const v) : _code(Type::CODE::UINT32), _ptr(new uint32_t(v))
		{
		}
		_PackA::_PackA(float const v) : _code(Type::CODE::FLOAT32), _ptr(new float(v))
		{
		}
		
		_PackA::_PackA(_PackA const& p) : _code(p._code), _ptr(p._ptr)
		{
		}
		_PackA::~_PackA()
		{
			switch(_code)
			{
				case
				Type::CODE::NONE:
				{
					_PACK_ASSERT(_ptr == nullptr);
				}
				case	Type::CODE::DATA:		{	delete (Legacy2013SharedMemory*)_ptr;	}
				case	Type::CODE::STRING:		{	delete (std::string*)_ptr;	}
				case	Type::CODE::UINT32:		{	delete (uint32_t*)_ptr;	}
				case	Type::CODE::FLOAT32:	{	delete (float*)_ptr;	}
			}
		}


		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		_PackA&
		_PackA::operator=(_PackA p)
		{
			std::swap(_code, p._code);
			std::swap(_ptr, p._ptr);
			return	*this;
		}
		
		_PackA::Type::CODE const
		_PackA::typecode() const
		{
			return	_code;
		}
		
		Legacy2013SharedMemory const&
		_PackA::dataValue() const
		{
			return	*(Legacy2013SharedMemory*)_ptr;
		}
		std::string const&
		_PackA::stringValue() const
		{
			return	*(std::string*)_ptr;
		}
		uint32_t const
		_PackA::uint32Value() const
		{
			return	*(uint32_t*)_ptr;
		}
		float const
		_PackA::float32Value() const
		{
			return	*(float*)_ptr;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		namespace
		{
//			using	Pair	=	std::pair<std::string, _PackA::Type::CODE>;
//			std::map<std::string, _PackA::Type::CODE> const&
//			codeMapping()
//			{
//				static	std::map<std::string, _PackA::Type::CODE>	_m	=
//				{
//					Pair("NUL ", _PackA::Type::CODE::NONE),
//					Pair("BIN ", _PackA::Type::CODE::DATA),
//					Pair("STR ", _PackA::Type::CODE::STRING),
//					Pair("U32 ", _PackA::Type::CODE::UINT32),
//					Pair("F32 ", _PackA::Type::CODE::FLOAT32),
//				};
//				return	_m;
//			}
			
//			Pair const
//			pairByString(std::string const s)
//			{
//				for (Pair const& p : codeMapping())
//				{
//					if (p.first == s)
//					{
//						return	p;
//					}
//				}
//				throw	"Bad string.";
//			}
//			Pair const
//			pairByCode(_PackA::Type::CODE const c)
//			{
//				for (Pair const& p : codeMapping())
//				{
//					if (p.second == c)
//					{
//						return	p;
//					}
//				}
//				throw	"Bad code.";
//			}
			
			
			
			
			
			
			
			
			
//			
//			
//			union
//			B4
//			{
//				uint32_t	u32;
//				float		f32;
//				char		bytes[4];
//			};
//			
//			
//			std::string const
//			stringFromMemory(Memory const m)
//			{
//				char*	bs	=	(char*)m.address();
//				size_t	len	=	m.length();
//				
//				for (size_t i=0; i<len; i++)
//				{
//					
//				}
//			}
//			std::string const
//			stringFromB4(std::string const s)
//			{
//			}
		}
		
		
//		std::string const
//		_PackA::Utility::stringRepresentationOfPack(const Eonil::Resource::_PackA p)
//		{
//			std::string	codestr	=	pairByCode(p._code).first;
//			
//		}
		
	
	

		
		
		
		
	}
	
	
	
	
	
	
	
	
}}}}
