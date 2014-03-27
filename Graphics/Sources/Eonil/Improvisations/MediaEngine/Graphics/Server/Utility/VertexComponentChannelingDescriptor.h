//
//  VertexComponentChannelingDescriptor.h
//  Graphics
//
//  Created by Hoon H. on 3/27/14.
//
//

#ifndef __Graphics__VertexComponentChannelingDescriptor__
#define __Graphics__VertexComponentChannelingDescriptor__

#include "../../Common.h"
#include "ProgramVertexChannelingDescriptor.h"
#include "Program.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		namespace
		Utility
		{

			
			
			
			
			
			enum class
			VERTEX_STREAM_DATA_PLACEMENT
			{
				CLIENT_MEMORY,
				SERVER_BUFFER,
			};
			


			
			
			
			
			
			
			
			
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
			template <VERTEX_STREAM_DATA_PLACEMENT const P>
			class
			VertexComponentChannelingDescriptor
			{
				using	DATA_PTR		=	typename std::conditional<P == VERTEX_STREAM_DATA_PLACEMENT::CLIENT_MEMORY, GenericMemoryRange<void const>, ArrayBuffer const*>::type;
				using	PROGRAM_SLOT	=	local<ProgramVertexAttributeSlotProxy>;
				
				DATA_PTR					_component_stream	{};
				VertexLayoutDescriptor		_source_layout		{};
				vec<PROGRAM_SLOT>			_destination_slots	{};
					
				/*
				 A vertex component is bound to a destination slot at same index.
				 A generic-vertex-index must be resolved dynamically by querying it with destination slot object.
				 */
				
				////
				
				VertexComponentChannelingDescriptor(DATA_PTR componentStream, VertexLayoutDescriptor const& sourceComponentLayout, vec<PROGRAM_SLOT> const& destinationSlots);
				
			public:
				VertexComponentChannelingDescriptor() = default;
				VertexComponentChannelingDescriptor(VertexComponentChannelingDescriptor const&) = default;
				
				auto	componentStream() const -> DATA_PTR;
				auto	sourceComponentLayout() const -> VertexLayoutDescriptor const&;
				auto	destinationSlots() const -> vec<PROGRAM_SLOT> const&;
				
			public:
				static auto	analyze(DATA_PTR data, VertexLayoutDescriptor const& layout, Program& program) -> VertexComponentChannelingDescriptor;
			};
			
			
			
			
			
			
			
			
			
			
			
			template <VERTEX_STREAM_DATA_PLACEMENT const P>
			VertexComponentChannelingDescriptor<P>::VertexComponentChannelingDescriptor(DATA_PTR componentStream, VertexLayoutDescriptor const& sourceComponentLayout, vec<PROGRAM_SLOT> const& destinationSlots)
			:	_component_stream(componentStream)
			,	_source_layout(sourceComponentLayout)
			,	_destination_slots(destinationSlots)
			{
			}
			
			template <VERTEX_STREAM_DATA_PLACEMENT const P> auto
			VertexComponentChannelingDescriptor<P>::
			componentStream() const -> DATA_PTR
			{
				return	_component_stream;
			}
			template <VERTEX_STREAM_DATA_PLACEMENT const P> auto
			VertexComponentChannelingDescriptor<P>::
			sourceComponentLayout() const -> VertexLayoutDescriptor const&
			{
				return	_source_layout;
			}
			template <VERTEX_STREAM_DATA_PLACEMENT const P> auto
			VertexComponentChannelingDescriptor<P>::
			destinationSlots() const -> vec<PROGRAM_SLOT> const&
			{
				return	_destination_slots;
			}
			
			template <VERTEX_STREAM_DATA_PLACEMENT const P> auto
			VertexComponentChannelingDescriptor<P>::
			analyze(DATA_PTR data, VertexLayoutDescriptor const& layout, Program& program) -> VertexComponentChannelingDescriptor
			{
				vec<PROGRAM_SLOT>	ch_slots{};
				
				for (Size i=0; i<layout.channelComponents().size(); i++)
				{
					EONIL_DEBUG_ASSERT(not layout.channelComponents().at(i).name.empty());
					
					auto const&		comp	=	layout.channelComponents().at(i);
					PROGRAM_SLOT	ch_slot	=	program.vertexAttributeSlotForName(comp.name);
					ch_slots.push_back(ch_slot);
				}
				
				return	{data, layout, ch_slots};
			}
			
			
			
			
			
			
			
			
			
			
			
			

			using	VertexComponentChannelingDescriptorForStreamInClientMemory	=	VertexComponentChannelingDescriptor<VERTEX_STREAM_DATA_PLACEMENT::CLIENT_MEMORY>;		//	Actually we just need beginning pointer, but accepts ending pointer for validation in debug mode.
			using	VertexComponentChannelingDescriptorForStreamInServerBuffer	=	VertexComponentChannelingDescriptor<VERTEX_STREAM_DATA_PLACEMENT::SERVER_BUFFER>;
			

			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__VertexComponentChannelingDescriptor__) */
