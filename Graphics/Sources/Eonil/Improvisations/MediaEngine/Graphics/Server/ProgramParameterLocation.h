//
//  ProgramParameterLocation.h
//  Graphics
//
//  Created by Hoon H. on 3/24/14.
//
//

#ifndef __Graphics__ProgramParameterLocation__
#define __Graphics__ProgramParameterLocation__


#include "../Common.h"
#include "Machinery/VertexAttributeChannel.h"
#include "Machinery/TextureSampler.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
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
			friend class	UniformValueSlot;
			friend class	VertexAttributeChannel;
			
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
		 */
		class
		UniformValueSlot
		{
			ProgramParameterLocation	_param_loc	{};

		public:
			UniformValueSlot() = default;
			UniformValueSlot(ProgramParameterLocation const& location);
			
//			void	setValue(GLfloat const value);
//			void	setValue(GLint const value);
//			void	setValue(glm::ivec2 const value);
//			void	setValue(glm::vec2 const value);
//			void	setValue(glm::mat2 const value);
//			void	setValue(glm::ivec3 const value);
//			void	setValue(glm::vec3 const value);
//			void	setValue(glm::mat3 const value);
//			void	setValue(glm::ivec4 const value);
//			void	setValue(glm::vec4 const value);
//			void	setValue(glm::mat4 const value);
			
			auto	setValue(Scalar const& value) -> void;
			auto	setValue(Vector2 const& value) -> void;
			auto	setValue(Vector3 const& value) -> void;
			auto	setValue(Vector4 const& value) -> void;
			auto	setValue(Quaternion const& value) -> void;
			auto	setValue(Matrix4 const& value) -> void;
			auto	setValueArray(Scalar const* const values, Size const count) -> void;
			auto	setValueArray(Vector4 const* const values, Size const count) -> void;
			auto	setValueArray(Matrix4 const* const values, Size const count) -> void;
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
		
		
		
		
		
		
		
		
		class
		VertexAttributeSlot
		{
			ProgramParameterLocation	_param_loc	{};
			
		public:
			VertexAttributeSlot() = default;
			VertexAttributeSlot(ProgramParameterLocation const& location);
		};
		
	}

}}}}

#endif /* defined(__Graphics__ProgramParameterLocation__) */
