//
//  BloomFilter.h
//  Graphics
//
//  Created by Hoon H. on 2/18/14.
//
//

#ifndef __Graphics__BloomFilter__
#define __Graphics__BloomFilter__

#include "../../Common.h"
#include "../../Server/Declarations.h"
#include "Scene.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{
			
			
			/*!
			 This performs alpha blending of multiple rendering-frame images.
			 
			 @discussion
			 This is different with object-level alpha-blending, and almost purely
			 pixel operation.
			 */
			class
			BloomFilter final
			{
				ptr<Server::PlanarTexture const>	_src_pass	{};
				
				uptr<Server::Program const>			_op_program	{};
				uptr<Server::PlanarTexture const>	_dst_tex	{};
				
			public:
				BloomFilter();
				~BloomFilter();
				
			public:
				BloomFilter(Server::PlanarTexture const& energyMap);
				
				auto	solution() const -> Server::PlanarTexture const&;
			};
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__BloomFilter__) */
