//
//  _PackNodeAA.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/26/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics___PackNodeAA__
#define __EonilGraphics___PackNodeAA__


#include "../Common.h"
#include "_PackA.h"






namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Transcoding
	{
		
		
			
		
		
		using namespace	Eonil::Improvisations::MediaEngine::Foundation;
//			using namespace	Eonil::Resource;
		
		
		
//		
//		class	_PackNodeA;
//		class	_PackNodeListA;
//		
//		
//		class
//		_PackNodeListA
//		{
//		public:
//		private:
//			std::vector
//		};
		
		
		
		
		
		
		
		
		
		/*!
		 Supports little endian only.
		 
		 Subpacks are completely created/destoryed by super-pack.
		 */
		class
		_PackNodeA
		{
		public:
			
			bool const		operator==(_PackNodeA& p);		//!	Performs deep equality comparison.
			bool const		operator!=(_PackNodeA& p);		//!	Performs deep equality comparison.
			
			
			
			std::string&	name();			//!	Name can be zero-length in case of array form.
			auto	data() -> Legacy2013SharedMemory&;
//			auto	data2() -> UniqueByteMemoryBlock;
			
//			std::vector<_PackNodeA&>&	subpacks();
			
			Size const		numberOfSubpacks();
			_PackNodeA&		subpackAtIndex(Size const index);
			_PackNodeA&		firstSubpack();
			_PackNodeA&		lastSubpack();
			
			_PackNodeA&		addSubpack();
			void			addSubpack(std::shared_ptr<_PackNodeA> p);
//			void			removeSubpackAtIndex(Size const index);
			
//			std::vector<_PackNodeA&>	allSubpacks();
			
			////			Name based access.
			bool const		hasSubpackForName(std::string const name);
			Size const		indexOfSubpackForName(std::string name);									//!	It's illegal to call this with subpack name which is not exist.
			_PackNodeA&		subpackForName(std::string const name, bool const createIfNotExist = false);	//!	It's illegal to call this with subpack name which is not exist.
			_PackNodeA&		addSubpackForName(std::string const name);									//!	It's illegal to call this with subpack name which is already exist.
			void			removeSubpackForName(std::string const name);								//!	It's illegal to call this with subpack name which is not exist.
			
			auto			dataForSubpackWithName(std::string const name) -> Legacy2013SharedMemory const&;								//!	Returns `nullptr` if subpack for the name does not exist.
//			auto			dataForSubpackWithName2(std::string const name) -> UniqueByteMemoryBlock;
			
			void			setDataForSubpackWithName(Legacy2013SharedMemory const data, std::string const name);		//!	If data is `nullptr`, the name will be deleted.
			
			std::string const	stringForSubpackWithName(std::string const name);						//!	Underlying string must have terminating NULL.
			uint32_t const	uint32ForSubpackWithName(std::string const name);
			float const		float32ForSubpackWithName(std::string const name);
			
			void			setStringForSubpackWithName(std::string const value, std::string name);		//!	Encoded string will have ending NULL.
			void			setUInt32ForSubpackWithName(uint32_t const value, std::string name);
			void			setFloat32ForSubpackWithName(float const value, std::string name);
			
		private:
			using	Box	=	std::shared_ptr<_PackNodeA>;
			
			std::string		_name	=	"";
			Legacy2013SharedMemory			_data	=	nullptr;
			std::vector<Box>	_subpcks;
		};
		
		
		
		
		
		
		
		
		
		
		
		
		
	}

	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics___PackNodeAA__) */
