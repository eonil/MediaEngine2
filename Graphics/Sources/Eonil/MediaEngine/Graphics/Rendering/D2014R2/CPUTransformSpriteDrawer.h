//
//  CPUTransformSpriteDrawer.h
//  Graphics
//
//  Created by Hoon H. on 2/19/14.
//
//

#pragma once
#include "RenderingD2014R2Common.h"
#include "PlanarTexture.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN






/*!
 A flexible sprite drawer which transforms all vertices in client-side (CPU).
 
 @classdesign
 This is written for dynamic 2D sprite shading in 3D space. We can perform 
 transform in any of CPU or GPU, and each of them provides different performance
 characteristics. Choose whichever fits better to your situation.
 */
class
CPUTransformSpriteDrawer
{
	struct	Core;
	
	uptr<Core>		_core_ptr	{};
	
public:
	struct
	EONIL_MEDIA_ENGINE_DEPRECATE()
	UniformScalingInstance
	{
		Scalar		scale			{1};
		Vector3		translation		{0,0,0};
		Quaternion	rotation		{Quaternion::Utility::identity()};
		Vector4		color			{1,1,1,1};		//	Will be multiplied to texture color.
	};
	struct
	FreeTransformInstance
	{
		Matrix4		transform		=	Matrix4::Utility::identity();
		Vector4		color			=	{1,1,1,1};						//	Will be multiplied to texture color.
	};
	
public:
	CPUTransformSpriteDrawer();
	~CPUTransformSpriteDrawer();

	/*!
	 Draws 2x2 sized (-1,-1) ~ (+1,+1) instances using part of a texture.
	 
	 @discussion
	 Drawn texture will fully fill the screen if transform is identity.
	 
	 @param	samplingRegion
	 Measured in texture UV space. (0,0) is left-bottom origin point, and
	 (+1,+1) is right-top point. This library is based on OpenGL coordination
	 system, and expects top of the image to be (x,+1).
	 You can coordinate out of (0~1) range. In that case, texture will be
	 sampled according to its wraping mode.
	 If you want to specify whole texture, then set this to {0,0,1,1}.
	 Whatever you specified, the drawn sprite size is same. If you specify
	 smaller portion, it will fill the 2x2 sized box.
	 
	 @param	worldToScreenTransform
	 This must be a whole transform from world to final screen (NDC).
	 Take care that final destination space is NDC, not RSS.
	 
	 */
	auto	drawInstances(PlanarTexture const& colorTexture, Bounds2 const& samplingRegion, vec<FreeTransformInstance> const& instances, Matrix4 const& worldToScreenTransform) const -> void;
	auto	drawInstances(PlanarTexture const& colorTexture, Bounds2 const& samplingRegion, vec<FreeTransformInstance> const& instances, Matrix4 const& worldToScreenTransform, DisplayScreenFrame const& frame) const -> void;
	
	/*!
	 Draws 2x2 sized  instances using whole texture region.
	 */
	auto	drawInstances(PlanarTexture const& colorTexture, vec<FreeTransformInstance> const& instances, Matrix4 const& worldToScreenTransform, DisplayScreenFrame const& frame) const -> void;

	auto	EONIL_MEDIA_ENGINE_DEPRECATE() drawInstances(PlanarTexture const& colorTexture, Bounds2 const& samplingRegion, vec<UniformScalingInstance> const& instances, Matrix4 const& worldToScreenTransform, DisplayScreenFrame const& frame) const -> void;
	auto	EONIL_MEDIA_ENGINE_DEPRECATE() drawInstances(PlanarTexture const& colorTexture, vec<UniformScalingInstance> const& instances, Matrix4 const& worldToScreenTransform, DisplayScreenFrame const& frame) const -> void;
};









EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END
