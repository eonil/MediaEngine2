//
//  Buffer.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "GL-Buffer.h"
#include "Buffer.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Server
{
	using namespace	Stub;
	
	static	std::vector<void*>	cptr;
	
	
	
	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	ArrayBuffer::ArrayBuffer(GenericMemoryRange<void const> data)
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			ObjectInstanceAddressTracker<ArrayBuffer>::registerObjectAddress(this);
			assertCurrentGLContextExistence();
		}
		
		////
		
		GenericMemoryRange<uint8_t const>	bin	=	data.reinterpretAs<uint8_t const>();
		
		_name		=	eeglGenBuffer();
		
		////
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(_name != 0);
			assertCurrentGLContextExistence();
			err9_converted_legacy_assertion(not data.empty());
		}
		////
		
		GLsizeiptr const	size	=	bin.size();
		GLvoid* const		mem		=	(GLvoid*)bin.begin();
		
		eeglBindBuffer(GL_ARRAY_BUFFER, name());
		eeglBufferData(GL_ARRAY_BUFFER, size, mem, GL_STATIC_DRAW);
		eeglUnbindBufer(GL_ARRAY_BUFFER);
	}
//		ArrayBuffer::ArrayBuffer(_Legacy2013::SharedMemory const data)
//		{
//			Debug::ObjectInstanceAddressTracker<ArrayBuffer>::registerObjectAddress(this);
//			
//			EEGL_RUN_AS_ASSERTION(Doctor::assertCurrentGLContextExistence());
//			
//			_name		=	eeglGenBuffer();
//			
//			EEGL_ASSERT(_name != 0);
//			
//			////
//			
//			EEGL_RUN_AS_ASSERTION(Doctor::assertCurrentGLContextExistence());
//			EEGL_ASSERT(data != nullptr);
//			
////			EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(_dbg_source_content = data);
//			
//			GLsizeiptr const	size	=	data.length();
//			GLvoid* const		mem		=	(GLvoid*)data.address();
//			
//			eeglBindBuffer(GL_ARRAY_BUFFER, name());
//			eeglBufferData(GL_ARRAY_BUFFER, size, mem, GL_STATIC_DRAW);
//			eeglUnbindBufer(GL_ARRAY_BUFFER);
//			
//		}
	ArrayBuffer::ArrayBuffer(ArrayBuffer&& o) : _name(std::move(o._name))
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			o._name = NULL_GL_NAME();
		}
	}
	ArrayBuffer::~ArrayBuffer()
	{
		if (_name != NULL_GL_NAME())
		{
			if (USE_DEBUGGING_ASSERTIONS)
			{
				assertCurrentGLContextExistence();
				err9_converted_legacy_assertion(_name != 0);
			}
			
			eeglDeleteBuffer(_name);
			
			if (USE_DEBUGGING_ASSERTIONS)
			{
				_name = 0;
			}
		}
		
		if (USE_DEBUGGING_ASSERTIONS)
		{
			ObjectInstanceAddressTracker<ArrayBuffer>::unregisterObjectAddress(this);
		}
	}

	////
	
	
	
	auto ArrayBuffer::
	operator==(ArrayBuffer const& other) const -> bool
	{
		EEGL_ASSERT(&other != nullptr);
		return	_name == other._name;
	}
	auto ArrayBuffer::
	operator!=(ArrayBuffer const& other) const -> bool
	{
		EEGL_ASSERT(&other != nullptr);
		return	_name != other._name;
	}		
	
	auto ArrayBuffer::
	empty() const -> bool
	{
		return	_name == NULL_GL_NAME();
	}
	auto ArrayBuffer::
	name() const -> GLuint
	{
		EEGL_ASSERT(this != nullptr);
		return	_name;
	}
//		auto ArrayBuffer::
//		description() const -> str
//		{
////			GLuint const		curname	=	eeglGetInteger(GL_ARRAY_BUFFER_BINDING);
////			eeglUnbindBufer(GL_ARRAY_BUFFER_BINDING);
////			eeglBindBuffer(GL_ARRAY_BUFFER_BINDING, owner.name());
//
//			str const	desc	=	Doctor::stringWithCFormat("<ArrayBuffer: 0x%llx, name = %llu, length = %llu>", (uint64_t)(uintptr_t)this, uint64_t(name()), uint64_t(_cptr->_dbg_source_content.length()));
//
////			eeglUnbindBufer(GL_ARRAY_BUFFER_BINDING);
////			eeglBindBuffer(GL_ARRAY_BUFFER_BINDING, curname);
//			return	desc;
//		}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
//		ElementArrayBuffer::ElementArrayBuffer(_Legacy2013::SharedMemory const data)
//		{
//			Debug::ObjectInstanceAddressTracker<ElementArrayBuffer>::registerObjectAddress(this);
//			
//			EEGL_RUN_AS_ASSERTION(Doctor::assertCurrentGLContextExistence());
//			_name		=	eeglGenBuffer();
//
//			////
//			
//			EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN(_dbg_source_content = data);
//			
//			if (data.length() > 0)
//			{
//				GLsizeiptr const	size	=	data.length();
//				GLvoid* const		mem		=	(GLvoid*)data.address();
//				
//				eeglBindBuffer(GL_ARRAY_BUFFER, name());
//				eeglBufferData(GL_ARRAY_BUFFER, size, mem, GL_STATIC_DRAW);
//				eeglUnbindBufer(GL_ARRAY_BUFFER);
//			}
//			
//			_hotfix_length_of_data	=	data.length();
//		}
	ElementArrayBuffer::ElementArrayBuffer(GenericMemoryRange<uint16_t const> data)
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(not data.empty());
			ObjectInstanceAddressTracker<ElementArrayBuffer>::registerObjectAddress(this);
			assertCurrentGLContextExistence();
		}

		////
		
		_name		=	eeglGenBuffer();
		
		////
		
		auto	bytes	=	data.reinterpretAs<uint8_t const>();
		
		GLsizeiptr const		size	=	bytes.size();
		GLvoid const* const		mem		=	(GLvoid const*)bytes.begin();
		
		eeglBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _name);
		eeglBufferData(GL_ELEMENT_ARRAY_BUFFER, size, mem, GL_STATIC_DRAW);
		eeglUnbindBufer(GL_ELEMENT_ARRAY_BUFFER);
		
		_hotfix_length_of_data	=	bytes.size();
	}
	ElementArrayBuffer::~ElementArrayBuffer()
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			assertCurrentGLContextExistence();
		}
		
		////
		
		eeglDeleteBuffer(_name);
		
		////
		
		if (USE_DEBUGGING_ASSERTIONS)
		{
			ObjectInstanceAddressTracker<ElementArrayBuffer>::unregisterObjectAddress(this);
		}
	}
	
	
	
	
	
	auto ElementArrayBuffer::
	operator==(ElementArrayBuffer const& other) const -> bool
	{
		return	_name == other._name;
	}
	auto ElementArrayBuffer::
	operator!=(ElementArrayBuffer const& other) const -> bool
	{
		return	_name != other._name;
	}
	
	
	
	auto ElementArrayBuffer::
	empty() const -> bool
	{
		return	_name == NULL_GL_NAME();
	}
	
	auto ElementArrayBuffer::
	name() const -> GLuint
	{
		return	_name;
	}
	
//			std::string const
//			ElementArrayBuffer::Heart::Examination::description() const
//			{
//				ArrayBuffer const&	owner	=	*Doctor::Examination<ArrayBuffer, Examination>::resolveObjectForExamination(this);
//				
////				GLuint const		curname	=	eeglGetInteger(GL_ARRAY_BUFFER_BINDING);
////				eeglUnbindBufer(GL_ARRAY_BUFFER_BINDING);
////				eeglBindBuffer(GL_ARRAY_BUFFER_BINDING, owner.name());
//				
//				std::string const	desc	=	Doctor::stringWithCFormat("<ArrayBuffer: 0x%llx, name = %llu, length = %llu>", (uint64_t)(uintptr_t)this, uint64_t(owner.name()), uint64_t(source.length()));
//				
////				eeglUnbindBufer(GL_ARRAY_BUFFER_BINDING);
////				eeglBindBuffer(GL_ARRAY_BUFFER_BINDING, curname);
//				return	desc;
//			}


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END




