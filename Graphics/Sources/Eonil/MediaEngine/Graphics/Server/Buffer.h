//
//  Buffer.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#pragma once
#include "../Common.h"
#include "ServerObjectProxy.h"
namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Server
	{
		
		namespace
		Machinery
		{
			class
			IndexUnitChannel;
		}
		
		/*!
		 Buffer intentionally subclassed to distinguish two type of buffers
		 which only suit to for thier own type of slots.
		 */
		class
		Buffer : public ServerObjectProxy
		{
		};
		
		
		
		
		
		
		
		
		
		
		/*!
		 @note
		 This class stores `Memory` as debugging info.
		 
		 @discussion
		 The destructor is not virtual by default. Subclassing this class might be dangerous.
		 */
		class
		ArrayBuffer final : public Buffer
		{
			GLuint	_name	=	NULL_GL_NAME();
			
//			EONIL_MEDIA_ENGINE_DEBUG_ONLY_INLINE_FIELD(Legacy2013SharedMemory, _dbg_source_content);
			
		public:
			ArrayBuffer() = default;
//			EONIL_MEDIA_ENGINE_DEPRECATE() ArrayBuffer(_Legacy2013::SharedMemory const data);							//	Creates initialized fixed sized buffer.
			ArrayBuffer(GenericMemoryRange<void const> data);
			ArrayBuffer(ArrayBuffer const&) = delete;
			ArrayBuffer(ArrayBuffer&&);
			~ArrayBuffer();
			
			auto	operator==(ArrayBuffer const& other) const -> bool;
			auto	operator!=(ArrayBuffer const& other) const -> bool;
			
		public:
			auto	empty() const -> bool;
			auto	name() const -> GLuint;
			
//			auto	description() const -> str;
		};
		
		
		
		
		
		
		
		
		
		
		/*!
		 @discussion
		 The destructor is not virtual by default. Subclassing this class might be dangerous.
		 */
		class
		ElementArrayBuffer final : public Buffer
		{
			friend class	Machinery::IndexUnitChannel;
			
			GLuint	_name	=	NULL_GL_NAME();
			size_t	_hotfix_length_of_data{0};

//			EONIL_MEDIA_ENGINE_DEPRECATE()
//			EONIL_MEDIA_ENGINE_DEBUG_ONLY_INLINE_FIELD(_Legacy2013::SharedMemory, _dbg_source_content);

		public:
			ElementArrayBuffer() = default;
//			[[deprecated]] ElementArrayBuffer(_Legacy2013::SharedMemory const data);
			ElementArrayBuffer(GenericMemoryRange<uint16_t const> data);
			ElementArrayBuffer(ElementArrayBuffer const&) = delete;
			~ElementArrayBuffer();
			
			auto	operator==(ElementArrayBuffer const& other) const -> bool;
			auto	operator!=(ElementArrayBuffer const& other) const -> bool;
			
			auto	empty() const -> bool;
			auto	name() const -> GLuint;
		};
	}
	
	
	
	
	
	
	
	
	
	
	
}}}}

