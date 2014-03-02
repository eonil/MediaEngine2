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
#include "ProgramSlot.h"

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
		 
		 
		 
		 @discussion
		 The destructor is not virtual by default. Subclassing this class might be dangerous.
		 */
		class
		Program final : public TrackableObject
		{
			using						VAC						=	Machinery::VertexAttributeChannel;
			
			GLuint						_name						{NULL_GL_NAME()};
			
			vec<UniformValueSlot>		_uniformValueSlots			{};
			vec<VertexAttributeSlot>	_vertexAttributeSlots		{};
			
			map<str, VAC const*>		_vertexChannelsForAttributesMapping{};
			
			////
			
			auto	_assertNonEmptyState() const -> void;
			
			
			
			
			
		public:
			Program() = default;
			Program(VertexShader const& vertexShader, FragmentShader const& fragmentShader);
			Program(Program const&) = delete;
			~Program();
			
			auto	operator==(Program const& other) const -> bool;
			auto	operator!=(Program const& other) const -> bool;
			
			auto	empty() const -> bool;
			auto	name() const -> GLuint;
			
//			struct
//			{
//				std::vector<UniformValueSlot> const&	all() const;
//				UniformValueSlot const&					atIndex(Size const index) const;
//				UniformValueSlot&						atIndex(Size const index);
//				
//				Size const								indexForName(
//				UniformValueSlot const&					forName(std::string const name) const;
//				UniformValueSlot&						forName(std::string const name);
//			}
//			uniformValueSlot;
//
//			struct
//			{
//				std::vector<VertexAttributeSlot> const&		all() const;
//				VertexAttributeSlot const&					atIndex(Size const index) const;
//				VertexAttributeSlot&						atIndex(Size const index);
//			}
//			vertexAttributeSlot;
			
			auto	allUniformValueSlots() const									->	vec<UniformValueSlot> const&;
			auto	uniformValueSlotAtIndex(Size const index) const					->	UniformValueSlot const&;
			auto	uniformValueSlotAtIndex(Size const index)						->	UniformValueSlot&;
			auto	indexOfUniformValueSlotForName(std::string const name) const	->	Size;			//!	@note	If there's no slot for the name, An excepion will be thrown. Also this doesn't resolve struct field or array indexing expression. Only unifom names.
			
			auto	allVertexAttributeSlots() const									->	vec<VertexAttributeSlot> const&;
			auto	vertexAttributeSlotAtIndex(Size const index) const				->	VertexAttributeSlot const&;
			auto	vertexAttributeSlotAtIndex(Size const index)					->	VertexAttributeSlot&;
			auto	indexOfVertexAttributeSlotForName(std::string const name) const	->	Size;
			
			auto	vertexAttributeSlotForName(str const& name) const				->	VertexAttributeSlot const&;
			
			
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




