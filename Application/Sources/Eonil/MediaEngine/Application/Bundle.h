//
//  Bundle.h
//  Application
//
//  Created by Hoon H. on 2/26/14.
//
//

#ifndef __Application__Bundle__
#define __Application__Bundle__

#include <Eonil/MediaEngine/Foundation.h>

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Application {
	
	
	
	
	
	
	
	
	
	
	using namespace	Eonil::Improvisations::MediaEngine::Foundation;
	
	/*!
	 Provides access to resource files included in application bundle.
	 
	 
	 @discussion
	 Bundle class is designed to provide simple access to resources
	 packaged with the final product. This is designed for a small 
	 amount of read-only resource files, and doesn't fit for many 
	 complex resource items. You need to use your own management 
	 system yourself. I recommend *ERTE* for complex and large 
	 resource management.
	 */
	class
	Bundle
	{
		class	Core;
		
		uptr<Core>	_core_ptr{};
		
		Bundle(str const& rootDirectoryPath);
		
	public:
		Bundle();
		
		/*!
		 Retrieve a path to a file in the default application's resource directory.
		 */
		auto	pathForResource(str const& location, str const& name, str const& type) const -> str;
		
	public:
		static auto	main() -> Bundle const&;
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__Application__Bundle__) */
