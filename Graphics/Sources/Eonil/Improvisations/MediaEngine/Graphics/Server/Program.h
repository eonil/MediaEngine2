//
//  Program.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__Program__
#define __EonilGraphics__Program__

#include "../Common.h"
#include "Declarations.h"
#include "ServerObjectProxy.h"
#include "ProgramSlotV1.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{		
		/*!
		 
		 @classdesign	Uniform search by name is discouraged to reduce lookup cost from client code. Client must 
						cache the index and should use the index. Index for the name won't be changed while program 
						alive.
		 
						This class does not support free-binding of vertex attribute location. All the version 
						attribute locations must be pre-bound before creating program object, and once created 
						binding cannot be changed later. In other words, vertex attribute location binding is 
						immutable. This has advatages when you are using VAO (which fixes vertex locations).
		 
						

		 @discussion	Parameter-less constructor creates an empty object which is invalid for any operation. Use 
						it only for nil-state marker.
		 
						A program object accepts a vertex and a fragment shaders, and copies thier contents into
						program object when linking them. You can freely delete the shaders after creating a program.
		 
		 @ref			http://www.khronos.org/opengles/sdk/docs/man/xhtml/glLinkProgram.xml
		 
						>	The program object's information log is updated and the program is generated at the time
						>	of the link operation. After the link operation, applications are free to modify attached
						>	shader objects, compile attached shader objects, detach shader objects, delete shader 
						>	objects, and attach additional shader objects. None of these operations affects the 
						>	information log or the program that is part of the program object.
		 
		 
		 
		 @note			You must bind program to a `Machine` to set parameters. Debug build asserts for invalid
						program binding.
		 
		 
		 
		 @note			OpenGL ES 2.0 API provides a way to query location of a uniform substructure like struct field
						or array element. This functionality is not supported in this library to simplify design and 
						implementation.
		 
						@ref	http://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetUniformLocation.xml
		 
						Support for that needs complex something which describes stuct field and array indexing.
						The feature may be supported in future, but not expected anytime soon without very strong
						request.
		 
		 
		 
		 @note
		 Subclassing is prohibited. So destructor is not virtual.
		 
		 @warning
		 Do not refer any object returned from this object. Always copy them.
		 If you're using deprecated methods, copy the index numbers instead of.
		 */
		class
		Program final : public TrackableObject
		{
			using						VAC						=	Machinery::VertexAttributeChannel;
			
			GLuint						_name						{NULL_GL_NAME()};
			
			vec<ProgramUniformValueSlotProxyV1>		_uniformValueSlots			{};			//	This is immutable/readonly. Will not be modified after once retrieved. @deprecated
			vec<ProgramVertexAttributeSlotProxyV1>	_vertexAttributeSlots		{};			//	This is immutable/readonly. Will not be modified after once retrieved. @deprecated
			
			map<str, VAC const*>		_vertexChannelsForAttributesMapping{};
			
			////
			
			auto	_assertNonEmptyState() const -> void;
			
			auto	_search_uniform_location(str const& name) const -> GLint;
			auto	_search_vertex_attribute_location(const str &name) const -> GLint;
			
			[[deprecated]]	auto	searchProgramUniformValueSlotProxyV1ForName(const str &name) const -> ProgramUniformValueSlotProxyV1 const*;
			[[deprecated]]	auto	searchProgramUniformValueSlotProxyV1ForName(const str &name) -> ProgramUniformValueSlotProxyV1*;
			
			
		public:
			Program() = default;
			Program(VertexShader const& vertexShader, FragmentShader const& fragmentShader);
			Program(Program const&) = delete;
			Program(Program&&) = default;
			~Program();
			
			auto	operator==(Program const& other) const -> bool;
			auto	operator!=(Program const& other) const -> bool;
			
			auto	empty() const -> bool;
			auto	name() const -> GLuint;
			
//			struct
//			{
//				std::vector<ProgramUniformValueSlotProxyV1> const&	all() const;
//				ProgramUniformValueSlotProxyV1 const&					atIndex(Size const index) const;
//				ProgramUniformValueSlotProxyV1&						atIndex(Size const index);
//				
//				Size const								indexForName(
//				ProgramUniformValueSlotProxyV1 const&					forName(std::string const name) const;
//				ProgramUniformValueSlotProxyV1&						forName(std::string const name);
//			}
//			uniformValueSlot;
//
//			struct
//			{
//				std::vector<ProgramVertexAttributeSlotProxyV1> const&		all() const;
//				ProgramVertexAttributeSlotProxyV1 const&					atIndex(Size const index) const;
//				ProgramVertexAttributeSlotProxyV1&						atIndex(Size const index);
//			}
//			vertexAttributeSlot;
			
			auto	uniformValueSlotForName(str const& name) const -> local<ProgramUniformValueSlotProxy const>;			//!	Panics if there's no slot for the name.
			auto	uniformValueSlotForName(str const& name) -> local<ProgramUniformValueSlotProxy>;						//!	Panics if there's no slot for the name.
			auto	vertexAttributeSlotForName(str const& name) const -> local<ProgramVertexAttributeSlotProxy const>;		//!	Panics if there's no slot for the name.
			auto	vertexAttributeSlotForName(str const& name) -> local<ProgramVertexAttributeSlotProxy>;					//!	Panics if there's no slot for the name.
			
			[[deprecated]]	auto	allProgramUniformValueSlotProxyV1s() const									->	vec<ProgramUniformValueSlotProxyV1> const&;
			[[deprecated]]	auto	uniformValueSlotAtIndex(Size const index) const					->	ProgramUniformValueSlotProxyV1 const&;
			[[deprecated]]	auto	uniformValueSlotAtIndex(Size const index)						->	ProgramUniformValueSlotProxyV1&;
			[[deprecated]]	auto	indexOfProgramUniformValueSlotProxyV1ForName(std::string const name) const	->	Size;								//!	@note	If there's no slot for the name, An excepion will be thrown. Take care that you need to supply fully qualified name for a slot. See the OpenGL ES 2.0 manual for details. The only exception is sole array name.
			
			[[deprecated]]	auto	allProgramVertexAttributeSlotProxyV1s() const									->	vec<ProgramVertexAttributeSlotProxyV1> const&;
			[[deprecated]]	auto	vertexAttributeSlotAtIndex(Size const index) const				->	ProgramVertexAttributeSlotProxyV1 const&;
			[[deprecated]]	auto	vertexAttributeSlotAtIndex(Size const index)					->	ProgramVertexAttributeSlotProxyV1&;
			[[deprecated]]	auto	indexOfProgramVertexAttributeSlotProxyV1ForName(std::string const name) const	->	Size;
			
//			auto	vertexAttributeSlotForName(str const& name) const				->	ProgramVertexAttributeSlotProxyV1 const&;
			
			
//		public:
//			std::string const							description() const;
			
			
			
			
		public:
			struct
			Utility
			{
				static auto	shaderCodeForLegacyPlatformsWhichDoNotSupportPrecision(str const& code) -> str;
			};
		};
	}
	
	

	
	
}}}}

#endif /* defined(__EonilGraphics__Program__) */




