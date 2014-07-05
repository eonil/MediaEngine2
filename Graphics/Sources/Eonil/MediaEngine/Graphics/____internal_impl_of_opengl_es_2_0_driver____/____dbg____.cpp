//
//  ____dbg____.cpp
//  Graphics
//
//  Created by Hoon H. on 14/7/6.
//
//

#include "____dbg____.h"
#include "../Debugging/Doctor.h"
#include "../Platform/iOS.h"
#include "../Platform/OSX.h"
#include <sstream>
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN








auto
assertWithReason(const bool condition) -> void
{
	err9_converted_legacy_assertion(condition);
}

auto
assertWithReason(const bool condition, const std::string reason) -> void
{
	err9_converted_legacy_assertion(condition, reason);
}




auto
assertCurrentGLContextExistence() -> void
{
#if		EONIL_MEDIA_ENGINE_TARGET_IOS
	assertWithReason(Platforms::iOS::hasCurrentGLContext(), "There's no GL context currently bounds.");
#elif	EONIL_MEDIA_ENGINE_TARGET_OSX
	assertWithReason(Platforms::OSX::hasCurrentGLContext(), "There's no GL context currently bounds.");
#else
	static_assert(false, "Unknown, unsupported platform.");
#endif
}





auto
assertNoGLError() -> void
{
	assertNoGLErrorWithMessageDesignations(std::map<GLenum,std::string>());
}


auto
assertNoGLErrorWithMessageDesignations(const std::map<GLenum, std::string> messageMap) -> void
{
	/*
	 GL error can be stacked multiple times.
	 Pump them all out.
	 */
	
	sz				c	=	0;
	GLenum			err	=	GL_NO_ERROR;
	
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		if (messageMap.find(err) == messageMap.end())
		{
			//#define GL_INVALID_ENUM                   0x0500
			//#define GL_INVALID_VALUE                  0x0501
			//#define GL_INVALID_OPERATION              0x0502
			//#define GL_OUT_OF_MEMORY                  0x0505
			
			std::stringstream	ss;
			ss << "A GL error occured: 0x" << std::hex << err << " (message undesignated)";
			std::string const	msg	=	ss.str();
			log(msg);
			
			//						std::string const	s1	=	std::hex << err;
			//						std::string const	num	=	stringWithCFormat("0x%X", err);
			//						std::string const	msg	=	stringWithCFormat("A GL error occured: %s (message undesignated)", num.c_str());
			//						log(msg);
		}
		else
		{
			std::string const	msg	=	messageMap.at(err);
			log("A GL error occured: " + msg);
		}
		c++;
	}
	assertWithReason(c == 0, "GL error shouldn't be detected.");
}


			
auto
log(str const& message) -> void
{
	/*!
	 @todo
	 Seems needs more polish.
	 */
	std::cout << message << "\n";
}
			
auto
description_with_attributes(str const& description, vec<std::pair<str,str>> const& attributes) -> str
{
	std::stringstream	ss1{};

	ss1	<<	description;
	ss1	<<	": ";

	sz	c1	=	0;
	for (auto const& p1: attributes)
	{
	ss1	<<	p1.first;
	ss1	<<	" = ";
	ss1	<<	p1.second;

	c1++;
	if (c1 < attributes.size())
	{
	ss1	<<	", ";
	}
	}

	return	ss1.str();
}

auto
description_of_object(str const& type, vec<std::pair<str,str>> const& attributes) -> str
{
	return	"<" + description_with_attributes(type, attributes) + ">";
}










				
				
				

			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END

