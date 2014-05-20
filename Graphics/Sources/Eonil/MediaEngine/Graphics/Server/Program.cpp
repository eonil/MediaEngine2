//
//  Program.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "Program.h"

#include "../Stub/GL.h"
#include "../Debugging/Doctor.h"
#include "ImplementationCommon.h"

#include "Shader.h"
#include "ProgramParameterLocation.h"
#include "Machinery/VertexAttributeChannel.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Server
	{
		using namespace Debugging;
		using namespace Stub;
		
		
		
		
		
		
		
		
		
		
		
		auto
		Program::
		_search_uniform_location(const str &name) const -> GLint
		{
			GLint	loc2	=	Stub::eeglGetUniformLocation(_name, toGLchar(name));
			if (loc2 != -1)
			{
				return	loc2;
			}
			Doctor::exceptWithReason("Uniform value slot for the name does not exist.");
		}
		auto
		Program::
		_search_vertex_attribute_location(const str &name) const -> GLint
		{
			GLint	loc2	=	Stub::eeglGetAttribLocation(_name, toGLchar(name));
			if (loc2 != -1)
			{
				return	loc2;
			}
			Doctor::exceptWithReason("Uniform value slot for the name does not exist.");
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		Program::Program(VertexShader const& vertexShader, FragmentShader const& fragmentShader)
		{
			Debug::ObjectInstanceAddressTracker<Program>::registerObjectAddress(this);
			
			_name		=	eeglCreateProgram();
//			printf("Program created: %u\n", name);
			
			////
			
			//	Prebind all the vertex-channels(generic vertex attribute indexes) to program's vertex attribute slots.
			{
				for (auto const& mapping : vertexShader.attributeNamesForChannelsMapping())
				{
					eeglBindAttribLocation(name(), mapping.second->index(), mapping.first.c_str());
					_vertexChannelsForAttributesMapping.insert(mapping);
				}
			};
			
			eeglAttachShader(name(), vertexShader.name());
			eeglAttachShader(name(), fragmentShader.name());
			eeglLinkProgram(name());
			
			////
			
//				printf("shader count = %u\n", eeglGetProgrami(name(), GL_ATTACHED_SHADERS));				
////				printf("program = %s\n", Debugging::Doctor::describe(*this).c_str());
			
			////
			
//				if (Doctor::useStateValidation())
//				{
//					for (std::string const& s : vertexShader.attributeNames())
//					{
//					}
//				}
		}
		Program::~Program()
		{
			eeglDeleteProgram(_name);
//			printf("Program deleted: %u\n", name);
			
			Debug::ObjectInstanceAddressTracker<Program>::unregisterObjectAddress(this);
		}
		
		
		
		
		
		
		////
		
		
		auto Program::
		operator==(const Eonil::Improvisations::MediaEngine::Graphics::Server::Program &other) const -> bool
		{
			return	_name == other._name;
		}
		auto Program::
		operator!=(const Eonil::Improvisations::MediaEngine::Graphics::Server::Program &other) const -> bool
		{
			return	_name != other._name;
		}
		
		
		
		
		
		
		
		
		
		auto Program::
		empty() const -> bool
		{
			return	_name == NULL_GL_NAME();
		}
		auto Program::
		name() const -> GLuint
		{
			_assertNonEmptyState();
			
			return	_name;
		}
		
		
		
		
		
		
		
				
		
		
		
		
		
		auto Program::
		uniformValueSlotForName(const str &name) const -> local<ProgramUniformValueSlotProxy const>
		{
			ProgramParameterLocation	p1	{_name, _search_uniform_location(name)};
			ProgramUniformValueSlotProxy			s2	{p1};
			
			return	{s2};
		}
		auto Program::
		uniformValueSlotForName(const str &name) -> local<ProgramUniformValueSlotProxy>
		{
			ProgramParameterLocation	p1	{_name, _search_uniform_location(name)};
			ProgramUniformValueSlotProxy			s2	{p1};
			
			return	{s2};
		}
		auto Program::
		vertexAttributeSlotForName(const str &name) const -> local<ProgramVertexAttributeSlotProxy const>
		{
			ProgramParameterLocation	p1	{_name, _search_vertex_attribute_location(name)};
			ProgramVertexAttributeSlotProxy			s2	{p1};
			
			return	{s2};
		}
		auto Program::
		vertexAttributeSlotForName(const str &name) -> local<ProgramVertexAttributeSlotProxy>
		{
			ProgramParameterLocation	p1	{_name, _search_vertex_attribute_location(name)};
			ProgramVertexAttributeSlotProxy			s2	{p1};
			
			return	{s2};
		}
		
		
		
		
		
		
		
		auto Program::
		_assertNonEmptyState() const -> void
		{
			EEGL_ASSERT(_name != NULL_GL_NAME());
		}
		
		
		

		
		
		
		
		
		
		
		
		

		
		
		auto Program::Utility::
		shaderCodeForLegacyPlatformsWhichDoNotSupportPrecision(const str &code) -> str
		{
			static std::string const	prefix	=
			"#define	highp					\n"
			"#define	mediump					\n"
			"#define	lowp					\n"
//			"#line		0						\n"
			;
		
			return	prefix + code;
		}
		
		
		
		
		
	}


	
	
	
	
	
	
}}}}
