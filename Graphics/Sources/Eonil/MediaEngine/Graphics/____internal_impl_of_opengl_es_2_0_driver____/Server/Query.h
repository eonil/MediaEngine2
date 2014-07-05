//
//  Query.h
//  Graphics
//
//  Created by Hoon H. on 3/24/14.
//
//

#pragma once
#include "Declarations.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

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
		auto	maximumVertexUniformVectorCount() const -> sz;
	};
	
	
	
	
	
	
	
	
	
	
	
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END
