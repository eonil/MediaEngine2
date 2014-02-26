//
//  Bundle.h
//  Application
//
//  Created by Hoon H. on 2/26/14.
//
//

#ifndef __Application__Bundle__
#define __Application__Bundle__

#include <Eonil/Improvisations/MediaEngine/Foundation/Foundation.h>

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Application {
	
	
	
	
	
	
	
	
	
	
	using namespace	Eonil::Improvisations::MediaEngine::Foundation;
	
	/*!
	 Provides access to resource files included in application bundle.
	 */
	class
	Bundle
	{
		class	Core;
		
		uptr<Core>	_core_ptr{};
		
		Bundle(str const& rootDirectoryPath);
		
	public:
		Bundle();
		
		auto	pathForResource(str const& location, str const& name, str const& type) const -> str;
		
	public:
		static auto	main() -> Bundle const&;
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__Application__Bundle__) */

