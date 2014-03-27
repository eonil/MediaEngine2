////
////  ProgramVertexChannelingDescriptor.h
////  Graphics
////
////  Created by Hoon H. on 2/26/14.
////
////
//
//#ifndef __Graphics__ProgramVertexChannelingDescriptor__
//#define __Graphics__ProgramVertexChannelingDescriptor__
//
//#include "../../Common.h"
//#include "VertexLayoutDescriptor.h"
//
//#include "../ProgramParameterLocation.h"		//	I don't know why the compiler wants definition of `ProgramVertexAttributeSlotProxy`...
//
//namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
//	
//	namespace
//	Server
//	{
//		namespace
//		Utility
//		{
////			/*!
////			 Maps component -> channel by thier indexes.
////			 */
////			class
////			ProgramVertexChannelingDescriptor
////			{
////				vec<Size>		_chidxs	{};
////				
////				[[deprecated]]
////				ProgramVertexChannelingDescriptor(vec<Size> const& allChannelIndexes);
////				
////			public:
////				[[deprecated]]
////				ProgramVertexChannelingDescriptor();
////				
////				[[deprecated]]
////				auto	channelIndexForComponentIndex(Size const& componentIndex) const -> Size;
////				auto	allChannelIndexes() const -> vec<Size> const&;
////				
////			public:
////				[[deprecated]]
////				static auto	analyze(VertexLayoutDescriptor const& layout, Program const& program) -> ProgramVertexChannelingDescriptor;
////			};
//			
//
//			
//			
//			
//			
//			/*!
//			 Defines how each vertex component to be mapped to
//			 a attribute slot of a program.
//			 
//			 @classdesign
//			 This sees vertex data as a stream of components. Graphics
//			 server may accept multiple streams, and we need information
//			 of how those components are laid out on the streams.
//			 
//			 This object describes layout of components
//			 
//			 `Server::Utility` provides convenient, simple, functional-
//			 style drawing method by abstracting out some details.
//			 
//			 
//			 Maps component -> vertex channel slot.
//			 
//			 Stores pointers to program's uniform slots in order of
//			 they defined by vertex layout. Consequently, this maps
//			 each vertex component to corresponding uniform slot.
//			 
//			 That means this presumes all the vertex components to 
//			 be interleaved in a single buffer. If you want to use
//			 multiple vertex stream, then you have to use multiple
//			 `ProgramVertexChannelingDescriptor` objects to describe
//			 each streams.
//			 
//			 @todo
//			 Remove `2` when stabilized.
//			 */
//			class
//			EONIL_DEPRECATED_CLASS
//			ProgramVertexChannelingDescriptor2
//			{
//				using	SLOT	=	local<ProgramVertexAttributeSlotProxy>;
//				
//				vec<SLOT>		_ch_slots;
//				
//				ProgramVertexChannelingDescriptor2(vec<SLOT> const& allChannelSlots);
//				
//			public:
//				ProgramVertexChannelingDescriptor2();
//				
//				auto	channelSlotForComponentIndex(Size const& componentIndex) const -> SLOT;
//				auto	allChannelSlots() const -> vec<SLOT> const&;
//				
//			public:
//				static auto	analyze(VertexLayoutDescriptor const& layout, Program& program) -> ProgramVertexChannelingDescriptor2;
//			};
//			
//
//			
//			
//			
//			
//			
//			
//		}
//	}
//	
//}}}}
//
//#endif /* defined(__Graphics__ProgramVertexChannelingDescriptor__) */
