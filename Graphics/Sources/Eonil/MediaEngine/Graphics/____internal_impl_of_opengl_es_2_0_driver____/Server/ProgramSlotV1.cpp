//
//  ProgramSlotV1.cpp
//  EonilGraphics
//
//  Created by Eonil on 5/1/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "../Stub/GL.h"
#include "ProgramSlotV1.h"

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Server
{
	using namespace Stub;
	
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	ProgramSlotV1::ProgramSlotV1()
	{
	}
	
	GLuint const
	ProgramSlotV1::index() const
	{
		return	_idx;
	}
	std::string const&
	ProgramSlotV1::name() const
	{
		return	_name;
	}
	GLenum const
	ProgramSlotV1::type() const
	{
		return	_type;
	}
	GLint const
	ProgramSlotV1::size() const
	{
		return	_sz;
	}
	GLint const
	ProgramSlotV1::location() const
	{
		return	_loc;
	}
	
	std::string const
	ProgramSlotV1::description() const
	{
		return	"<ProgramSlotV1: program = " + std::to_string(_pname)
		+		", index = " + std::to_string(index())
		+		", name = " + name()
		+		", type = " + std::to_string(type())
		+		", size = " + std::to_string(size())
		+		", location = " + std::to_string(location())
		;
	}
	

	
	

	
	ProgramUniformValueSlotProxyV1::ProgramUniformValueSlotProxyV1(GLuint const programName, GLuint const slotIndex) 
	{
		sz const	maxlen	=	eeglGetProgrami(programName, GL_ACTIVE_UNIFORM_MAX_LENGTH);
		sz const	bufsz	=	maxlen+1;
		char		buf[bufsz];
		
		GLsizei const	bufsz2	=	toGLsizei(bufsz);
		
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
	ProgramUniformValueSlotProxyV1::setValue(const Scalar &value)
	{
		_validateProgramBinding();
		eeglUniform1f(location(), value);
		_set_as_having_some_value();
	}
	void
	ProgramUniformValueSlotProxyV1::setValue(const Vector2 &value)
	{
		_validateProgramBinding();
		eeglUniform2fv(location(), 1, value.components);
		_set_as_having_some_value();
	}
	void
	ProgramUniformValueSlotProxyV1::setValue(const Vector3 &value)
	{
		_validateProgramBinding();
		eeglUniform3fv(location(), 1, value.components);
		_set_as_having_some_value();
	}
	void
	ProgramUniformValueSlotProxyV1::setValue(const Vector4 &value)
	{
		_validateProgramBinding();
		eeglUniform4fv(location(), 1, value.components);
		_set_as_having_some_value();
	}
	void
	ProgramUniformValueSlotProxyV1::setValue(const Quaternion &value)
	{
		_validateProgramBinding();
		eeglUniform4fv(location(), 1, CONV4(value).glcomponents);
		_set_as_having_some_value();
	}
	void
	ProgramUniformValueSlotProxyV1::setValue(const Matrix4 &value)
	{
		_validateProgramBinding();
		eeglUniformMatrix4fv(location(), 1, GL_FALSE, CONV16(value).glcomponents);
		_set_as_having_some_value();
	}
	void
	ProgramUniformValueSlotProxyV1::setValueArray(const Scalar *const values, const sz count)
	{
		GLsizei	c	=	toGLsizei(count);
		_validateProgramBinding();
		eeglUniform1fv(location(), c, toGLfloat(values));
		_set_as_having_some_value();
	}
	void
	ProgramUniformValueSlotProxyV1::setValueArray(const Vector4 *const values, const sz count)
	{
		GLsizei	c	=	toGLsizei(count);
		_validateProgramBinding();
		eeglUniform4fv(location(), c, toGLfloat(values));
		_set_as_having_some_value();
	}
	void
	ProgramUniformValueSlotProxyV1::setValueArray(const Matrix4 *const values, const sz count)
	{
		GLsizei	c	=	toGLsizei(count);
		_validateProgramBinding();
		eeglUniformMatrix4fv(location(), c, GL_FALSE, toGLfloat(values));
		_set_as_having_some_value();
	}
	
	void
	ProgramUniformValueSlotProxyV1::setSampler(const Server::Machinery::TextureSampler &sampler)
	{
		//!	@todo	Needs uniform type check.
		
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(sampler.index() <= std::numeric_limits<GLint>::max());
		}
		
		GLint	idx	=	sampler.index();
		
		_validateProgramBinding();
		eeglUniform1i(location(), idx);
		_set_as_having_some_value();
	}
	
	void
	ProgramUniformValueSlotProxyV1::unset()
	{
		_set_as_having_no_value();
	}
	
	
	
	void
	ProgramUniformValueSlotProxyV1::_validateProgramBinding() const
	{
		EEGL_ASSERT_WITH_REASON(_pname == eeglGetInteger(GL_CURRENT_PROGRAM), "You must bind the owner program before setting any uniform parameter.");
	}
	void
	ProgramUniformValueSlotProxyV1::_set_as_having_no_value() const
	{
		EEGL_ASSERT(_validity._does_slot_have_value);
		_validity._does_slot_have_value	=	false;
	}
	void
	ProgramUniformValueSlotProxyV1::_set_as_having_some_value() const
	{
		EEGL_ASSERT(not _validity._does_slot_have_value);
		_validity._does_slot_have_value	=	true;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	ProgramVertexAttributeSlotProxyV1::ProgramVertexAttributeSlotProxyV1(GLuint const programName, GLuint const slotIndex)
	{
		sz const	maxlen	=	eeglGetProgrami(programName, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
		sz const	bufsz	=	maxlen+1;
		char		buf[bufsz];
		
		GLsizei const	bufsz2	=	toGLsizei(bufsz);
		
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
//			ProgramVertexAttributeSlotProxyV1::setVertexAttributeChannel(const Machinery::VertexAttributeChannel channel)
//			{
//				eeglBindAttribLocation(_pname, channel.index(), name().c_str());
//			}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}






INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END






