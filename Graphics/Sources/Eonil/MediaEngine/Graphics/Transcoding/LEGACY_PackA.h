//
//  _PackA.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/26/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics___PackA__
#define __EonilGraphics___PackA__


#include <map>
#include <vector>
#include <iostream>

#include "../Common.h"
#include "../LEGACY/LEGACY_Common.h"

#define	_PACK_ASSERT(cond)		{ if (not (cond)) throw "ASSERTION FAILURE!"; }








namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Transcoding
	{
		
		using namespace Eonil::Improvisations::MediaEngine::Foundation;
		
		
		
		class
		_PackA
		{
		public:
			struct
			Type
			{
				enum
				CODE
				{
					NONE	=	0,			//	Means null.
					DATA	=	101,
					STRING	=	102,
					UINT32	=	103,
					FLOAT32	=	104,
				};
			};
			
		public:
			_PackA();
			_PackA(decltype(nullptr) const null);
			_PackA(Legacy2013SharedMemory const v);
			_PackA(std::string const v);
			_PackA(uint32_t const v);
			_PackA(float const v);

			_PackA(_PackA const& p);
			~_PackA();
			
			_PackA&	operator=(_PackA p);
			
			Type::CODE const	typecode() const;
			
			Legacy2013SharedMemory const&		dataValue() const;
			std::string const&	stringValue() const;
			uint32_t const		uint32Value() const;
			float const			float32Value() const;
			
			
			
//			struct
//			Utility
//			{
//				static std::string const		stringRepresentationOfPack(_PackA const p);
//				static _PackA const				packRepresentationOfString(std::string const s);
//				
//				static Memory const				dataRepresentationOfPack(_PackA const p);
//				static _PackA const				packRepresentationOfData(Memory const m);
//			};
			
		private:
			Type::CODE			_code;
			void*				_ptr;
		};
		

		
		
		
		
		
		
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics___PackA__) */
