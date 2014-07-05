//
//  CPUTransformDebuggingLineDrawer.cpp
//  Graphics
//
//  Created by Hoon H. on 2/22/14.
//
//

#include "CPUTransformDebuggingLineDrawer.h"
#include "RenderingD2014R2____internal____.h"

/*!

OpenGL 2.0 does not support geometry instancing.

*/

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

namespace
Rendering
{
	namespace
	D2014R2
	{
		using namespace	Server;
		using namespace	Server::Utility;
		
		namespace
		{
			
			static constexpr char const
			VERTEX_SHADER_CODE[]	=
#if				EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
#include		"CPUTransformDebuggingLineDrawer.vertex.shader.glsl-dt-1_10"
#elif			EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
#include		"CPUTransformDebuggingLineDrawer.vertex.shader.glsl-es-1_00"
#else
#error			EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
#endif
			
			;
			
			static constexpr char const
			FRAGMENT_SHADER_CODE[]	=
#if				EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
#include		"CPUTransformDebuggingLineDrawer.fragment.shader.glsl-dt-1_10"
#elif			EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
#include		"CPUTransformDebuggingLineDrawer.fragment.shader.glsl-es-1_00"
#else			
#error			EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
#endif
			;
			
			
			
			static inline auto
			M() -> Machine&
			{
				return	Machine::current();
			}
			
			enum
			VERTEX_CHANNEL_INDEXES : sz
			{
				LOCATION_COORDINATE		=	0,
				COMPOSITION_COLOR		=	1,
			};
			
			static inline auto
			make_vertex_format() -> VertexLayoutDescriptor
			{
				VertexLayoutDescriptor	f{};
				f.appendScalarVectorChannel("locationCoordinateV", 4);				//	LOCATION_COORDINATE
				f.appendScalarVectorChannel("compositionColorV", 4);				//	COMPOSITION_COLOR
				
				return	f;
			}
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		struct
		CPUTransformDebuggingLineDrawer::Core
		{
			Program								program						{{VERTEX_SHADER_CODE}, {FRAGMENT_SHADER_CODE}};
			local<ProgramUniformValueSlotProxy>	transformUniformIndex		{program.uniformValueSlotForName("localToWorldTransformP")};
			
			VertexComponentChannelingDescriptor	channeling					{VertexComponentChannelingDescriptor::analyze(make_vertex_format(), program)};
		};
		
		
		
		
		
		
		
		
		
		
		
		
		CPUTransformDebuggingLineDrawer::CPUTransformDebuggingLineDrawer()
		{
			_core_ptr		=	uptr<Core>{new Core{}};
		}
		CPUTransformDebuggingLineDrawer::~CPUTransformDebuggingLineDrawer()
		{
		}
		
		auto CPUTransformDebuggingLineDrawer::
		drawInstances(const vec<Instance> &instances, const Matrix4 &worldToScreenTransform) const -> void
		{
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion(instances.size() >0, "You must pass at least one or more instances. No instance cannot be rendered.");
				for (auto const& i: instances)
				{
					err9_converted_legacy_assertion(i.origination.location.w == 1);
					err9_converted_legacy_assertion(i.destination.location.w == 1);
				}
			}
			
			////
			
			////
			
			M().useProgram(_core_ptr->program);
			{
				auto&	transform_uniform_slot	=	*_core_ptr->transformUniformIndex;
				
				transform_uniform_slot.setValue(worldToScreenTransform);
				{
					GenericMemoryRange<void const>		range1	{instances.data(), instances.data() + instances.size()};
					ClientMemoryVertexProvisioning		verts1	{range1, _core_ptr->channeling};
					GeometryProvisioning				geomp1	{&verts1};
					
					draw(geomp1, DrawingMode::LINES, {0, instances.size() * 2});
				}
				transform_uniform_slot.unset();
			}
			M().unuseProgram();
		}
		
		
		

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END

