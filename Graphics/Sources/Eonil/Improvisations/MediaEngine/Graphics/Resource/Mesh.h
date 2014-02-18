//
//  Mesh.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/13/13.
//
//

#ifndef __EonilGraphics__Mesh__
#define __EonilGraphics__Mesh__

#include "../Common.h"
#include "../Debugging/Doctor.h"
#include "../Server/Buffer.h"
#include "../Server/Texture.h"
#include "../Server/Program.h"
#include "../Server/_Legacy2013Compat.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Resource
	{
		using namespace Debugging;
		using namespace Value;
		using namespace Server;
		
		
		struct
		DebuggingMeshBase
		{
//				struct
//				{
//					Eonil::Improvisations::MediaEngine::Foundation::_Legacy2013::SharedMemory	vertexes;
//				}
//				DBG;
		};
		
		/*!
		 3D shape.
		 
		 Mesh vertexes are write-only on release build. Read method are
		 not exist on release build. Because mesh disposes any redundent 
		 data after dispatching it to GPU to save memory.
		 Debug build will keep the data in memory for runtime introspection,
		 */
		template<typename V, typename I, typename P>
		class
		Mesh : DebuggingMeshBase
		{
			static_assert(std::is_standard_layout<V>::value, "Vertex type `V` must be a POD type.");
			static_assert(std::is_integral<I>::value, "Index type `I` must be an integral type.");
			static_assert(std::is_unsigned<I>::value, "Index type `I` must be an unsigned type.");
			static_assert(sizeof(I) == 1 or sizeof(I) == 2, "Size of index type `I` must be 1 or 2.");
//				static_assert(sizeof(I) == 2 or sizeof(I) == 4, "Size of index type `I` must be 2 or 4.");
			
		public:
			using	Index		=	I;
			using	Vertex		=	V;
			
			struct
			Section
			{
				std::vector<Index>							indexes;
				_Legacy2013_SharingBox<Program> 			program;
				_Legacy2013_SharingBox<PlanarTexture>		texture;
				
				Section(std::vector<Index> const indexes, Program const program, PlanarTexture const texture);
			};
//			static_assert(std::is_standard_layout<Section>::value, "");
			
		public:
			Mesh(_Legacy2013_SharingBox<ArrayBuffer> vertexes, _Legacy2013_SharingBox<ElementArrayBuffer> indexes, std::vector<Section const> const sections);
//				Mesh(Mesh const& other);
			
			ArrayBuffer const&			vertexes() const;
			ElementArrayBuffer const&	indexes() const;
			std::vector<Section> const&	sections() const;
			
//				void	drawUsingParameters(P const parameters) const;
			
		private:
			struct
			State
			{
				_Legacy2013_SharingBox<ArrayBuffer>				vb{nullptr};
				_Legacy2013_SharingBox<ElementArrayBuffer>		ib;
				std::vector<Section const>			ss;
				
				State(_Legacy2013_SharingBox<ArrayBuffer> vb, _Legacy2013_SharingBox<ElementArrayBuffer> ib, std::vector<Section const> const ss);
			};
			
			std::shared_ptr<State const> const	_st_ptr;
		};

	}
	
	
	
	
	
	
	
	
}}}}























#pragma mark	-	Implementation

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Resource
	{
		template<typename V, typename I, typename P>
		Mesh<V, I, P>::State::State(_Legacy2013_SharingBox<ArrayBuffer> vb, _Legacy2013_SharingBox<ElementArrayBuffer> ib, std::vector<Section const> const ss) : vb(vb), ib(ib), ss(ss)
		{
		}
		
		template<typename V, typename I, typename P>
		Mesh<V, I, P>::Mesh(_Legacy2013_SharingBox<ArrayBuffer> vertexes, _Legacy2013_SharingBox<ElementArrayBuffer> indexes, std::vector<Section const> const sections)
		: _st_ptr(new State(vertexes, indexes, sections))
		{
		}
		
//			template<typename V>
//			Mesh<V>::Mesh(Mesh const& other) : _st_ptr(other._st_ptr)
//			{
//			}
		
		
//			template<typename V, typename I, typename P> auto
//			Mesh<V, I, P>::drawUsingParameters(const P parameters) const -> void
//			{
//				Debugging::Doctor::exceptWithReason("Drawing method is not implemented! It should be implemented in specialized form.");
//			}
	}
	
	
	
	
	
	
	
}}}}




























#pragma mark	-	Specialization

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Resource
	{

		
		
		/*!
		 Indeformable mesh vertex.
		 */
		struct
		StaticVertex
		{
			struct
			{
				Vector3			spaceCoordinate;
				Vector3			normalDirection;
			}
			geom;
			
			struct
			{
				Vector2			mappingCoordinate;
			}
			texture;
		};
		static_assert(std::is_standard_layout<StaticVertex>::value, "");
		static_assert(sizeof(StaticVertex) == sizeof(Scalar) * 8, "");
		
		/*!
		 Deformable mesh vertex.
		 */
		struct
		SkinningVertex
		{
			using BoneIndex	=	UInt32;
			
			struct
			{
				Vector3			spaceCoordinate;
				Vector3			normalDirection;
			}
			geom;
			
			struct
			{
				Vector2			mappingCoordinate;
			}
			texture;
			
			struct
			{
				struct
				{
					BoneIndex	boneIndex;
					Scalar		applicationIntensity;
				}
				influences[4];
			}
			deform;
		};
		static_assert(std::is_standard_layout<SkinningVertex>::value, "");
		static_assert(sizeof(SkinningVertex) == sizeof(StaticVertex) + sizeof(Scalar) * (2 * 4), "");
		
		
		
		
		struct
		MeshDrawingParameters
		{
			Matrix4		transform;
//				Vector3		ambientLightColor;
//				Vector3		lightDirection;
		};
		struct
		StaticMeshDrawingParameters
		{
			
		};
		struct
		DeformingMeshDrawingParameters
		{
			std::vector<Matrix4>	boneTransforms;
		};
		
		
		
		
		
		
		
		class
		StaticMesh : public Mesh<StaticVertex, UInt16, StaticMeshDrawingParameters>
		{
		public:
			StaticMesh(_Legacy2013_SharingBox<ArrayBuffer> vertexes, _Legacy2013_SharingBox<ElementArrayBuffer> indexes, std::vector<Section const> const sections);
		};
		
		class
		DeformingMesh : public Mesh<SkinningVertex, UInt16, DeformingMeshDrawingParameters>
		{
		public:
			DeformingMesh(_Legacy2013_SharingBox<ArrayBuffer> vertexes, _Legacy2013_SharingBox<ElementArrayBuffer> indexes, std::vector<Section const> const sections);
		};

	}
	
	
	
	
	
	
	
	
}}}}




#endif /* defined(__EonilGraphics__Mesh__) */
