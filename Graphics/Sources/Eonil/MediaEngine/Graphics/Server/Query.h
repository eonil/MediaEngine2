//
//  Query.h
//  Graphics
//
//  Created by Hoon H. on 3/24/14.
//
//

#ifndef __Graphics__Server__Query__
#define __Graphics__Server__Query__


#include "../Common.h"
#include "Declarations.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{

		
		
		
		
		
		/*!
		 Provides features to read data back from graphics server (GPU).
		 
		 @discussion
		 Any operation reading back from GPU is **very expensive**. There's no 
		 cheap way to do it because OpenGL is output-only API.
		 */
		class
		Query
		{
		public:
			auto	maximumVertexUniformVectorCount() const -> Size;
		};
		
		
		
		
		
		
		
		
		
		
		
	}
	
}}}}
	

#endif /* defined(__Graphics__Server__Query__) */
