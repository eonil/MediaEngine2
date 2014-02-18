//
//  SpriteDrawer.h
//  Graphics
//
//  Created by Hoon H. on 2/18/14.
//
//

#ifndef __Graphics__SpriteDrawer__
#define __Graphics__SpriteDrawer__

#include "../../Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{
			
			
			
			
			/*!
			 */
			class
			SpriteDrawer
			{
				uptr<Server::Program>				_program	{};
				ptr<Server::PlanarTexture const>	_texture	{};
				
			public:
				struct
				Instance
				{
					Vector3		location	{0,0,0};
					Scalar		scale		{1};
					Vector4		color		{1,1,1,1};		//	Will be multiplied to texture color.
				};
				
			public:
				SpriteDrawer(Server::PlanarTexture const& texture);
				~SpriteDrawer();
				
				auto	drawInstances(vec<Instance> const& instances) const -> void;
			};
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__SpriteDrawer__) */
