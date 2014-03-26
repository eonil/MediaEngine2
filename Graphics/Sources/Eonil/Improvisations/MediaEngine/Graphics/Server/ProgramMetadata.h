//
//  ProgramMetadata.h
//  Graphics
//
//  Created by Hoon H. on 3/24/14.
//
//

#ifndef __Graphics__ProgramMetadata__
#define __Graphics__ProgramMetadata__

#include "../Common.h"
#include "Declarations.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
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
			
			auto	allUniformValueSlots() const -> vec<ParameterSlotDescription>;
			auto	allVertexAttributeSlots() const -> vec<ParameterSlotDescription>;
		};
		
		
		
		
		
		
		
		
		
	}
	
}}}}

#endif /* defined(__Graphics__ProgramMetadata__) */
