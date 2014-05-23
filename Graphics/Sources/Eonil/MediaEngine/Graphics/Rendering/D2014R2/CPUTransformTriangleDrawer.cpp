//
//  CPUTransformTriangleDrawer.cpp
//  Graphics
//
//  Created by Hoon H. on 14/5/23.
//
//

#include "CPUTransformTriangleDrawer.h"
#include "../../Server/Symbols.h"
#include "../../Server/Texture.h"
#include "../../Server/Shader.h"
#include "../../Server/Program.h"
#include "../../Server/Machine.h"
#include "../../Server/Machinery/VertexAttributeChannel.h"
#include "../../Server/Utility/VertexLayoutDescriptor.h"
#include "../../Server/Utility/UniformProgramParameter.h"
#include "../../Server/Utility/GeometryRendering.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN
using namespace	Server;
using namespace	Server::Utility;









namespace
{
	
	static constexpr char const
	VERTEX_SHADER_CODE[]	=
#if				EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
#include		"Common.vertex.shader.glsl-dt-1_10"
#elif			EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
#include		"Common.vertex.shader.glsl-es-1_00"
#else
#error			EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
#endif
#include		"CPUTransformTriangleDrawer.vertex.shader.rstr"
	;
	
	static constexpr char const
	FRAGMENT_SHADER_CODE[]	=
#if				EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
#include		"Common.fragment.shader.glsl-dt-1_10"
#include		"CPUTransformTriangleDrawer.fragment.shader.rstr"
#elif			EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
#include		"Common.fragment.shader.glsl-es-1_00"
#include		"CPUTransformTriangleDrawer.fragment.shader.rstr"
#else
#error			EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
#endif
	;
	
	
	
	
	
	
	static inline auto
	machine() -> Machine&
	{
		return	Machine::current();
	}
	
	enum
	VERTEX_CHANNEL_INDEXES : Size
	{
		POSITION_COORDINATE		=	0,
//		COLOR_COORDINATE		=	1,
//		COMPOSITION_COLOR		=	2,
	};
	
	static inline auto
	make_vertex_format() -> VertexLayoutDescriptor
	{
		VertexLayoutDescriptor	f{};
		f.appendScalarVectorChannel("locationCoordinateV", 3);
		
		return	f;
	}
}























struct
CPUTransformTriangleDrawer::Core
{
	Program								program				=	{{VERTEX_SHADER_CODE}, {FRAGMENT_SHADER_CODE}};
	VertexComponentChannelingDescriptor	channeling			=	{VertexComponentChannelingDescriptor::analyze(make_vertex_format(), program)};
	
	local<ProgramUniformValueSlotProxy>	colorUniformSlot	=	{program.uniformValueSlotForName("compositionColorF")};
};












CPUTransformTriangleDrawer::CPUTransformTriangleDrawer() : _core_ptr(new Core())
{
}
CPUTransformTriangleDrawer::~CPUTransformTriangleDrawer()
{
}




//auto CPUTransformTriangleDrawer::
//drawTriangleList(const Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::CPUTransformTriangleDrawer::CounterClockwiseWindingPointList &triangles, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector4 &color) const -> void
//{
//	EONIL_DEBUG_ASSERT_WITH_MESSAGE(triangles.points.size() > 0, "Empty list is not supported.");
//	EONIL_DEBUG_ASSERT_WITH_MESSAGE(triangles.points.size() % 3 == 0, "The list must contain at exactly 3N points.");
//	
//	////
//	
//	machine().useProgram(_core_ptr->program);
//	{
//		GenericMemoryRange<void const>	mem1	{triangles.points.data(), triangles.points.data() + triangles.points.size()};
//		ClientMemoryVertexProvisioning	verts1	{mem1, _core_ptr->channeling};
//		GeometryProvisioning			gp1	{&verts1};
//		
//		draw(gp1, DrawingMode::TRIANGLE_LIST, {0, triangles.points.size()/3});
//	}
//	machine().unuseProgram();
//}

auto
CPUTransformTriangleDrawer::
drawTriangleList(const GenericMemoryRange<const Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::CPUTransformTriangleDrawer::Triangle> &triangles, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector4 &color) const -> void
{
	if (triangles.size() == 0)
	{
		return;
	}
	
	////
	
	machine().useProgram(_core_ptr->program);
	{
		GenericMemoryRange<void const>	mem1	=	triangles.reinterpretAs<void const>();
		ClientMemoryVertexProvisioning	verts1	=	{mem1, _core_ptr->channeling};
		GeometryProvisioning			gp1		=	{&verts1};
		Size							num_v	=	triangles.size() * 3;
		
		_core_ptr->colorUniformSlot->setValue(color);
		{
			draw(gp1, DrawingMode::TRIANGLE_LIST, {0, num_v});
		}
		_core_ptr->colorUniformSlot->unset();
	}
	machine().unuseProgram();
}

auto
CPUTransformTriangleDrawer::
drawTriangleList(const GenericMemoryRange<const Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2::CPUTransformTriangleDrawer::Triangle> &triangles) const -> void
{
	drawTriangleList(triangles, {1,1,1,1});
}

























	


EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END