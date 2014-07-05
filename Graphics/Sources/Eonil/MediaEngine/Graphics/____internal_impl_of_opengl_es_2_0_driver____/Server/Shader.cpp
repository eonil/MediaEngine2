//
//  Shader.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "../Stub/GL.h"
#include "Shader.h"

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Server
{
	using namespace Stub;
	
	
	VertexShader::VertexShader(str const& sourceCode) : _name(eeglCreateShader(GL_VERTEX_SHADER)), _mapping()
	{
		eeglShaderSourceString(_name, sourceCode);
		eeglCompileShader(_name);
	}
	VertexShader::VertexShader(str const& sourceCode, NameChannelMap const& mapping) : _name(eeglCreateShader(GL_VERTEX_SHADER)), _mapping(mapping)
	{
		eeglShaderSourceString(_name, sourceCode);
		eeglCompileShader(_name);
	}
	VertexShader::~VertexShader()
	{
		eeglDeleteShader(_name);
	}
	
	
	
	
	auto VertexShader::
	empty() const -> bool
	{
		return	_name == NULL_GL_NAME();
	}
	auto VertexShader::
	name() const -> GLuint
	{
		return	_name;
	}
	auto VertexShader::
	attributeNamesForChannelsMapping() const -> VertexShader::NameChannelMap const&
	{
		return	_mapping;
	}
	auto VertexShader::
	sourceCode() const -> str
	{
		return	eeglGetShaderSourceString(name());
	}
	
	auto VertexShader::
	operator==(const VertexShader &other) const -> bool
	{
		return	_name == other._name;
	}
	auto VertexShader::
	operator!=(const VertexShader &other) const -> bool
	{
		return	_name != other._name;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	FragmentShader::FragmentShader(str const& sourceCode) : _name(eeglCreateShader(GL_FRAGMENT_SHADER))
	{
		eeglShaderSourceString(_name, sourceCode);
		eeglCompileShader(_name);
	}
	FragmentShader::~FragmentShader()
	{
		eeglDeleteShader(_name);
	}

	auto FragmentShader::
	empty() const -> bool
	{
		return	_name == NULL_GL_NAME();
	}
	auto FragmentShader::
	name() const -> GLuint
	{
		return	_name;
	}
	
	auto FragmentShader::
	sourceCode() const -> str
	{
		return	eeglGetShaderSourceString(_name);
	}
	auto FragmentShader::
	description() const -> str
	{
		uint64_t	addr	=	(uintptr_t)this;
		uint64_t	name	=	_name;
		return		"<FragmentShader: 0x" + heximize(addr) + ", name = " + std::to_string(name) + ">";
	}
	auto
	FragmentShader::operator==(const FragmentShader &other) const -> bool
	{
		return	_name == other._name;
	}
	auto
	FragmentShader::operator!=(const FragmentShader &other) const -> bool
	{
		return	_name != other._name;
	}
}







INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END

