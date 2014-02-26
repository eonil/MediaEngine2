//
//  CPUTransformSpriteDrawer.cpp
//  Graphics
//
//  Created by Hoon H. on 2/19/14.
//
//

#include "CPUTransformSpriteDrawer.h"

#include "../../Server/Symbols.h"
#include "../../Server/Texture.h"
#include "../../Server/Machine.h"
#include "../../Server/Machinery/VertexAttributeChannel.h"
#include "../../Server/Utility/VertexLayoutDescriptor.h"
#include "../../Server/Utility/UniformProgramParameter.h"
#include "../../Server/Utility/ProgramVertexChannelingDescriptor.h"
#include "../../Server/Utility/Functions.h"

/*!
 
 OpenGL 2.0 does not support geometry instancing.
 
 */







namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{
			using namespace	Server::Utility;
			
			
			namespace
			{
				
				static constexpr char const
				VERTEX_SHADER_CODE[]	=
#include "CPUTransformSpriteDrawer.vertex.shader"
				;
				
				static constexpr char const
				FRAGMENT_SHADER_CODE[]	=
#if EONIL_MEDIA_ENGINE_TARGET_IOS
#include "CPUTransformSpriteDrawer.es.fragment.shader"
#endif
#if EONIL_MEDIA_ENGINE_TARGET_OSX
#include "CPUTransformSpriteDrawer.dt.fragment.shader"
#endif
				;
				
				
				
				
				
				
				static inline auto
				M() -> Machine&
				{
					return	Machine::machine();
				}
				
				enum
				VERTEX_CHANNEL_INDEXES : Size
				{
					POSITION_COORDINATE		=	0,
					COLOR_COORDINATE		=	1,
					COMPOSITION_COLOR		=	2,
				};
				
				static inline auto
				make_vertex_format() -> VertexLayoutDescriptor
				{
					VertexLayoutDescriptor	f{};
					f.appendScalarVectorChannel("positionCoordinateV", 2);
					f.appendScalarVectorChannel("textureCoordinateV", 2);
					f.appendScalarVectorChannel("compositionColorV", 4);
					
					return	f;
				}
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			struct
			CPUTransformSpriteDrawer::Core
			{
				Program								program			{{VERTEX_SHADER_CODE}, {FRAGMENT_SHADER_CODE}};
				VertexLayoutDescriptor				layout			{make_vertex_format()};
				ProgramVertexChannelingDescriptor	channeling		{ProgramVertexChannelingDescriptor::analyze(layout, program)};
	
			};
			
			
			
			
			
			
			
			
			
			
			
			
			CPUTransformSpriteDrawer::CPUTransformSpriteDrawer() : _core_ptr(new Core())
			{
			}
			CPUTransformSpriteDrawer::~CPUTransformSpriteDrawer()
			{
			}
			
			auto CPUTransformSpriteDrawer::
			drawInstances(PlanarTexture const& colorTexture, Bounds2 const& samplingRegion, vec<UniformScalingInstance> const& instances, Matrix4 const& worldToScreenTransform, DisplayScreenFrame const& frame) const -> void
			{
				/*!
				 @todo
				 There're a lot of room for optimization in this function. Do them all.
				 */
				
				struct
				Vertex
				{
					Vector2		p;
					Vector2		uv;
					Vector4		c;
				}
				__attribute__((aligned(16)));
				
				vec<Vertex>	vs{};
				
				////
				
				Vector2		lbuv	=	samplingRegion.minimum;
				Vector2		rtuv	=	samplingRegion.maximum;
				Vector2		ltuv	=	Vector2(lbuv.x, rtuv.y);
				Vector2		rbuv	=	Vector2(rtuv.x, lbuv.y);
				
				for (auto const& inst: instances)
				{
					Matrix4	t0	=	Matrix4::Utility::identity();
					Matrix4	t1	=	Matrix4::Utility::scaleWithUniformScalar(inst.scale) * t0;
					Matrix4	t2	=	Matrix4::Utility::rotationWithQuaternion(inst.rotation) * t1;
					Matrix4	t3	=	Matrix4::Utility::translationWithVector(inst.translation) * t2;
					
					auto	make_vertex	=
					[&inst, &t3](Vector3 const& p, Vector2 const& uv) -> Vertex
					{
						Vector3	p2	=	t3.transform(p);
						
						Vertex	v{};
						v.p		=	Vector2(p2.x, p2.y);
						v.uv	=	uv;
						v.c		=	inst.color;
						return	v;
					};
					
					Vector3	lbp	=	Vector3(-1,-1,0);
					Vector3	rbp	=	Vector3(+1,-1,0);
					Vector3	ltp	=	Vector3(-1,+1,0);
					Vector3	rtp	=	Vector3(+1,+1,0);
						
					Vertex	lbv	=	make_vertex(lbp, lbuv);
					Vertex	rbv	=	make_vertex(rbp, rbuv);
					Vertex	ltv	=	make_vertex(ltp, ltuv);
					Vertex	rtv	=	make_vertex(rtp, rtuv);
					
					vs.push_back(lbv);
					vs.push_back(rbv);
					vs.push_back(ltv);
					
					vs.push_back(ltv);
					vs.push_back(rbv);
					vs.push_back(rtv);
				}
				
				////
				
				Machine::machine().useProgram(_core_ptr->program);
				draw(vs.data(), _core_ptr->layout, _core_ptr->channeling, colorTexture, DrawingMode::TRIANGLES, Range::fromAdvancement(0,instances.size() * 6));
				Machine::machine().unuseProgram();
			}

			auto CPUTransformSpriteDrawer::
			drawInstances(PlanarTexture const& colorTexture, vec<UniformScalingInstance> const& instances, Matrix4 const& worldToScreenTransform, DisplayScreenFrame const& frame) const -> void
			{
				drawInstances(colorTexture, Bounds2{0,0,1,1}, instances, worldToScreenTransform, frame);
			}

			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
				
				
		}
	}
				
}}}}
