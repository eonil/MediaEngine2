//
//  ProgramSlot.h
//  EonilGraphics
//
//  Created by Eonil on 5/1/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__ProgramSlot__
#define __EonilGraphics__ProgramSlot__

#include "../Common.h"
#include "Machinery/VertexAttributeChannel.h"
#include "Machinery/TextureSampler.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		using namespace	Machinery;
		
		
		
		/*!
		 @warning
		 An OpenGL uniform slot can be refered using multiple names.
		 That means you really can't rely on the *name* to identify a slot. It can be used
		 just a hint for it. So, do not keep the name as a part of a slot information. It's
		 just a query method.
		 
		 The `name` method will be kept for debugging metadta purpose, and will be removed
		 from the public access.
		 
		 @note
		 OpenGL uniform slots are just a big flat 4D float vector.
		 */
		
		class
		ProgramSlot : public NoCopyButMoveObject
		{
		public:
			auto	index() const -> GLuint const;
			auto	name() const -> std::string const&;			//!	@note	I am not sure that whether I have to remove this property or not...
			auto	type() const -> GLenum const;
			auto	size() const -> GLint const;
			auto	location() const -> GLint const;
			
		protected:
			ProgramSlot();
			
			GLuint					_pname;			//	Name of program which owns this slot.
			
			GLuint					_idx;
			std::string				_name;
			GLenum					_type;
			GLint					_sz;
			
			GLint					_loc;
			
			
		public:
			std::string const		description() const;
		};
		
		
		
		
		
		
		
		
		class
		UniformValueSlot final : public ProgramSlot
		{
			friend class	Program;
			
			UniformValueSlot(GLuint const programName, GLuint const slotIndex);
			
		public:
			
//			void					setValue(GLfloat const value);
//			void					setValue(GLint const value);
//			void					setValue(glm::ivec2 const value);
//			void					setValue(glm::vec2 const value);
//			void					setValue(glm::mat2 const value);
//			void					setValue(glm::ivec3 const value);
//			void					setValue(glm::vec3 const value);
//			void					setValue(glm::mat3 const value);
//			void					setValue(glm::ivec4 const value);
//			void					setValue(glm::vec4 const value);
//			void					setValue(glm::mat4 const value);
			
			void	setValue(Scalar const& value);
			void	setValue(Vector2 const& value);
			void	setValue(Vector3 const& value);
			void	setValue(Vector4 const& value);
			void	setValue(Quaternion const& value);
			void	setValue(Matrix4 const& value);
			void	setValueArray(Scalar const* const values, Size const count);
			void	setValueArray(Vector4 const* const values, Size const count);
			void	setValueArray(Matrix4 const* const values, Size const count);
			
			void	setSampler(TextureSampler const& sampler);
			
			void	unset();
			
		private:
			void	_validateProgramBinding() const;
			void	_set_as_having_no_value() const;
			void	_set_as_having_some_value() const;
			
			mutable
			struct
			{
				bool	_does_slot_have_value	=	false;					
			}
			_validity;
		};
		
		
		
		
		
		class
		VertexAttributeSlot final : public ProgramSlot
		{
			friend class	Program;
			
			VertexAttributeSlot(GLuint const programName, GLuint const slotIndex);
			
		public:
			
//				void					setVertexAttributeChannel(Machinery::VertexAttributeChannel const channel);
		};
	}
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics__ProgramSlot__) */
