//
//  GeometryRendering.cpp
//  Graphics
//
//  Created by Hoon H. on 3/27/14.
//
//

#include "GeometryRendering.h"

#include "VertexLayoutDescriptor.h"
#include "ProgramVertexChannelingDescriptor.h"
#include "UniformProgramParameter.h"
#include "../Machine.h"
#include "../../Stub/GL-Common.h"
#include "../../Stub/GL-Get.h"
#include "../../Stub/GL-Context.h"
#include "../../Server/Machinery/VertexAttributeChannel.h"
#include "../../Server/ProgramParameterLocation.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		
		
	
		
		
		namespace
		Utility
		{
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			namespace
			{
				static inline auto
				M() -> Machine&
				{
					return	Machine::current();
				}
				
				
				
				
				
				static inline auto
				linkup(local<VertexAttributeChannel> vert_chan_ptr, GenericMemoryRange<void const> data_ptr, Machinery::VertexAttributeChannel::Format const& f) -> void
				{
					vert_chan_ptr->linkWithClientMemory(data_ptr.begin(), f);
				}
				
				static inline auto
				linkup(local<VertexAttributeChannel> vert_chan_ptr, ArrayBuffer const* data_ptr, Machinery::VertexAttributeChannel::Format const& f) -> void
				{
					vert_chan_ptr->linkWithServerBuffer(*data_ptr, f);
				}
				
				template <VERTEX_PROVISIONING_LOCATION const P>
				static inline auto
				setAllChannelings(GenericMemoryRange<VertexComponentProvisioning<P> const> providers) -> void
				{
					for (auto const& provider: providers)
					{
						auto const&		channeling	=	provider.channeling();
						
						auto const&	src_layout	=	channeling.sourceComponentLayout();
						EONIL_DEBUG_ASSERT(src_layout.channelComponents().size() == channeling.destinationSlots().size());
						
						Size	num_comps	=	src_layout.channelComponents().size();
						for (Size i=0; i<num_comps; i++)
						{
							auto const&		src_vcomp_obj	=	src_layout.channelComponents().at(i);
							auto const&		dest_slot_ptr	=	channeling.destinationSlots().at(i);
							
							Machinery::VertexAttributeChannel::Format	f{};
							f.componentCount	=	Machinery::VertexAttributeChannel::ComponentSize(src_vcomp_obj.count);
							f.componentType		=	src_vcomp_obj.type;
							f.dataOffset		=	src_vcomp_obj.offset;
							f.normalization		=	GL_FALSE;
							f.strideSizeInBytes	=	Stub::toGLsizei(src_layout.strideSize());
							
							auto const&		data_ptr		=	provider.components();
							auto			vert_chan_ptr	=	M().vertexAttributeChannels().at(*dest_slot_ptr);
							
							linkup(vert_chan_ptr, data_ptr, f);
						}
					}
				}
				
				template <VERTEX_PROVISIONING_LOCATION const P>
				static inline auto
				unsetAllChannelings(GenericMemoryRange<VertexComponentProvisioning<P> const> providers) -> void
				{
					for (auto const& provider: providers)
					{
						Size	num_comps	=	provider.channeling().destinationSlots().size();
						for (Size i=0; i<num_comps; i++)
						{
							auto const&		dest_slot_ptr	=	provider.channeling().destinationSlots().at(i);
							auto			vert_chan_ptr	=	M().vertexAttributeChannels().at(*dest_slot_ptr);
							
							vert_chan_ptr->unlink();
						}
					}
				}
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			namespace
			{
				static inline auto
				_has_duplicated_generic_vidx(GeometryProvisioning const& vertexes) -> bool
				{
					std::multiset<GLuint>	_refcounts{};
					
					for (auto const& a: vertexes.server)
					{
						for (auto const& b: a.channeling().destinationSlots())
						{
							GLuint	generic_vertex_idx	=	M().vertexAttributeChannels().at(*b)->index();
							_refcounts.insert(generic_vertex_idx);
						}
					}
					
					for (auto const& a: vertexes.client)
					{
						for (auto const& b: a.channeling().destinationSlots())
						{
							GLuint	generic_vertex_idx	=	M().vertexAttributeChannels().at(*b)->index();
							_refcounts.insert(generic_vertex_idx);
						}
					}
					
					for (auto const& c: _refcounts)
					{
						if (_refcounts.count(c) > 1)
						{
							return	true;
						}
					}
					return	false;
				}
				
				
				
				static inline auto
				_generic_draw(GeometryProvisioning const& vertexes, TextureChannelingRangePointer const& textures, DrawingMode const& mode, IndexingRange const& selection) -> void
				{
					EONIL_DEBUG_ASSERT(not _has_duplicated_generic_vidx(vertexes));
					
					setAllChannelings(vertexes.server);
					setAllChannelings(vertexes.client);
					{
						for (Size i=0; i<textures.size(); i++)
						{
							M().textureUnitAtIndex(i).setTexture(textures.at(i));
						}
						{
							M().drawArrays(mode, selection.begin(), selection.size());
						}
						for (Size i=0; i<textures.size(); i++)
						{
							M().textureUnitAtIndex(i).unsetTexture();
						}
					}
					unsetAllChannelings(vertexes.client);
					unsetAllChannelings(vertexes.server);
				}
			}
			
			
			
			
			
			
			
			
			auto
			draw(GeometryProvisioning const& vertexes, TextureChannelingRangePointer const& textures, DrawingMode const& mode, IndexingRange const& selection) -> void
			{
				EONIL_DEBUG_ASSERT(not vertexes.empty());
				EONIL_DEBUG_ASSERT(not textures.empty());
				EONIL_DEBUG_ASSERT(not selection.empty());
				_generic_draw(vertexes, textures, mode, selection);
			}
			auto
			draw(GeometryProvisioning const& vertexes, DrawingMode const& mode, IndexingRange const& selection) -> void
			{
				EONIL_DEBUG_ASSERT(not vertexes.empty());
				EONIL_DEBUG_ASSERT(not selection.empty());
				_generic_draw(vertexes, {}, mode, selection);
			}
			
			
			
			
			
			
			
			
			
			
					
		
		
		
		
		
		
		
			
			
			
		
		
		}







	}

}}}}