//
//  ProgramParameterLocation.cpp
//  Graphics
//
//  Created by Hoon H. on 3/24/14.
//
//

#include "ProgramParameterLocation.h"

#include "../Stub/GL.h"
#include "../Debugging/Doctor.h"
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
		
		
		
		
		
		
		auto
		ProgramParameterLocation::
		_is_valid() const -> bool
		{
			return	_pname != NULL_GL_NAME();
		}
		
		
		ProgramParameterLocation::
		ProgramParameterLocation(GLuint programName, GLint locationNumber) : _pname(programName), _loc(locationNumber)
		{
		}
		auto
		ProgramParameterLocation::
		location() const -> GLint
		{
			return	_loc;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		UniformValueSlot::
		UniformValueSlot(ProgramParameterLocation const& location) : _param_loc(location)
		{
		}
		
		void
		UniformValueSlot::setValue(const Scalar &value)
		{
			_validateProgramBinding();
			eeglUniform1f(_param_loc.location(), value);
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValue(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector2 &value)
		{
			_validateProgramBinding();
			eeglUniform2fv(_param_loc.location(), 1, value.components);
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValue(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector3 &value)
		{
			_validateProgramBinding();
			eeglUniform3fv(_param_loc.location(), 1, value.components);
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValue(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector4 &value)
		{
			_validateProgramBinding();
			eeglUniform4fv(_param_loc.location(), 1, value.components);
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValue(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Quaternion &value)
		{
			_validateProgramBinding();
			eeglUniform4fv(_param_loc.location(), 1, CONV4(value).glcomponents);
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValue(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Matrix4 &value)
		{
			_validateProgramBinding();
			eeglUniformMatrix4fv(_param_loc.location(), 1, GL_FALSE, CONV16(value).glcomponents);
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValueArray(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Scalar *const values, const Size count)
		{
			GLsizei	c	=	toGLsizei(count);
			_validateProgramBinding();
			eeglUniform1fv(_param_loc.location(), c, toGLfloat(values));
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValueArray(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector4 *const values, const Size count)
		{
			GLsizei	c	=	toGLsizei(count);
			_validateProgramBinding();
			eeglUniform4fv(_param_loc.location(), c, toGLfloat(values));
			_set_as_having_some_value();
		}
		void
		UniformValueSlot::setValueArray(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Matrix4 *const values, const Size count)
		{
			GLsizei	c	=	toGLsizei(count);
			_validateProgramBinding();
			eeglUniformMatrix4fv(_param_loc.location(), c, GL_FALSE, toGLfloat(values));
			_set_as_having_some_value();
		}
		
		void
		UniformValueSlot::setSampler(const Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::TextureSampler &sampler)
		{
			//!	@todo	Needs uniform type check.
			
			GLenum	sidx	=	sampler.index();
			GLint	idx		=	sidx;
			
			_validateProgramBinding();
			eeglUniform1i(_param_loc.location(), idx);
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
			EEGL_ASSERT_WITH_REASON(_param_loc._pname == eeglGetInteger(GL_CURRENT_PROGRAM), "You must bind the owner program before setting any uniform parameter.");
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
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		VertexAttributeSlot::
		VertexAttributeSlot(ProgramParameterLocation const& location) : _param_loc(location)
		{
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
	
	
	
	
	
	
}}}}


