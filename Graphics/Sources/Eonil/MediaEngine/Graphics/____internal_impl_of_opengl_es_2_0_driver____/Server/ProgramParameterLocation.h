//
//  ProgramParameterLocation.h
//  Graphics
//
//  Created by Hoon H. on 3/24/14.
//
//

#pragma once
#include "Declarations.h"
#include "Machinery/VertexAttributeChannel.h"
#include "Machinery/TextureSampler.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN
namespace
Server
{
	using namespace	Machinery;
	
	
	
	/*!
	 Represents a pointer to a parameter slot(uniform or vertex channel) of a program.

	 @discussion
	 When I query a program parameter, OpenGL will provide the leaf nodes which are fully
	 divided. That means keeping those information will take huge memory, and even further,
	 the informations are not useful on runtime. 
	 
	 @classdesign
	 Previous version implementation kept all those information, and wasted huge memory if
	 a program us emplying many uniforms. This version class is redesigned as a simple
	 pointer to the target uniform slot, and does not waste extra memory.
	 
	 @note
	 OpenGL uniform slots are just a big flat 4D float vector.
	 */
	
	class
	ProgramParameterLocation
	{
		friend class	ProgramUniformValueSlotProxy;
		friend class	VertexAttributeChannel;
		friend class	VertexAttributeChannelList;
		
		GLuint	_pname		{NULL_GL_NAME()};
		GLint	_loc		{};						//!	0 is allowed and a valid state.
		
		auto	_is_valid() const -> bool;
		auto	location() const -> GLint;
		
	public:
		ProgramParameterLocation();
		ProgramParameterLocation(GLuint programName, GLint locationNumber);
		
	};
	
	
	
	
	
	
	
	/*!
	 @discussion
	 This class keeps just pointer to the slot.
	 If you need full slot metadata, then you can use `ProgramMetadata` class.
	 Semantically this is a pointer to another object.
	 */
	class
	ProgramUniformValueSlotProxy
	{
		ProgramParameterLocation	_param_loc	{};

	public:
		ProgramUniformValueSlotProxy() = default;
		ProgramUniformValueSlotProxy(ProgramParameterLocation const& location);
		
		auto	setValue(Scalar const& value) -> void;
		auto	setValue(Vector2 const& value) -> void;
		auto	setValue(Vector3 const& value) -> void;
		auto	setValue(Vector4 const& value) -> void;
		auto	setValue(Quaternion const& value) -> void;
		auto	setValue(Matrix4 const& value) -> void;
		auto	setValueArray(Scalar const* const values, sz const count) -> void;
		auto	setValueArray(Vector4 const* const values, sz const count) -> void;
		auto	setValueArray(Matrix4 const* const values, sz const count) -> void;
		auto	setSampler(TextureSampler const& sampler) -> void;
		
		auto	unset() -> void;
		
	private:
		auto	_validateProgramBinding() const -> void;
		auto	_set_as_having_no_value() const -> void;
		auto	_set_as_having_some_value() const -> void;
		
		mutable
		struct
		{
			bool	_does_slot_have_value	=	false;
		}
		_validity;
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*!
	 A program's vertex-attribute-slot parameters.
	 Don't be confused with `VertexAttributeChannel` object.
	 Semantically this is a pointer to another object.
	 
	 @discussion
	 Semantically, we just channel a vertex data into this slot.
	 But the GL is adapting some complex indirection mechacnism 
	 for flexibility - *generic veretx index* -, and we cannot
	 channel a vertex data into program slot directly. 
	 
	 It's possible to add some *convenient* method to abstract
	 them out, but we do not provide those methods because this
	 is the lowest C++ layer to GL API, and this must reflect 
	 GL's API structure. Adding those method also means 
	 abstracting out some semantics, and that may introduce 
	 some serious semantic issues.
	 */
	class
	ProgramVertexAttributeSlotProxy final
	{
		friend class				VertexAttributeChannelList;
		
		ProgramParameterLocation	_param_loc	{};
		
	public:
		ProgramVertexAttributeSlotProxy() = default;
		ProgramVertexAttributeSlotProxy(ProgramParameterLocation const& location);
	};
	
}
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END
