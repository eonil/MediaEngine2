//
//  SkinningStuffs.h
//  Graphics
//
//  Created by Hoon H. on 2014/05/20.
//
//

#pragma once
#include "../../RenderingCommon.h"
#include "../../../Server/Buffer.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN



/*
 All features in this file are just a sketch. Not actually implemented or tested.
 */



namespace
SkinningStuffs
{
	/*!
	 Animating bones are different problem.
	 */
	struct
	Bone
	{
		Vector3		position	=	{0,0,0};
	};
	
	struct
	SkinningAffection
	{
		Scalar		boneIndex	=	0;
		Scalar		weight		=	0;
	};
	
	struct
	SkinningVertex
	{
		using	AFXS	=	std::array<SkinningAffection,4>;
		
		////
		
		Vector3		position	=	{};
		Vector3		normal		=	{};
		Vector2		texture		=	{};
		AFXS		affections	=	{};
	};
	
	class
	CPUVertexList
	{
		vec<SkinningVertex>		vertexes		=	{};
		vec<uint16_t>			indexes			=	{};
	};
	
	class
	GPUVertexList
	{
		using	VTXBUF	=	Server::ArrayBuffer;
		using	IDXBUF	=	Server::ElementArrayBuffer;
		
		VTXBUF		vertexes		=	{};
		IDXBUF		indexes			=	{};
	};
	
	
	class
	CPUSkinMorphing
	{
	public:
		auto	operator()(CPUVertexList const& mesh, vec<Bone> const& skeleton) const -> CPUVertexList;
	};
	

}





EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END