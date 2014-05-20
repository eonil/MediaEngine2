//
//  run.h
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#ifndef __Application__run__
#define __Application__run__

#include <Eonil/MediaEngine/Foundation.h>
#include <Eonil/MediaEngine/Graphics.h>
#include "Stepping.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Application {
	
	using namespace	Eonil::Improvisations::MediaEngine::Foundation;
	using namespace	Eonil::Improvisations::MediaEngine::Graphics;
	using namespace	Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2;
	
	using	STEP	=	std::function<void(Stepping const&)>;
	using	PROC	=	std::function<void(void)>;
	
	
	
	/*!
	 Runs application loop.
	 
	 @param	step	
	 A function will be called for each frame.
	 This will be copied, so you must configure all captured variables to be safe for copying.
	 
	 @discussion
	 If you need to prepare/cleanup some stuffs, then do it before/after calling this function.
	 */
	auto
	run(int argc, char const *argv[], STEP const& step) -> int;
	
	
	auto
	run(int argc, char const *argv[], PROC const& prepare, PROC const &cleanup, STEP const &step) -> int;
	
	
	
	
	
	
	
	
	
	
	/*!
	 Runs application loop with custom system object class.
	 
	 @param	T
	 Platform-agnostic system class.
	 
	 @param	
	 Platform-specific extension class. Use `void` if you don't need platform specific extensions.
	 
	 @classdesign
	 Application will create, step and delete the system object.
	 It will be created after all the related resources are ready. For example, the *current GL 
	 context* will always be available while the system object is alive.
	 
	 This class must have these methods.
	 
		class T
		{
		public:
			T();										//	Put application-global prepare code.
			~T();										//	Put application-global cleanup code.
	 
			auto	step(Stepping const&) -> void;		//	Put application-global stepping code.
		};
		
	 The lifetime of this object is defined by the application system which is defined by underlying OS
	 design. Basically, you cannot control the lifespan managment because it's fixed by underlying OS. 
	 To support cross-platform behavior, only least common features will be supported, and that means 
	 your program should alaways be prepared for sudden termination. Because that's the minimally 
	 supported lifespan behavior. Specifically, the *iOS* does not support concept of generic program 
	 quitting by user. (only forced termination exists) Platform-placific behavior control method can be
	 added later, but not now.
	 
	 If the extension class `X` has been provided as non-`void` type, then application will also handle
	 the extension habevior. Anyway interface for the class `X` is all different by platforms. See
	 *Platform-Specific Customization* section in manual for required interface implementations.
	 
	 @discussion
	 Because the system object `T` will be created and deleted while all the related devices are ready,
	 you can safely perform preloading/post-cleanup in the constructor and desctructor. Anyway, by the
	 limitation of the application lifespan, the application cleanup routine is not likely to be run.
	 Then you shouldn't rely on cleanup routine, and must be prepared for sudden termination without
	 the cleanup. Anyway you still should to put fully logically complete cleanup routine because it 
	 will be called if appropriate.
	 */
	template <typename T>
	auto
	run(int argc, char const *argv[]) -> int
	{
		T	*sysptr	=	nullptr;
		
		return
		run(argc, argv,
		[&sysptr]()
		{
			sysptr	=	new T();
		},
		[&sysptr]()
		{
			delete	sysptr;
			sysptr	=	nullptr;
		},
		[&sysptr](Stepping const& context)
		{
			sysptr->step(context);
		});
	}
	
	
	
	
	
	
}}}}

#endif /* defined(__Application__run__) */
