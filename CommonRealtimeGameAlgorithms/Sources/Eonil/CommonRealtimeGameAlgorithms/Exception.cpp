//
//  Exception.cpp
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 14/4/30.
//
//

#include "Exception.h"
EONIL_COMMON_REALTIME_GAME_ALGORITHMS_BEGIN



namespace
{
	static inline auto
	compose_exc_msg(std::string const& domain, std::string const& category, std::string const& message) -> std::string
	{
		return	"[" + domain + "/" + category + "] " + message;
	}
}

Exception::Exception(std::string const& domain, std::string const& category, std::string const& message) : domain(domain), category(category), message(message), logic_error(compose_exc_msg(domain, category, message))
{
}
Exception::~Exception()
{
}

//auto
//Exception::what() const -> char const*
//{
//	return	logic_error::what();
//}

Error::Error(std::string const& domain, std::string const& message) : Exception(domain, "Error", message)
{
}
Error::~Error()
{
}

Crash::Crash(std::string const& domain, std::string const& message) : Exception(domain, "Crash", "(UNRECOVERABLE!!!) " + message)
{
}
Crash::~Crash()
{
}


EONIL_COMMON_REALTIME_GAME_ALGORITHMS_END