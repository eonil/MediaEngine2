////
////  HierarchicalAgents.h
////  Graphics
////
////  Created by Hoon H. on 2/19/14.
////
////
//
//#ifndef __Graphics__HierarchicalAgents__
//#define __Graphics__HierarchicalAgents__
//
//#include "VertexDescriptor.h"
//
//namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
//	
//	namespace
//	Server
//	{
//		namespace
//		Agency
//		{
//			using	ConfigureProgram	=	std::function<void(Program& program)>;
//
//
//			class	DrawingAgent;
//			class	TexturingAgent;
//			class	GeometryAgent;
//			class	ProgrammingAgent;
//			class	MachineAgent;
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
//			class
//			TexturingAgent
//			{
//				GeometryAgent*		_geometry_agent		{};
//				ptr<PlanarTexture>	_texture			{};
//
//				TexturingAgent(GeometryAgent* const g, ptr<PlanarTexture> const texture);
//
//			public:
//				~TexturingAgent();
//
//			public:
//				/*!
//				 @param	range	Specifies index/count of vertexes to draw.
//				 This range must be correctly match for each drawing mode.
//				 For example, you must specify 3n number for TRIANGLES drawing mode.
//				 And 3 + n for TRIANGLE_STRIP drawing mode.
//				 */
//				auto	draw(ConfigureProgram const& configurator, DrawingMode const& mode, Range const& range) -> void;
//			};
//
//
//
//
//
//
//
//			/*!
//			 Draws with geometry data placed in client-side memory.
//			 This is good for data which is constantly mutated by CPU, so needs to be transferred to graphics server for each time.
//			 */
//			class
//			GeometryAgent
//			{
//				ProgrammingAgent*	_programming_agent	{};
//				VertexDescriptor	_format				{};
//				void const*			_vertexes			{};
//
//				GeometryAgent(ProgrammingAgent* const p, VertexDescriptor const& format, void const* vertexes);
//
//			public:
//				~GeometryAgent();
//
//			public:
//				auto	texturing(PlanarTexture const& texture) const -> TexturingAgent const&;
//			};
//
//
//
//
//
//
//
//			class
//			ProgrammingAgent
//			{
//				MachineAgent*	_machine_agent	{};
//				ptr<Program>	_program		{};
//
//				ProgrammingAgent(MachineAgent* const m, ptr<Program> const program);
//
//			public:
//				~ProgrammingAgent();
//
//			public:
//				auto	gemortry(VertexDescriptor const& format, void const* vertexes) const -> GeometryAgent const&;
//			};
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
//			/*!
//			 Simplified, even more abstracted, data-driven server handling, but yet quiet efficient.
//			 */
//			class
//			MachineAgent
//			{
//			public:
//				MachineAgent();
//				~MachineAgent();
//
//
//
//			public:
//				auto	programming(Program const& program) const -> ProgrammingAgent const&;
//
//
//
//
//			};
//
//			
//			
//
//		}
//	}
//	
//}}}}
//
//#endif /* defined(__Graphics__HierarchicalAgents__) */
