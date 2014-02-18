//
//  _PackSerializerA.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/26/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics___PackSerializerA__
#define __EonilGraphics___PackSerializerA__


#include "_PackNodeA.h"
#include "../Debugging/Doctor.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Transcoding
	{

	
	
	
	
	
		
		
		
		
		
		
		
		
		
		
		
		
		class
		_PackSerializerA
		{
			union
			Number
			{
				uint32_t	value;
				char		bytes[4];
			}
			__attribute__((__packed__));
		public:
			
			uint32_t const		readNumber(std::istream& s)
			{
				static_assert(sizeof(Number) == 4, "");
				
				Number	n;
				s.read(n.bytes, sizeof(n));
				_PACK_ASSERT(s.good());
				_PACK_ASSERT(not s.fail());
				_PACK_ASSERT(not s.bad());
				_PACK_ASSERT(not s.eof());
				
				return	n.value;
			}
			
			std::string const	readStringByLength(std::istream& s, Size const len)
			{
				char*			buf		=	(char*)malloc(len+1);
				std::streamsize	ss		=	std::streamsize(len);
				
				s.read(buf, ss);
				_PACK_ASSERT(not s.eof());
				_PACK_ASSERT(not s.fail());
				_PACK_ASSERT(not s.bad());
				_PACK_ASSERT(s.good());
				
				buf[len]	=	'\0';	//	For safety.
				std::string	str	=	buf;
				_PACK_ASSERT(str.length() == strlen(buf));
				//				_PACK_ASSERT(str.length() != 0);
				
				free(buf);
				return	str;
			}
			void	readFixedString(std::istream& s, std::string const string)
			{
				std::string	r0	=	readStringByLength(s, string.length());
				_PACK_ASSERT(r0 == string);
			}
			std::string const	readString(std::istream& s)
			{
				uint32_t	len			=	readNumber(s);
				return		readStringByLength(s, len);
			}
			Legacy2013SharedMemory const	readData(std::istream& s)
			{
				uint32_t	nonull	=	readNumber(s);
				if (nonull == 0)
				{
					return	nullptr;
				}
				
				////
				
				uint32_t	len		=	readNumber(s);
				char*		mem		=	(char*)malloc(len);
				s.read(mem, len);
				_PACK_ASSERT(s.good());
				_PACK_ASSERT(not s.fail());
				_PACK_ASSERT(not s.bad());
				_PACK_ASSERT(not s.eof());
				
				return	Legacy2013SharedMemory::Factory::memoryByOwningRange(mem, len);
			}
			
			void
			writeNumber(std::ostream& s, uint32_t const v)
			{
				Number	n;
				n.value	=	v;
				s.write(n.bytes, sizeof(Number));
				_PACK_ASSERT(s.good());
				_PACK_ASSERT(not s.fail());
				_PACK_ASSERT(not s.bad());
				_PACK_ASSERT(not s.eof());
			}
			void
			writeString(std::ostream& s, std::string const v)
			{
				_PACK_ASSERT(v.length() < std::numeric_limits<uint32_t>::max());
				
				writeNumber(s, uint32_t(v.length()));
				char const*	cstr	=	v.c_str();
				size_t		len		=	strlen(cstr);
				
				_PACK_ASSERT(len < std::numeric_limits<std::streamsize>::max());
				s.write(cstr, std::streamsize(len));
				
				_PACK_ASSERT(s.good());
				_PACK_ASSERT(not s.fail());
				_PACK_ASSERT(not s.bad());
				_PACK_ASSERT(not s.eof());
			}
			void
			writeFixedString(std::ostream& s, std::string const v)
			{
				_PACK_ASSERT(v.length() < std::numeric_limits<uint32_t>::max());
				
				char const*	cstr	=	v.c_str();
				size_t		len		=	strlen(cstr);
				
				_PACK_ASSERT(len < std::numeric_limits<std::streamsize>::max());
				s.write(cstr, std::streamsize(len));
				
				_PACK_ASSERT(s.good());
				_PACK_ASSERT(not s.fail());
				_PACK_ASSERT(not s.bad());
				_PACK_ASSERT(not s.eof());
			}
			void
			writeData(std::ostream& s, Legacy2013SharedMemory const v)
			{
				_PACK_ASSERT(v == nullptr or v.length() < std::numeric_limits<uint32_t>::max());
				writeNumber(s, v == nullptr ? 0 : 1);
				
				if (v != nullptr)
				{
					writeNumber(s, uint32_t(v.length()));
					_PACK_ASSERT(v.length() < std::numeric_limits<std::streamsize>::max());
					s.write((char*)v.address(), std::streamsize(v.length()));
				}
				
				_PACK_ASSERT(s.good());
				_PACK_ASSERT(not s.fail());
				_PACK_ASSERT(not s.bad());
				_PACK_ASSERT(not s.eof());
			}
			
			
			
			
			
			
			
			void
			verifyHeader(std::istream& s)
			{
				readFixedString(s, "[PACK TREE]");
			}
			void
			verifyFooter(std::istream& s)
			{
				readFixedString(s, "+END+");
			}
			void
			writeHeader(std::ostream& s)
			{
				writeFixedString(s, "[PACK TREE]");
			}
			void
			writeFooter(std::ostream& s)
			{
				writeFixedString(s, "+END+");
				
				/*!
				 EOF prevention sentinel. This is 4 bytes of 0xFF.
				 Some OS - such as iOS - marks EOF if it arrives at the end of stream. 
				 Assertions will fail at there, so is intentionally put to avoid that situiation.
				 So do not read this when deserializing.
				 */
				writeNumber(s, 0xFFFFFFFF);
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			bool	useDebuggingMarker	=	false;
			
			void
			readDebuggingMarkerString(std::istream& s, std::string const string)
			{
				if (useDebuggingMarker)
				{
					readFixedString(s, string);
				}
			}
			void
			writeDebuggingMarkerString(std::ostream& s, std::string const string)
			{
				if (useDebuggingMarker)
				{
					writeFixedString(s, string);
				}
			}
			
			std::shared_ptr<_PackNodeA>
			deserialize(std::istream& s)
			{
//					std::streampos	pos	=	s.tellg();
//					Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::log("NODE POS = " + std::to_string(pos));
//					if (pos == 1189652)
//					{
//						
//					}
				
				//	Single rooted subtree.
				_PackNodeA*	rt	=	new _PackNodeA();
				readDebuggingMarkerString(s, "<NAME>");
				rt->name()	=	readString(s);
				
				readDebuggingMarkerString(s, "<DATA>");
				rt->data()	=	readData(s);
				
				readDebuggingMarkerString(s, "<SUBPACKS>");
				uint32_t	snc	=	readNumber(s);
				
				for (uint32_t i=0; i<snc; i++)
				{
					readDebuggingMarkerString(s, "<ATOM>");
					rt->addSubpack(deserialize(s));
				}
				return	std::shared_ptr<_PackNodeA>(rt);
			}
			void
			serialize(_PackNodeA& tree, std::ostream& s)
			{
				writeDebuggingMarkerString(s, "<NAME>");
				writeString(s, tree.name());
				
				writeDebuggingMarkerString(s, "<DATA>");
				writeData(s, tree.data());
				
				writeDebuggingMarkerString(s, "<SUBPACKS>");
				Size		snc	=	tree.numberOfSubpacks();
				uint32_t	n2	=	uint32_t(snc);
				
				writeNumber(s, n2);
				for (Size i=0; i<snc; i++)
				{
					writeDebuggingMarkerString(s, "<ATOM>");
					_PackNodeA&	subtree	=	tree.subpackAtIndex(i);
					serialize(subtree, s);
				}
			}
		};
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
	
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics___PackSerializerA__) */
