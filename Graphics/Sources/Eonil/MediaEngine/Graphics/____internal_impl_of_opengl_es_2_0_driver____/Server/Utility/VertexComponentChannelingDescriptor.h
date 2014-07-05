//
//  VertexComponentChannelingDescriptor.h
//  Graphics
//
//  Created by Hoon H. on 3/27/14.
//
//

#pragma once
#include "../Declarations.h"
#include "../Program.h"
#include "../ProgramParameterLocation.h"
#include "VertexLayoutDescriptor.h"
#include "ProgramVertexChannelingDescriptor.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

namespace
Server
{
	namespace
	Utility
	{
		
		
		
		
		
		
		
		/*!
		 Describes a single stream of multiple vertex components.
		 
		 @classdesign
		 This presumes a stream of multiple vertexes which contain
		 interleaved components. The vertexes may be placed in server
		 buffer or client memory.
		 
		 If you have multiple streams of vertexes, then you have to 
		 use multiple descriptors.
		 
		 If you really want non-interleaved data layout, you can do
		 that by putting only one component in a stream.
		 */
		class
		VertexComponentChannelingDescriptor
		{
			using	PROGRAM_SLOT	=	local<ProgramVertexAttributeSlotProxy>;
			
			VertexLayoutDescriptor		_source_layout		{};
			vec<PROGRAM_SLOT>			_destination_slots	{};
				
			/*
			 A vertex component is bound to a destination slot at same index.
			 A generic-vertex-index must be resolved dynamically by querying it with destination slot object.
			 */
			
			////
			
			VertexComponentChannelingDescriptor(VertexLayoutDescriptor const& sourceComponentLayout, vec<PROGRAM_SLOT> const& destinationSlots);
			
		public:
			VertexComponentChannelingDescriptor() = default;
			VertexComponentChannelingDescriptor(VertexComponentChannelingDescriptor const&) = default;
			
			
			auto	sourceComponentLayout() const -> VertexLayoutDescriptor const&;
			auto	destinationSlots() const -> vec<PROGRAM_SLOT> const&;
			
		public:
			static auto	analyze(VertexLayoutDescriptor const& layout, Program& program) -> VertexComponentChannelingDescriptor;
		};
		
		
		
		
		
		
		
		
		
		
					
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		enum class
		VERTEX_PROVISIONING_LOCATION
		{
			CLIENT_MEMORY,
			SERVER_BUFFER,
		};
		
		
		/*!
		 A definition of streaming vertex component with metadata.
		 */
		template <VERTEX_PROVISIONING_LOCATION const P>
		struct
		VertexComponentProvisioning
		{
			using	DATA_PTR		=	typename std::conditional<P == VERTEX_PROVISIONING_LOCATION::CLIENT_MEMORY, GenericMemoryRange<void const>, ArrayBuffer const*>::type;

			DATA_PTR								_components;
			VertexComponentChannelingDescriptor		_channeling;
			
		public:
			VertexComponentProvisioning(DATA_PTR components, VertexComponentChannelingDescriptor const& channeling);
			
			auto	components() const -> DATA_PTR;
			auto	channeling() const -> VertexComponentChannelingDescriptor const&;
		};
		
		
		
		template <VERTEX_PROVISIONING_LOCATION const P>
		VertexComponentProvisioning<P>::
		VertexComponentProvisioning(DATA_PTR components, VertexComponentChannelingDescriptor const& channeling) : _components(components), _channeling(channeling)
		{
		}
		template <VERTEX_PROVISIONING_LOCATION const P> auto
		VertexComponentProvisioning<P>::components() const -> DATA_PTR
		{
			return	_components;
		}
		template <VERTEX_PROVISIONING_LOCATION const P> auto
		VertexComponentProvisioning<P>::channeling() const -> VertexComponentChannelingDescriptor const&
		{
			return	_channeling;
		}
		
		
		
		
		
		
		

		using	ServerBufferVertexProvisioning		=	VertexComponentProvisioning<VERTEX_PROVISIONING_LOCATION::SERVER_BUFFER>;
		using	ClientMemoryVertexProvisioning		=	VertexComponentProvisioning<VERTEX_PROVISIONING_LOCATION::CLIENT_MEMORY>;
		
		
		
	}
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END

