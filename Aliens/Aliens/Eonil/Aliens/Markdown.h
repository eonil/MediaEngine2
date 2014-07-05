//
//  Markdown.h
//  Aliens
//
//  Created by Hoon H. on 14/4/27.
//
//

#pragma once

#include "Common.h"

EONIL_ALIENS_NAMESPACE_BEGIN





/*!
 Markdown code compiler into HTML.
 */
class
Markdown
{
public:
	class
	Exception : public std::logic_error
	{
	public:
		using	logic_error::logic_error;
	};
	
public:
	/*!
	 Generates HTML string from Markdown string.
	 
	 @result
	 Generated HTML source code string.
	 
	 @exception
	 An `Exception` instance will be thrown on any exception.
	 Guarantees strong exception safety.
	 
	 @note
	 Empty input will generate empty output.
	 */
	static auto	process(std::string const& text) -> std::string;
};









EONIL_ALIENS_NAMESPACE_END