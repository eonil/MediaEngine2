//
//  _PackNodeAA.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/26/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "_PackNodeA.h"








namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Transcoding
	{
		

		
		
		
		
		
		
		
		
		
		
			
		namespace
		{
			bool const
			dataEquality(Legacy2013SharedMemory const& a, Legacy2013SharedMemory const& b)
			{
				return	(a == nullptr and b == nullptr) or
						(a != nullptr and b != nullptr and a.length() == b.length() and memcmp(a.address(), b.address(), a.length()) == 0);
			}
			bool const
			vectorEquality(std::vector<std::shared_ptr<_PackNodeA>>& a, std::vector<std::shared_ptr<_PackNodeA>>& b)
			{
				if (a.size() != b.size())
				{
					return	false;
				}
				for (Size i=0; i<a.size(); i++)
				{
					_PackNodeA	a1	=	*(a.at(i));
					_PackNodeA	b1	=	*(b.at(i));
					
					if (a1 != b1)
					{
						return	false;
					}
				}
				return	true;
			}
		}
		
		bool const
		_PackNodeA::operator==(_PackNodeA &p)
		{
			_PACK_ASSERT(this != nullptr);
			return	name() == p.name() and dataEquality(data(), p.data()) and vectorEquality(_subpcks, p._subpcks);
		}
		bool const
		_PackNodeA::operator!=(_PackNodeA &p)
		{
			return	not (*this == p);
		}
		
		
		
		
		std::string&
		_PackNodeA::name()
		{
			_PACK_ASSERT(this != nullptr);
			return	_name;
		}
		Legacy2013SharedMemory&
		_PackNodeA::data()
		{
			_PACK_ASSERT(this != nullptr);
			return	_data;
		}
//		UniqueByteMemoryBlock
//		_PackNodeA::data2()
//		{
//			_PACK_ASSERT(this != nullptr);
//			return	_data;
//		}
		
		Size const
		_PackNodeA::numberOfSubpacks()
		{
			return	_subpcks.size();
		}
		_PackNodeA&
		_PackNodeA::subpackAtIndex(Size const index)
		{
			return	*_subpcks.at(index);
		}
		_PackNodeA&
		_PackNodeA::firstSubpack()
		{
			return	*_subpcks.front();
		}
		_PackNodeA&
		_PackNodeA::lastSubpack()
		{
			return	*_subpcks.back();
		}

//		std::vector<_PackNodeA&>&
//		_PackNodeA::_subpcks
//		{
//			_PACK_ASSERT(this != nullptr);
//			std::vector<_PackNodeA&>	_refs;
//			for (std::shared_ptr<_PackNodeA> const& p : _subpcks)
//			{
//				_refs.push_back(*p);
//			}
//			return	_refs;
//		}
		
		
		
		
		
		_PackNodeA&
		_PackNodeA::addSubpack()
		{
			_PACK_ASSERT(this != nullptr);
			_subpcks.push_back(Box(new _PackNodeA()));
			return	lastSubpack();
		}
		void
		_PackNodeA::addSubpack(std::shared_ptr<_PackNodeA> p)
		{
			_PACK_ASSERT(this != nullptr);
			_subpcks.push_back(p);
		}
		
		
		
		
		
		
		bool const
		_PackNodeA::hasSubpackForName(std::string const name)
		{
			_PACK_ASSERT(this != nullptr);
			_PACK_ASSERT(name.length() > 0);
			
			for (Box& p : _subpcks)
			{
				if (p->name() == name)
				{
					return	true;
				}
			}
			return	false;
		}
		
		
		Size const
		_PackNodeA::indexOfSubpackForName(std::string name)
		{
			_PACK_ASSERT(this != nullptr);
			_PACK_ASSERT(name.length() > 0);
			
			for (Size i=0; i<_subpcks.size(); i++)
			{
				_PackNodeA&	p	=	subpackAtIndex(i);
				if (p.name() == name)
				{
					return	i;
				}
			}
			throw	"Illegal access.";
		}
		
		
		_PackNodeA&
		_PackNodeA::subpackForName(std::string const name, bool const createIfNotExist)
		{
			_PACK_ASSERT(this != nullptr);
			_PACK_ASSERT(name.length() > 0);
			if (createIfNotExist and not hasSubpackForName(name))
			{
				addSubpackForName(name);
			}
			return	subpackAtIndex(indexOfSubpackForName(name));
		}
		_PackNodeA&
		_PackNodeA::addSubpackForName(const std::string name)
		{
			_PACK_ASSERT(this != nullptr);
			_PACK_ASSERT(not hasSubpackForName(name));
			_PackNodeA*	p	=	new _PackNodeA();
			p->name()		=	name;
			_subpcks.push_back(Box(p));
			return	lastSubpack();
		}
		void
		_PackNodeA::removeSubpackForName(const std::string name)
		{
			_PACK_ASSERT(this != nullptr);
			_PACK_ASSERT(hasSubpackForName(name));
			intptr_t	dt	=	intptr_t(indexOfSubpackForName(name));
			_subpcks.erase(_subpcks.begin() + dt);
		}
		Legacy2013SharedMemory const&
		_PackNodeA::dataForSubpackWithName(std::string const name)
		{
			static Legacy2013SharedMemory const		null	=	nullptr;
			
			_PACK_ASSERT(this != nullptr);
			_PACK_ASSERT(name.length() > 0);
			
			for (Size i=0; i<_subpcks.size(); i++)
			{
				_PackNodeA&	p	=	subpackAtIndex(i);
				if (p.name() == name)
				{
					return	p.data();
				}
			}
			return	null;
		}
//		UniqueByteMemoryBlock
//		_PackNodeA::dataForSubpackWithName2(std::string const name)
//		{
//			static Legacy2013SharedMemory const		null	=	nullptr;
//			
//			_PACK_ASSERT(this != nullptr);
//			_PACK_ASSERT(name.length() > 0);
//			
//			for (Size i=0; i<_subpcks.size(); i++)
//			{
//				_PackNodeA&	p	=	subpackAtIndex(i);
//				if (p.name() == name)
//				{
//					return	p.data2();
//				}
//			}
//			return	{};
//		}

		void
		_PackNodeA::setDataForSubpackWithName(const Eonil::Improvisations::MediaEngine::Foundation::_Legacy2013::SharedMemory data, const std::string name)
		{
			_PACK_ASSERT(this != nullptr);
			_PACK_ASSERT(name.length() > 0);
			
			if (data == nullptr)
			{
				if (hasSubpackForName(name))
				{
					removeSubpackForName(name);
				}
			}
			else
			{
				if (hasSubpackForName(name))
				{
					subpackForName(name).data()	=	data;
				}
				else
				{
					subpackForName(name, true).data()	=	data;
				}
			}
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		namespace
		{
			union
			B4
			{
				uint32_t	asUInt32;
				float		asFloat32;
				char		bytes[4];
			};
		}
		
		std::string const
		_PackNodeA::stringForSubpackWithName(const std::string name)
		{
			Legacy2013SharedMemory	d0	=	dataForSubpackWithName(name);
			char*	d1	=	(char*)d0.address();
			
			_PACK_ASSERT(d1[d0.length()-1] == 0);
			_PACK_ASSERT(strlen(d1) == d0.length()-1);
			return	std::string(d1, d0.length()-1);
		}
		uint32_t const
		_PackNodeA::uint32ForSubpackWithName(const std::string name)
		{
			Legacy2013SharedMemory	d0	=	dataForSubpackWithName(name);
			_PACK_ASSERT(d0.length() == sizeof(B4));
			
			B4*		b4	=	(B4*)d0.address();
			return	b4->asUInt32;
		}
		float const
		_PackNodeA::float32ForSubpackWithName(const std::string name)
		{
			Legacy2013SharedMemory	d0	=	dataForSubpackWithName(name);
			_PACK_ASSERT(d0.length() == sizeof(B4));
			
			B4*		b4	=	(B4*)d0.address();
			return	b4->asFloat32;
		}
		
		
		
		
		
		
		
		void
		_PackNodeA::setStringForSubpackWithName(const std::string value, std::string name)
		{
			char const*	c0	=	value.c_str();
			size_t	len		=	value.length();
			_PACK_ASSERT(len == strlen(c0));
			_PACK_ASSERT(c0[len] == 0);
			Legacy2013SharedMemory	m1	=	Legacy2013SharedMemory::Factory::memoryByCopyingRange(c0, len+1);
			
			setDataForSubpackWithName(m1, name);
		}
		void
		_PackNodeA::setUInt32ForSubpackWithName(const uint32_t value, std::string name)
		{
			B4*		b4	=	new B4();
			b4->asUInt32	=	value;
			Legacy2013SharedMemory	m1	=	Legacy2013SharedMemory::Factory::memoryByCopyingRange(b4, sizeof(B4));
			setDataForSubpackWithName(m1, name);
		}
		void
		_PackNodeA::setFloat32ForSubpackWithName(const float value, std::string name)
		{
			B4*		b4	=	new B4();
			b4->asFloat32	=	value;
			Legacy2013SharedMemory	m1	=	Legacy2013SharedMemory::Factory::memoryByCopyingRange(b4, sizeof(B4));
			setDataForSubpackWithName(m1, name);
		}
		
		
		
		
		
		
		
		
		
		
		
		
	}
	
	
	
	
	
	
	
	
}}}}


