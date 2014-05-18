//
//  DebuggingInformationOverlayDrawer.cpp
//  Graphics
//
//  Created by Hoon H. on 2/22/14.
//
//

#include "DebuggingInformationOverlayDrawer.h"

#include "../../Server/Symbols.h"
#include "../../Server/Machine.h"
#include "../../Server/Agency/Agent.h"







namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{
			namespace
			{
				using	LINE	=	CPUTransformLineDrawer::Instance;
				using	POINT	=	CPUTransformLineDrawer::Point;
			}
			
			
			
			DebuggingInformationOverlayDrawer::DebuggingInformationOverlayDrawer(Scalar const& objectUniformScale) : _uni_scale(objectUniformScale)
			{
			}
			
			auto DebuggingInformationOverlayDrawer::
			objectUniformScale() const -> Scalar const&
			{
				return	_uni_scale;
			}
			auto DebuggingInformationOverlayDrawer::
			objectUniformScale() -> Scalar&
			{
				return	_uni_scale;
			}
			
			
			
			
			auto DebuggingInformationOverlayDrawer::
			drawNull(DisplayScreenFrame const& frame, Matrix4 const& transform, Vector3 const& radius) const -> void
			{
				Vector4		x_axis_color	{1,0,0,1};
				Vector4		y_axis_color	{0,1,0,1};
				Vector4		z_axis_color	{0,0,1,1};
				
				Vector3		zero			{0,0,0};
				Vector3		x_max			{radius.x, 0, 0};
				Vector3		y_max			{0, radius.y, 0};
				Vector3		z_max			{0, 0, radius.z};
				
				vec<LINE>	lines	{};
				
				lines.push_back(LINE{{+x_max, x_axis_color}, {-x_max, x_axis_color}});
				lines.push_back(LINE{{+y_max, y_axis_color}, {-y_max, y_axis_color}});
				lines.push_back(LINE{{+z_max, z_axis_color}, {-z_max, z_axis_color}});
				
				_line_drawer.drawInstances(lines, transform);
			}
			
			auto DebuggingInformationOverlayDrawer::
			drawBox(DisplayScreenFrame const& frame, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Matrix4 &transform, Vector2 const& halfSize, Vector4 const& color) const -> void
			{
				Vector4		c			{color};
				
				Scalar		x			{halfSize.x};
				Scalar		y			{halfSize.y};
				
				POINT		lt			{{-x, +y, 0}, c};
				POINT		rt			{{+x, +y, 0}, c};
				POINT		lb			{{-x, -y, 0}, c};
				POINT		rb			{{+x, -y, 0}, c};
				
				LINE		l0			{lb, lt};
				LINE		l1			{lt, rt};
				LINE		l2			{rt, rb};
				LINE		l3			{rb, lb};
				
				vec<LINE>	ls
				{
					
					{lb, lt},
					{lt, rt},
					{rt, rb},
					{rb, lb},
				};
				
				_line_drawer.drawInstances(ls, transform);
			}
			
			auto DebuggingInformationOverlayDrawer::
			drawCube(DisplayScreenFrame const& frame, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Matrix4 &transform, Vector3 const& halfSize, Vector4 const& color) const -> void
			{
				Vector4		c			{color};
				
				Scalar		x			{halfSize.x};
				Scalar		y			{halfSize.y};
				Scalar		z			{halfSize.z};
				
				POINT		ltn			{{-x, +y, -z}, c};
				POINT		rtn			{{+x, +y, -z}, c};
				POINT		lbn			{{-x, -y, -z}, c};
				POINT		rbn			{{+x, -y, -z}, c};
				
				POINT		ltf			{{-x, +y, +z}, c};
				POINT		rtf			{{+x, +y, +z}, c};
				POINT		lbf			{{-x, -y, +z}, c};
				POINT		rbf			{{+x, -y, +z}, c};
				
				vec<LINE>	ls
				{
					{lbn, ltn},
					{ltn, rtn},
					{rtn, rbn},
					{rbn, lbn},
					
					{lbf, ltf},
					{ltf, rtf},
					{rtf, rbf},
					{rbf, lbf},
				};
				
				_line_drawer.drawInstances(ls, transform);
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}
