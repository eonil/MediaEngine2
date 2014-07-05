//
//  XML.h
//  Aliens
//
//  Created by Hoon H. on 14/4/27.
//
//

#pragma once

#include "Common.h"
#include "../../pugixml.hpp"

EONIL_ALIENS_NAMESPACE_BEGIN





/*!
 XML document access.
 */
class
XML
{
public:
	class
	Exception : public std::logic_error
	{
	public:
		using	logic_error::logic_error;
	};
	
public:
	class
	Node
	{
		
	};
	
	class
	Attribute
	{
		
	};
	
	class
	Element
	{
	};
	
	class
	Document
	{
		pugi::xml_document		_doc	{};
	};
};









EONIL_ALIENS_NAMESPACE_END