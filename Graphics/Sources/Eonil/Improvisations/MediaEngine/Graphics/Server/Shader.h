//
//  Shader.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__Shader__
#define __EonilGraphics__Shader__

#include <string>
#include "../Common.h"
#include "Machinery/VertexAttributeChannel.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Server
	{
		/*!
		 
		 @discussion
		 The destructor is not virtual by default. Subclassing this class might be dangerous.
		 */
		class
		VertexShader final
		{
		public:
			using	NameChannelMap	=	map<str, Machinery::VertexAttributeChannel const&>;
			
		private:
			GLuint						_name		{NULL_GL_NAME()};
			NameChannelMap				_mapping	{};

		public:
//			VertexShader(str const& sourceCode, vec<str> const& attributeNames = {});
			
			/*!
			 This does not retain any input resources, so you can freely free them all.
			 */
			VertexShader(str const& sourceCode, NameChannelMap const& attributeNamesForChannelsMapping);
			VertexShader(VertexShader const&) = delete;
			~VertexShader();
			
			auto	operator==(VertexShader const& other) const		->	bool;
			auto	operator!=(VertexShader const& other) const		->	bool;
			
			auto	empty() const									->	bool;
			auto	name() const									->	GLuint;
			auto	attributeNamesForChannelsMapping() const		->	NameChannelMap const&;
			
			auto	sourceCode() const								->	str;
		};
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		/*!
		 
		 @discussion
		 The destructor is not virtual by default. Subclassing this class might be dangerous.
		 */
		class
		FragmentShader final
		{
			GLuint	_name	{NULL_GL_NAME()};
			
			
		public:
			FragmentShader(str const& sourceCode);
			FragmentShader(FragmentShader const&) = delete;
			~FragmentShader();
			
			auto	operator==(FragmentShader const& other) const	->	bool;
			auto	operator!=(FragmentShader const& other) const	->	bool;
			
			auto	empty() const									->	bool;
			auto	name() const									->	GLuint;
			auto	sourceCode() const								->	str;				//!	Returns internally keeping source code by GL driver.
			auto	description() const								->	str;			
		};
					
	}
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics__Shader__) */
