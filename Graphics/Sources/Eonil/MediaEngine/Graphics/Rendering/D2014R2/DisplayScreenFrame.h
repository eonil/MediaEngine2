//
//  DisplayScreenFrame.h
//  Graphics
//
//  Created by Hoon H. on 2/23/14.
//
//

#pragma once
#include "RenderingD2014R2Common.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN








/*!
 Defines displaying area of a frame in a client window.
 
 @classdesign
 You should create only one of this class at a time. If you
 create multiple instances, GL state will be messed, and
 result is undefined.
 
 @discussion
 This symbolize existence of viewport definition. Literally, 
 this object set a viewport definition when being created, 
 and unset the viewport definition when being destroyed.
 */
class
DisplayScreenFrame
{
	struct	Core;
	
	uptr<Core>	_core_ptr	{};

	
public:
	/*!
	 @param	bounds
	 Bounding box of viewport in display window's local coordinate system.
	 */
	DisplayScreenFrame(Bounds2 const& bounds);
	~DisplayScreenFrame();
	
	/*!
	 Provides pixel dimension of the display surface.
	 Take care that this covers only display surface (client window), not a whole screen.
	 */
	auto	dimensionInPixels() const -> Bounds2;

	/*!
	 Creates a matrix which transforms points in RSS into NDC.
	 If you draw 2x2 square with this transform, it will become biggest filling square in the screen.
	 If the screen is non-square shape, then longer side will be padded.
	 */
	auto	regulationTransformMatrix() const -> Matrix4;
};









EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END


