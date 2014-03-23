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
			
			GLint const		attrc	=	eeglGetProgrami(name(), GL_ACTIVE_ATTRIBUTES);
			GLint const		unic	=	eeglGetProgrami(name(), GL_ACTIVE_UNIFORMS);
			
			for (GLuint i=0; i<attrc; i++)
			{
				_vertexAttributeSlots.push_back(VertexAttributeSlotV1(name(), i));
			}
			for (GLuint i=0; i<unic; i++)
			{
				_uniformValueSlots.push_back(UniformValueSlotV1(name(), i));
			}
			
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
		
		
		
		
		
		
		
		
		
		
//		auto Program::
//		uniformsValueSlots() const -> GenericMemoryRange<UniformValueSlotV1 const>
//		{
//			return	{_uniformValueSlots.data(), _uniformValueSlots.data() + _uniformValueSlots.size()};
//		}
//		auto Program::
//		uniformsValueSlots() -> GenericMemoryRange<UniformValueSlotV1>
//		{
//			return	{_uniformValueSlots.data(), _uniformValueSlots.data() + _uniformValueSlots.size()};
//		}
		auto Program::
		searchUniformValueSlotV1ForName(const str &name) const -> UniformValueSlotV1 const*
		{
			return	((Program*)this)->searchUniformValueSlotV1ForName(name);
		}
		auto Program::
		searchUniformValueSlotV1ForName(const str &name) -> UniformValueSlotV1*
		{
			_assertNonEmptyState();
			
			for (UniformValueSlotV1& s : _uniformValueSlots)
			{
				if (s.name() == name)
				{
					return	&s;
				}
			}

			GLint	loc2	=	Stub::eeglGetUniformLocation(_name, toGLchar(name));
			if (loc2 != -1)
			{
				for (UniformValueSlotV1& s: _uniformValueSlots)
				{
					if (s.location() == loc2)
					{
						return	&s;
					}
				}
			}
			
			return	nullptr;
		}
		
		
		
		
		
		
		
		auto Program::
		uniformValueSlotForName(const str &name) const -> local<UniformValueSlot const>
		{
			ProgramParameterLocation	p1	{_name, _search_uniform_location(name)};
			UniformValueSlot			s2	{p1};
			
			return	{s2};
		}
		auto Program::
		uniformValueSlotForName(const str &name) -> local<UniformValueSlot>
		{
			ProgramParameterLocation	p1	{_name, _search_uniform_location(name)};
			UniformValueSlot			s2	{p1};
			
			return	{s2};
		}
		
		auto Program::
		allUniformValueSlotV1s() const -> vec<UniformValueSlotV1> const&
		{
			_assertNonEmptyState();
			
			return	_uniformValueSlots;
		}
		auto Program::
		uniformValueSlotAtIndex(Size const index) -> UniformValueSlotV1&
		{
			_assertNonEmptyState();
			
			return	_uniformValueSlots.at(index);
		}
		auto Program::
		indexOfUniformValueSlotV1ForName(const std::string name) const -> Size
		{
			auto const*	ptr	=	searchUniformValueSlotV1ForName(name);
			
			if (ptr == nullptr)
			{
				Doctor::exceptWithReason("Uniform value slot for the name `" + name + "` is not exist.");
			}
			
			return	ptr->index();
			
//			_assertNonEmptyState();
//			
//			for (UniformValueSlotV1 const& s : _uniformValueSlots)
//			{
//				if (s.name() == name)
//				{
//					return	s.index();
//				}
//			}
//
//			GLint	loc2	=	Stub::eeglGetUniformLocation(_name, toGLchar(name));
//			if (loc2 != -1)
//			{
//				for (UniformValueSlotV1 const& s: _uniformValueSlots)
//				{
//					if (s.location() == loc2)
//					{
//						return	s.index();
//					}
//				}
//			}
//			
//			Doctor::exceptWithReason("Uniform value slot for the name is not exist.");
		}
		
		
		
		
		auto Program::
		allVertexAttributeSlotV1s() const -> vec<VertexAttributeSlotV1> const&
		{
			_assertNonEmptyState();
			
			return	_vertexAttributeSlots;
		}
		
		auto Program::
		vertexAttributeSlotAtIndex(Size const index) -> VertexAttributeSlotV1&
		{
			_assertNonEmptyState();
			
			return	_vertexAttributeSlots.at(index);
		}
		auto Program::
		indexOfVertexAttributeSlotV1ForName(const std::string name) const -> Size
		{
			_assertNonEmptyState();
			
			for (VertexAttributeSlotV1 const& s : _vertexAttributeSlots)
			{
				if (s.name() == name)
				{
					return	s.index();
				}
			}
			Doctor::exceptWithReason(Doctor::stringWithCFormat("Vertex attribute slot for the name `%s` does not exist.", name.c_str()));
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
