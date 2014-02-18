//
//  FigureDrawer.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/17/13.
//
//

#include "FigureDrawer.h"
#include "../Server/Machine.h"





namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	using namespace	Server;
	
	namespace
	{
//			using BoneIndex	=	UInt32;
//			
//			struct
//			{
//				Vector3			spaceCoordinate;
//				Vector3			normalDirection;
//			}
//			geom;
//			
//			struct
//			{
//				Vector2			mappingCoordinate;
//			}
//			texture;
//			
//			struct
//			{
//				struct
//				{
//					BoneIndex	boneIndex;
//					Scalar		applicationIntensity;
//				}
//				influences[4];
//			}
//			deform;
		
		
		
		_Legacy2013_SharingBox<Program>
		figureDrawingProgramForMachine(Machine const& m)
		{
			std::string const	vsc	=
			""
			"uniform	mat4	transforMatrix;"			//	Matrix which transforms a point in object space into screen space. (object -> world -> camera -> NDC -> screen)
			"uniform	mat4	boneTransforms[128];"
			""
			"attribute	vec3	spaceCoordinate;"
			"attribute	vec3	normalDirection;"
			"attribute	vec2	mappingCoordinate;"
			"attribute	float	boneIndex0;"
			"attribute	float	boneIntensity0;"
			"attribute	float	boneIndex1;"
			"attribute	float	boneIntensity1;"
			"attribute	float	boneIndex2;"
			"attribute	float	boneIntensity2;"
			"attribute	float	boneIndex3;"
			"attribute	float	boneIntensity3;"
			""
			"void"
			"resolvePosition()"
			"{"
			"	vec3		v0	=	spaceCoordinate;"
			"	vec4		v1	=	vec4(v.x, v.y, v.z, 1);"
			"	vec4		v2	=	transformMatrix * v1;"
			"	return		v2;"
			"}"
			""
			"void main(void)"
			"{"
			"	gl_Position		=	resolvePosition();"
			"}"
			;
			
			std::string			fsc	=
			""
			"void main (void)"
			"{"
			"	gl_FragColor	=	vec4(1,1,0,1);"
			"}";
			
			using MAP	=	std::map<std::string, VertexAttributeChannel const&>;
			using PAIR	=	std::pair<std::string, VertexAttributeChannel const&>;
			
			MAP	chmap;
			chmap.insert(PAIR("spaceCoordinate", m.vertexAttributeChannelAtIndex(0)));
			chmap.insert(PAIR("normalDirection", m.vertexAttributeChannelAtIndex(1)));
			chmap.insert(PAIR("mappingCoordinate", m.vertexAttributeChannelAtIndex(2)));
			chmap.insert(PAIR("boneIndex0", m.vertexAttributeChannelAtIndex(3)));
			chmap.insert(PAIR("boneIntensity0", m.vertexAttributeChannelAtIndex(4)));
			chmap.insert(PAIR("boneIndex1", m.vertexAttributeChannelAtIndex(5)));
			chmap.insert(PAIR("boneIntensity1", m.vertexAttributeChannelAtIndex(6)));
			chmap.insert(PAIR("boneIndex2", m.vertexAttributeChannelAtIndex(7)));
			chmap.insert(PAIR("boneIntensity2", m.vertexAttributeChannelAtIndex(8)));
			chmap.insert(PAIR("boneIndex3", m.vertexAttributeChannelAtIndex(9)));
			chmap.insert(PAIR("boneIntensity3", m.vertexAttributeChannelAtIndex(10)));
			return	_Legacy2013_SharingBox<Program>(new Program(VertexShader(vsc, chmap), FragmentShader(fsc)));
		}
	}
	
	FigureDrawer::FigureDrawer() : _p(figureDrawingProgramForMachine(Machine::machine()))
	{
	}
	
	
	
	void
	FigureDrawer::drawFigureUsingCamera(const Eonil::Improvisations::MediaEngine::Graphics::Form::Figure figure, const Eonil::Improvisations::MediaEngine::Graphics::Camera camera) const
	{
//			DeformingMesh const&		mesh	=	figure.model.mesh();
//			Size const
		
//			Machine::machine().setVertexSourcingParameters(VertexSourcingWithServerBuffer(mesh.vertexes()));
		
//			Machine::machine().drawArrays(Machine::DrawingMode::TRIANGLES, 0, <#const Size count#>)
//			Machine::machine().drawElementsUsingServerBuffer(Machine::DrawingMode::TRIANGLE_STRIP, unit_count, Machine::IndexType::CODE::UINT16, <#const Eonil::Improvisations::MediaEngine::Graphics::Server::ElementArrayBuffer buffer#>, <#const Size offset#>)
	}
	
	
	
	
	
	
	
	
}}}}









