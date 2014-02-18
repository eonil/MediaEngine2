//
//  Archive.cpp
//  Graphics
//
//  Created by Hoon H. on 2/5/14.
//
//

#include "Archive.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Debugging
	{






		auto
		Archive::summaryForAddress(const void *objectAddress) const -> str const&
		{
			return	_summary_map.at(objectAddress);
		}
		auto
		Archive::setSummaryForAddress(const void *objectAddress, const str &contentString) -> void
		{
			_summary_map[objectAddress]	=	contentString;
		}
		auto
		Archive::unsetSummaryForAddress(const void *objectAddress) -> void
		{
			_summary_map.erase(objectAddress);
		}






	}

}}}}