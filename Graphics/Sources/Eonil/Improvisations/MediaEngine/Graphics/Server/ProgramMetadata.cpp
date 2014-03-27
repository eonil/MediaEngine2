//
//  ProgramMetadata.cpp
//  Graphics
//
//  Created by Hoon H. on 3/24/14.
//
//

#include "ProgramMetadata.h"

#include "../Stub/GL.h"
#include "../Debugging/Doctor.h"
#include "../Value/Conversion/GLNumbers.h"
#include "Program.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		using namespace Debugging;
		using namespace Stub;
		using namespace Value::Conversion;
		





		
		
		
		
		
		
		ProgramMetadata::ProgramMetadata(GLuint const programName) : _pname(programName)
		{
		}
		
		
		auto
		ProgramMetadata::ParameterSlotDescription::stringify() const -> str
		{
			return	Doctor::stringWithCFormat("<index = %u, name = %s, type = %u, size = %u>", index, name.c_str(), type, size);
		}


		
		
		
		
		
		
		auto
		ProgramMetadata::
		allProgramUniformValueSlotProxys() const -> vec<ParameterSlotDescription>
		{
			vec<ParameterSlotDescription>		ret		{};
			
			GLint const		unic	=	eeglGetProgrami(_pname, GL_ACTIVE_UNIFORMS);
			for (GLuint i=0; i<unic; i++)
			{
				Size const	maxlen	=	eeglGetProgrami(_pname, GL_ACTIVE_UNIFORM_MAX_LENGTH);
				Size const	bufsz	=	maxlen+1;
				char		buf[bufsz];
				
				GLsizei const	bufsz2	=	toGLsizei(bufsz);
				
				GLsizei		curlen	=	0;
				GLint		cursz	=	0;
				GLenum		curtype	=	0;
				eeglGetActiveUniform(_pname, i, bufsz2, &curlen, &cursz, &curtype, buf);
				
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
				
				ParameterSlotDescription	desc1{};
				desc1.index		=	i;
				desc1.name		=	str(buf);
				desc1.type		=	curtype;
				desc1.size		=	cursz;
				desc1.location	=	eeglGetUniformLocation(_pname, buf);
				ret.push_back(desc1);
			}
			return	ret;
		}
		auto
		ProgramMetadata::
		allProgramVertexAttributeSlotProxys() const -> vec<ParameterSlotDescription>
		{
			vec<ParameterSlotDescription>	ret	{};
			
			GLint const		attrc	=	eeglGetProgrami(_pname, GL_ACTIVE_ATTRIBUTES);
			for (GLuint i=0; i<attrc; i++)
			{
				Size const	maxlen	=	eeglGetProgrami(_pname, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH);
				Size const	bufsz	=	maxlen+1;
				char		buf[bufsz];
				
				GLsizei const	bufsz2	=	toGLsizei(bufsz);
				
				GLsizei		curlen	=	0;
				GLint		cursz	=	0;
				GLenum		curtype	=	0;
				eeglGetActiveAttrib(_pname, i, bufsz2, &curlen, &cursz, &curtype, buf);
				
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
				
				ParameterSlotDescription	desc1	{};
				desc1.index		=	i;
				desc1.name		=	str(buf);
				desc1.type		=	curtype;
				desc1.size		=	cursz;
				desc1.location	=	eeglGetAttribLocation(_pname, buf);
				
				ret.push_back(desc1);
			}
			return	ret;
		}



	}

}}}}