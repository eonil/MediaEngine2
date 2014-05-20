//
//  Functions.cpp
//  Graphics
//
//  Created by Hoon H. on 2/26/14.
//
//

#include "Functions.h"

#include "VertexLayoutDescriptor.h"
#include "ProgramVertexChannelingDescriptor.h"
#include "UniformProgramParameter.h"
#include "../Machine.h"
#include "../../Stub/GL-Common.h"
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
//				static inline auto
//				M() -> Machine&
//				{
//					return	Machine::current();
//				}
//				
//				
//				
//				
//				
//				
//
//				
//				
//				
//				static inline auto
//				setAllVertexChannelings(void const* const vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling) -> void
//				{
//					for (Size i=0; i<layout.channelComponents().size(); i++)
//					{
//						auto const& ch	=	layout.channelComponents().at(i);
//						
//						Machinery::VertexAttributeChannel::Format	f{};
//						f.componentCount	=	Machinery::VertexAttributeChannel::ComponentSize(ch.count);
//						f.componentType		=	ch.type;
//						f.dataOffset		=	ch.offset;
//						f.normalization		=	GL_FALSE;
//						f.strideSizeInBytes	=	Stub::toGLsizei(layout.strideSize());
//						
//						auto	vchslot		=	channeling.channelSlotForComponentIndex(i);
//						M().vertexAttributeChannels().at(*vchslot)->linkWithClientMemory(vertexes, f);
//					}
//				}
//				static inline auto
//				setAllVertexChannelings(ArrayBuffer const& vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling) -> void
//				{
//					for (Size i=0; i<layout.channelComponents().size(); i++)
//					{
//						auto const& ch	=	layout.channelComponents().at(i);
//						
//						Machinery::VertexAttributeChannel::Format	f{};
//						f.componentCount	=	Machinery::VertexAttributeChannel::ComponentSize(ch.count);
//						f.componentType		=	ch.type;
//						f.dataOffset		=	ch.offset;
//						f.normalization		=	GL_FALSE;
//						f.strideSizeInBytes	=	Stub::toGLsizei(layout.strideSize());
//						
//						auto	vchslot		=	channeling.channelSlotForComponentIndex(i);
//						M().vertexAttributeChannels().at(*vchslot)->linkWithServerBuffer(vertexes, f);
//					}
//				}
//				static inline auto
//				unsetAllVertexChannelings(ProgramVertexChannelingDescriptor2 const& channeling) -> void
//				{
//					for (auto const& vchslot: channeling.allChannelSlots())
//					{
//						M().vertexAttributeChannels().at(*vchslot)->unlink();
//					}
//				}

			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			static inline auto
			clearColor(Vector4 const& color) -> void
			{
				Stub::eeglClearColor(color.x, color.y, color.z, color.w);
				Stub::eeglClear(GL_COLOR_BUFFER_BIT);
			}
			static inline auto
			clearDepth(Scalar const& depth) -> void
			{
				Stub::eeglClearDepthf(depth);
				Stub::eeglClear(GL_DEPTH_BUFFER_BIT);
			}
			static inline auto
			clearStencil(Size const& stencil) -> void
			{
				EONIL_DEBUG_ASSERT(stencil <= std::numeric_limits<GLint>::max());
				
				GLint	s	=	GLint(stencil);
				Stub::eeglClearStencil(s);
				Stub::eeglClear(GL_STENCIL_BUFFER_BIT);
			}
			auto
			clear(Vector4 const& color, Scalar const& depth, Size const& stencil) -> void
			{
				clearColor(color);
				clearDepth(depth);
				clearStencil(stencil);
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
//			
//			auto
//			draw(void const* const vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling, GenericMemoryRange<PlanarTexture const> const& textures, DrawingMode const& mode, Range const& range) -> void
//			{
//				setAllVertexChannelings(vertexes, layout, channeling);
//				{
//					for (Size i=0; i<textures.size(); i++)
//					{
//						M().textureUnitAtIndex(i).setTexture(textures.at(i));
//					}
//					{
//						M().drawArrays(mode, range.location(), range.length());
//					}
//					for (Size i=0; i<textures.size(); i++)
//					{
//						M().textureUnitAtIndex(i).unsetTexture();
//					}
//				}
//				unsetAllVertexChannelings(channeling);
//			}
//			
//			auto
//			draw(void const* const vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling, vec<PlanarTexture> const& textures, DrawingMode const& mode, Range const& range) -> void
//			{
//				draw(vertexes, layout, channeling, GenericMemoryRange<PlanarTexture const>{textures.data(), textures.size()}, mode, range);
//			}
//			
//			auto
//			draw(void const* const vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling, PlanarTexture const& texture, DrawingMode const& mode, Range const& range) -> void
//			{
//				draw(vertexes, layout, channeling, GenericMemoryRange<PlanarTexture const>{&texture, 1}, mode, range);
//			}
//			
//			auto
//			draw(void const* const vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling, DrawingMode const& mode, Range const& range) -> void
//			{
//				draw(vertexes, layout, channeling, GenericMemoryRange<PlanarTexture const>{}, mode, range);
//			}
//			
//			
//			
////			auto
////			draw(Program const& program, VertexLayoutDescriptor const& format, ArrayBuffer const& vertexes, ElementArrayBuffer const& indexes, PlanarTexture const& texture, DrawingMode const& mode, Range const& range) -> void
////			{
////				EONIL_DEBUG_ASSERT_WITH_MESSAGE(false, "Not yet implemented.");
////			}
//			
//			
//			
//			
//			
//			auto
//			draw(Server::ArrayBuffer const& vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling, GenericMemoryRange<PlanarTexture const> const& textures, DrawingMode const& mode, Range const& range) -> void
//			{
//				setAllVertexChannelings(vertexes, layout, channeling);
//				{
//					for (Size i=0; i<textures.size(); i++)
//					{
//						M().textureUnitAtIndex(i).setTexture(textures.at(i));
//					}
//					{
//						M().drawArrays(mode, range.location(), range.length());
//					}
//					for (Size i=0; i<textures.size(); i++)
//					{
//						M().textureUnitAtIndex(i).unsetTexture();
//					}
//				}
//				unsetAllVertexChannelings(channeling);
//			}
//			
//			auto
//			draw(Server::ArrayBuffer const& vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling, DrawingMode const& mode, Range const& range) -> void
//			{
//				draw(vertexes, layout, channeling, GenericMemoryRange<PlanarTexture const>{}, mode, range);
//			}
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
			
			
					
		
		
		
		
		
		
		
			
			
			
		
		
		}







	}

}}}}