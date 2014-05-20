//
//  Scope.h
//  TheMagnetismGame
//
//  Created by Hoon H. on 2014/05/18.
//  Copyright (c) 2014 Eonil Company. All rights reserved.
//

#pragma once
#include "Transform.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN






/*!
 Parametrically transforms coordinates into another space.
 
 @discussion
 Transformation into RSS instead of GL space provides aspect-ratio
 independent transformation.
 */
class
Scope
{
public:
	virtual ~Scope() = default;
	
	virtual auto	transformationMatrix() const -> Matrix4 = 0;
};









/*!
 Simplest bare transform scope.
 
 @discussion
 This class is designed to be used directly in your game.
 You also can use one of subclasses.
 */
class
TransformScope : public Scope
{
public:
	struct
	State
	{
		Transform	transform	=	{};
	};
	
public:
	auto	state() const -> State const&;
	auto	state() -> State&;
	
public:
	virtual auto	transformationMatrix() const -> Matrix4;
	
private:
	State	_state	=	{};
};







class
OrthographicScope : public Scope
{
public:
	/*
	 No defined yet.
	 Extra properties can be added later.
	 */
public:
	virtual auto	transformationMatrix() const -> Matrix4;
private:
};

class
PerspectiveScope : public Scope
{
public:
	/*
	 No defined yet.
	 Extra properties can be added later.
	 */
public:
	virtual auto	transformationMatrix() const -> Matrix4;
private:
};

class
BlendingTransitionScope : public Scope
{
public:
	BlendingTransitionScope() = delete;
	BlendingTransitionScope(Scope const* start, Scope const* finish);
	
	auto	progress() const -> Scalar;
	auto	setProgress(Scalar const) -> void;
	
public:
	virtual auto	transformationMatrix() const -> Matrix4
	{
		Matrix4 const	a	=	_start->transformationMatrix();
		Matrix4 const	b	=	_finish->transformationMatrix();
		Matrix4 const	c	=	a * (Scalar(1) - _progress) + b * _progress;
		
		return	c;
	}
	
private:
	Scope const*	_start		=	nullptr;
	Scope const*	_finish		=	nullptr;
	Scalar			_progress	=	0;
};











EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END
