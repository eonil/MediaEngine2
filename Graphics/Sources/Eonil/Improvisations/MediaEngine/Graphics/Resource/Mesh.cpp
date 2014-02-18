//
//  Mesh.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/13/13.
//
//

#include "Mesh.h"




namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Resource
	{
		


		
		StaticMesh::StaticMesh(_Legacy2013_SharingBox<ArrayBuffer> vertexes, _Legacy2013_SharingBox<ElementArrayBuffer> indexes, std::vector<Section const> const sections)
		: Mesh<Eonil::Improvisations::MediaEngine::Graphics::Resource::StaticVertex, UInt16, StaticMeshDrawingParameters>(vertexes, indexes, sections)
		{
		}
		DeformingMesh::DeformingMesh(_Legacy2013_SharingBox<ArrayBuffer> vertexes, _Legacy2013_SharingBox<ElementArrayBuffer> indexes, std::vector<Section const> const sections)
		: Mesh<Eonil::Improvisations::MediaEngine::Graphics::Resource::SkinningVertex, UInt16, DeformingMeshDrawingParameters>(vertexes, indexes, sections)
		{
		}
		
	}
	
	
	
	
	
	
	
	
}}}}
