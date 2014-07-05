//
//  ProgramMetadata.h
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
	 Queries reflective metadata of a program's parameters.
	 */
	class
	ProgramMetadata
	{
		GLuint	_pname	{};
		
	public:
		struct
		ParameterSlotDescription
		{
			GLuint	index		{};
			str		name		{};
			GLenum	type		{};
			GLint	size		{};
			GLint	location	{};
			
			auto	stringify() const -> str;
		};
		
	private:
		vec<ParameterSlotDescription>	_us{};
		vec<ParameterSlotDescription>	_vs{};
		
	public:
		ProgramMetadata(GLuint const programName);
		
		auto	allProgramUniformValueSlotProxys() const -> vec<ParameterSlotDescription>;
		auto	allProgramVertexAttributeSlotProxys() const -> vec<ParameterSlotDescription>;
	};
	
	
	
	
	
	
	
	
	
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END
