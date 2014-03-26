////
////  Agent.cpp
////  Graphics
////
////  Created by Hoon H. on 2/19/14.
////
////
//
//#include "Agent.h"
//#include "../Machine.h"
//#include "../../Stub/GL-Common.h"
//#include "../../Stub/GL-Context.h"
//
//#include "UniformProgramParameter.h"
//
//namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
//	
//	namespace
//	Server
//	{
//		namespace
//		Agency
//		{
//			
//			namespace
//			{
//				static inline auto
//				M() -> Machine&
//				{
//					return	Machine::current();
//				}
//				
//				static inline auto
//				setAllVertexChannelings(void const* const vertexes, VertexLayoutDescriptor const& format) -> Size		//	Returns number of all channels.
//				{
//					Size	chidx	=	0;
//					for (auto const& ch: format.channelComponents())
//					{
//						Machinery::VertexAttributeChannel::Format	f{};
//						f.componentCount	=	Machinery::VertexAttributeChannel::ComponentSize(ch.count);
//						f.componentType		=	ch.type;
//						f.dataOffset		=	ch.offset;
//						f.normalization		=	GL_FALSE;
//						f.strideSizeInBytes	=	Stub::toGLsizei(format.strideSize());
//						
//						M().vertexAttributeChannelAtIndex(chidx).linkWithClientMemory(vertexes, f);
//						chidx++;
//					}
//					return	chidx;
//				}
//				static inline auto
//				unsetAllVertexChannelings(Size const& count) -> void
//				{
//					for (Size i=0; i<count; i++)
//					{
//						M().vertexAttributeChannelAtIndex(i).unlink();
//					}
//				}
//				
//				
//				
////				static inline auto
////				setProgramUniformParameters(Program& program, vec<UniformProgramParameter> const& parameters) -> void
////				{
////					for (auto const& pp: parameters)
////					{
////						switch (pp.type())
////						{
////							case
////							UniformProgramParameter::TYPE::NONE:
////							{
////								panic("Bad enum value.");
////							}
////							case
////							UniformProgramParameter::TYPE::SCALAR:
////							{
////								program.uniformValueSlotAtIndex(pp.index()).setValue(*pp.scalar());
////								break;
////							}
////							case
////							UniformProgramParameter::TYPE::VECTOR4:
////							{
////								program.uniformValueSlotAtIndex(pp.index()).setValue(*pp.vector4());
////								break;
////							}
////							case
////							UniformProgramParameter::TYPE::MATRIX4:
////							{
////								program.uniformValueSlotAtIndex(pp.index()).setValue(*pp.matrix4());
////								break;
////							}
////							case
////							UniformProgramParameter::TYPE::SAMPLER:
////							{
////								program.uniformValueSlotAtIndex(pp.index()).setSampler(*pp.sampler());
////								break;
////							}
////						}
////					}
////				}
////				static inline auto
////				unsetProgramUniformParameters(Program& program, vec<UniformProgramParameter> const& parameters) -> void
////				{
////					for (auto const& pp: parameters)
////					{
////						program.uniformValueSlotAtIndex(pp.index()).unset();
////					}
////				}
//				
//				
//				
//				
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
//			
//			
//			
//			
//			static inline auto
//			clearColor(Vector4 const& color) -> void
//			{
//				Stub::eeglClearColor(color.x, color.y, color.z, color.w);
//				Stub::eeglClear(GL_COLOR_BUFFER_BIT);
//			}
//			static inline auto
//			clearDepth(Scalar const& depth) -> void
//			{
//				Stub::eeglClearDepthf(depth);
//				Stub::eeglClear(GL_DEPTH_BUFFER_BIT);
//			}
//			static inline auto
//			clearStencil(Size const& stencil) -> void
//			{
//				GLint	s	=	Stub::toGLint(stencil);
//				Stub::eeglClearStencil(s);
//				Stub::eeglClear(GL_STENCIL_BUFFER_BIT);
//			}
//			auto
//			clear(Vector4 const& color, Scalar const& depth, Size const& stencil) -> void
//			{
//				clearColor(color);
//				clearDepth(depth);
//				clearStencil(stencil);
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
//			
//			
//			
//			
//			
//			
//			auto
//			draw(Rendering::D2014R2::DisplayScreenFrame const& frame, Program& program, VertexLayoutDescriptor const& format, void const* const vertexes, PlanarTexture const& texture, DrawingMode const& mode, Range const& range) -> void
//			{
//				Size	num_ch	=
//				setAllVertexChannelings(vertexes, format);
//				{
//					M().useProgram(program);
//					setProgramUniformParameters(program, parameters);
//					{
//						M().textureUnitAtIndex(0).setTexture(texture);
//						{
//							M().drawArrays(mode, range.location(), range.length());
//						}
//						M().textureUnitAtIndex(0).unsetTexture();
//					}
//					unsetProgramUniformParameters(program, parameters);
//					M().unuseProgram();
//				}
//				unsetAllVertexChannelings(num_ch);
//			}
//			
//			auto
//			draw(Rendering::D2014R2::DisplayScreenFrame const& frame, Program& program, VertexLayoutDescriptor const& format, void const* const vertexes, DrawingMode const& mode, Range const& range) -> void
//			{
//				Size	num_ch	=
//				setAllVertexChannelings(vertexes, format);
//				{
//					M().useProgram(program);
//					setProgramUniformParameters(program, parameters);
//					{
//						M().drawArrays(mode, range.location(), range.length());
//					}
//					unsetProgramUniformParameters(program, parameters);
//					M().unuseProgram();
//				}
//				unsetAllVertexChannelings(num_ch);
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
//			
//			
//			
//			
//			
//			
//			
////			
////			
////			
////			auto
////			draw(Rendering::D2014R2::DisplayScreenFrame const& frame, Program& program, vec<UniformProgramParameter> const& parameters, VertexLayoutDescriptor const& format, void const* const vertexes, PlanarTexture const& texture, DrawingMode const& mode, Range const& range) -> void
////			{
////				Size	num_ch	=
////				setAllVertexChannelings(vertexes, format);
////				{
////					M().useProgram(program);
////					setProgramUniformParameters(program, parameters);
////					{
////						M().textureUnitAtIndex(0).setTexture(texture);
////						{
////							M().drawArrays(mode, range.location(), range.length());
////						}
////						M().textureUnitAtIndex(0).unsetTexture();
////					}
////					unsetProgramUniformParameters(program, parameters);
////					M().unuseProgram();
////				}
////				unsetAllVertexChannelings(num_ch);
////			}
////			
////			auto
////			draw(Rendering::D2014R2::DisplayScreenFrame const& frame, Program& program, vec<UniformProgramParameter> const& parameters, VertexLayoutDescriptor const& format, void const* const vertexes, DrawingMode const& mode, Range const& range) -> void
////			{
////				Size	num_ch	=
////				setAllVertexChannelings(vertexes, format);
////				{
////					M().useProgram(program);
////					setProgramUniformParameters(program, parameters);
////					{
////						M().drawArrays(mode, range.location(), range.length());
////					}
////					unsetProgramUniformParameters(program, parameters);
////					M().unuseProgram();
////				}
////				unsetAllVertexChannelings(num_ch);
////			}
////			
////			
////
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
//			
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
