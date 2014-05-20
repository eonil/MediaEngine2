//
//  Cloud.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/12/13.
//
//

#ifndef __EonilGraphics__Cloud__
#define __EonilGraphics__Cloud__

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Form
	{
		/*!
		 A collection of multiple particles.
		 */
		class
		Cloud
		{
			int		dummy_to_avoid_memory_allocation_error;		//!	@todo	remove this.
			
			bool const		shouldIgnoreRotation() const;
			void			setIgnoreRotation(bool ignore = true);
		};
	}
	
	


}}}}

#endif /* defined(__EonilGraphics__Cloud__) */
