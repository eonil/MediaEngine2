//
//  Common.h
//  Aliens
//
//  Created by Hoon H. on 14/4/25.
//
//

#pragma once

#define	EONIL_ALIENS_NAMESPACE_BEGIN			namespace Eonil { namespace Aliens {
#define	EONIL_ALIENS_NAMESPACE_END				} }







#include <memory>
#include <vector>

EONIL_ALIENS_NAMESPACE_BEGIN

inline auto
EONIL_ALIENS_DEBUG_ASSERT(bool cond) -> void
{
	if (not cond)
	{
		std::terminate();
	}
}

EONIL_ALIENS_NAMESPACE_END







