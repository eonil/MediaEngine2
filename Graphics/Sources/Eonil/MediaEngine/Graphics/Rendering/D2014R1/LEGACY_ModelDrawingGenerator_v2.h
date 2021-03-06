//
//  _ModelDrawingGenerator_v2.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/28/13.
//
//

#ifndef __EonilGraphics___ModelDrawingGenerator_v2__
#define __EonilGraphics___ModelDrawingGenerator_v2__

#include "../../Common.h"
#include "../../Transcoding/LEGACY_ModelImporter_v2.h"
#include "LEGACY_SkinnedForm_v2.h"

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
	
	namespace
	Rendering
	{
		namespace
		D2014R1
		{
			
		
		
		
		
			
			
			
			class
			_ModelDrawingGenerator_v2
			{
			public:
				
				
				struct
				Moment
				{
					Eonil::Improvisations::MediaEngine::Graphics::Transcoding::_Model_v2::Ref		model	=	nullptr;
					Eonil::Improvisations::MediaEngine::Graphics::Transcoding::_Motion_v2 const*		motion	=	nullptr;
					Size												time	=	0;
				};
				
				/*!
				 A model may need to issue multiple mesh drawings.
				 */
				void	addToList(Moment const moment, std::vector<_SkinnedForm_v2>& list);
			};
			
			
			
			
		
		
		
		}
	}
		
}}}}

#endif /* defined(__EonilGraphics___ModelDrawingGenerator_v2__) */
