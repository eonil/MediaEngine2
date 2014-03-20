//
//  ProgramSlot.cpp
//  EonilGraphics
//
//  Created by Eonil on 5/1/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "../Stub/GL.h"
#include "../Debugging/Doctor.h"
#include "ProgramSlot.h"
#include "../Value/Conversion/GLNumbers.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Server
	{
		using namespace Debugging;
		using namespace Stub;
		using namespace Value::Conversion;
		
		namespace
		{
			union
			CONV4
			{
				GLfloat		glcomponents[4];
				Vector4		eonilv4;
				Quaternion	eonilq;
				
				CONV4(Vector4 const eonil) : eonilv4(eonil) {};
				CONV4(Quaternion const eonil) : eonilq(eonil) {};
			};
			union
			CONV16
			{
				GLfloat		glcomponents[16];
				Matrix4		eonil;
				
				CONV16(Matrix4 const eonil) : eonil(eonil) {};
			};
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		ProgramSlot::ProgramSlot()
		{
		}
		
		GLuint const
		ProgramSlot::index() const
		{
			return	_idx;
		}
		std::string const&
		ProgramSlot::name() const
		{
			return	_name;
		}
		GLenum const
		ProgramSlot::type() const
		{
			return	_type;
		}
		GLint const
		ProgramSlot::size() const
		{
			return	_sz;
		}
		GLint const
		ProgramSlot::location() const
		{
			return	_loc;
		}
		
		std::string const
		ProgramSlot::description() const
		{
			return	Doctor::stringWithCFormat("<ProgramSlot: program = %u, index = %u, name = %s, type = %u, size = %u, location = %u>", _pname, index(), name().c_str(), type(), size(), location());
		}
		
	
		
		

		
		UniformValueSlot::UniformValueSlot(GLuint const programName, GLuint const slotIndex) 
		{
			Size const	maxlen	=	eeglGetProgrami(programName, GL_ACTIVE_UNIFORM_MAX_LENGTH);
			Size const	bufsz	=	maxlen+1;
			char		buf[bufsz];
			
			GLsizei const	bufsz2	=	GLsizeiFromSize(bufsz);
			
			GLsizei		curlen	=	0;
			GLint		cursz	=	0;
			GLenum		curtype	=	0;
			eeglGetActiveUniform(programName, slotIndex, bufsz2, &curlen, &cursz, &curtype, buf);
			
			EEGL_ASSERT(curlen > 0);
			EEGL_ASSERT(cursz > 0);
			EEGL_ASSERT(curtype > 0);
			EEGL_ASSERT(curlen <= maxlen);
			EEGL_ASSERT(buf[curlen] == '\0');
			
			//				GL_FLOAT,
			//				GL_FLOAT_VEC2,
			//				GL_FLOAT_VEC3,
			//				GL_FLOAT_VEC4,
			//				GL_INT,
			//				GL_INT_VEC2,
			//				GL_INT_VEC3,
			//				GL_INT_VEC4,
			//				GL_BOOL,
			//				GL_BOOL_VEC2,
			//				GL_BOOL_VEC3,
			//				GL_BOOL_VEC4,
			//				GL_FLOAT_MAT2,
			//				GL_FLOAT_MAT3,
			//				GL_FLOAT_MAT4,
			//				GL_SAMPLER_2D,
			//				GL_SAMPLER_CUBE,
			
			buf[curlen]	=	'\0';	//	For safety.
			
			////
			
			_pname		=	programName;
			_idx		=	slotIndex;
			_name		=	std::string(buf);
			_type		=	curtype;
			_sz			=	cursz;
			_loc		=	eeglGetUniformLocation(programName, buf);
		}
		
		void
		UniformValueSlot::setValue(const Scalar &value)
		{
			_validateProgramBinding();
			eeglUniform1f(location(), value);
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValue(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector2 &value)
		{
			_validateProgramBinding();
			eeglUniform2fv(location(), 1, value.components);
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValue(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector3 &value)
		{
			_validateProgramBinding();
			eeglUniform3fv(location(), 1, value.components);
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValue(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector4 &value)
		{
			_validateProgramBinding();
			eeglUniform4fv(location(), 1, value.components);
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValue(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Quaternion &value)
		{
			_validateProgramBinding();
			eeglUniform4fv(location(), 1, CONV4(value).glcomponents);
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValue(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Matrix4 &value)
		{
			_validateProgramBinding();
			eeglUniformMatrix4fv(location(), 1, GL_FALSE, CONV16(value).glcomponents);
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValueArray(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Scalar *const values, const Size count)
		{
			GLsizei	c	=	GLsizeiFromSize(count);
			_validateProgramBinding();
			eeglUniform1fv(location(), c, toGLfloat(values));
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValueArray(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector4 *const values, const Size count)
		{
			GLsizei	c	=	GLsizeiFromSize(count);
			_validateProgramBinding();
			eeglUniform4fv(location(), c, toGLfloat(values));
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValueArray(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Matrix4 *const values, const Size count)
		{
			GLsizei	c	=	GLsizeiFromSize(count);
			_validateProgramBinding();
			eeglUniformMatrix4fv(location(), c, GL_FALSE, toGLfloat(values));
			_set_as_having_some_value();
		}
		
		void
		UniformValueSlot::setSampler(const Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::TextureSampler &sampler)
		{
			//!	@todo	Needs uniform type check.
			
			GLint	idx	=	Value::Conversion::GLintFromSize(sampler.index());
			
			_validateProgramBinding();
			eeglUniform1i(location(), idx);
			_set_as_having_some_value();
		}
		
		void
		UniformValueSlot::unset()
		{
			_set_as_having_no_value();
		}
		
		
		
		void
		UniformValueSlot::_validateProgramBinding() const
		{
			EEGL_ASSERT_WITH_REASON(_pname == eeglGetInteger(GL_CURRENT_PROGRAM), "You must bind the owner program before setting any uniform parameter.");
		}
		void
		UniformValueSlot::_set_as_having_no_value() const
		{
			EEGL_ASSERT(_validity._does_slot_have_value);
			_validity._does_slot_have_value	=	false;
		}
		void
		UniformValueSlot::_set_as_having_some_value() const
		{
			EEGL_ASSERT(not _validity._does_slot_have_value);
			_validity._does_slot_have_value	=	true;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		VertexAttributeSlot::VertexAttributeSlot(GLuint const programName, GLuint const slotIndex)
		{
			Size const	maxlen	=	eeglGetProgrami(programName, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
			Size const	bufsz	=	maxlen+1;
			char		buf[bufsz];
			
			GLsizei const	bufsz2	=	GLsizeiFromSize(bufsz);
			
			GLsizei		curlen	=	0;
			GLint		cursz	=	0;
			GLenum		curtype	=	0;
			eeglGetActiveAttrib(programName, slotIndex, bufsz2, &curlen, &cursz, &curtype, buf);
			
			EEGL_ASSERT(curlen > 0);
			EEGL_ASSERT(cursz > 0);
			EEGL_ASSERT(curtype > 0);
			EEGL_ASSERT(curlen <= maxlen);
			EEGL_ASSERT(buf[curlen] == '\0');
			
			//				GL_FLOAT,
			//				GL_FLOAT_VEC2,
			//				GL_FLOAT_VEC3,
			//				GL_FLOAT_VEC4,
			//				GL_FLOAT_MAT2,
			//				GL_FLOAT_MAT3,
			//				GL_FLOAT_MAT4
			
			buf[curlen]	=	'\0';	//	For safety.
			
			////
			
			_pname		=	programName;
			_idx		=	slotIndex;
			_name		=	std::string(buf);
			_type		=	curtype;
			_sz			=	cursz;
			_loc		=	eeglGetAttribLocation(programName, buf);
		}
		
//			void
//			VertexAttributeSlot::setVertexAttributeChannel(const Machinery::VertexAttributeChannel channel)
//			{
//				eeglBindAttribLocation(_pname, channel.index(), name().c_str());
//			}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
	
	
	
	
	
	
}}}}





