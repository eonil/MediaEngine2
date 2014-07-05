//
//  CommonRealtimeGameAlgorithmsCommon.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 14/4/29.
//
//

#pragma once

#ifndef EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_MODE
#error	"You must define `EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_MODE` to one of `1`(true) or `0`(false) in preprocessor flags."
#endif

#ifndef EONIL_COMMON_REALTIME_GAME_ALGORITHMS_HEAVY_TRACE_DEBUG_MODE
#define	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_HEAVY_TRACE_DEBUG_MODE				EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_MODE
#endif


#define EONIL_COMMON_REALTIME_GAME_ALGORITHMS_BEGIN									namespace Eonil { namespace CommonRealtimeGameAlgorithms {
#define EONIL_COMMON_REALTIME_GAME_ALGORITHMS_END									} }

#define EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUGGING_TOOLS_BEGIN					namespace Eonil { namespace CommonRealtimeGameAlgorithms { namespace DebuggingTools {
#define EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUGGING_TOOLS_END					} } }

#define EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DATA_STRUCTURES_TOOLS_BEGIN			namespace Eonil { namespace CommonRealtimeGameAlgorithms { namespace DataStructures {
#define EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DATA_STRUCTURES_TOOLS_END				} } }

#define EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_BEGIN					namespace Eonil { namespace CommonRealtimeGameAlgorithms { namespace FlatContainers {
#define EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END					} } }

#define EONIL_COMMON_REALTIME_GAME_ALGORITHMS_GENERIC_UTILITIES_BEGIN				namespace Eonil { namespace CommonRealtimeGameAlgorithms { namespace GenericUtilities {
#define EONIL_COMMON_REALTIME_GAME_ALGORITHMS_GENERIC_UTILITIES_END					} } }



#include <memory>
#include <string>
#include <set>



EONIL_COMMON_REALTIME_GAME_ALGORITHMS_BEGIN
using	Size		=	std::size_t;
using	str			=	std::string;
constexpr bool const	USE_EXCEPTION_CHECKINGS				=	(EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_MODE == 1);		//	Performs only checkings with O(1) complexity.
constexpr bool const	USE_HEAVY_EXCEPTION_CHECKINGS		=	(EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_MODE == 1);		//	*HEAVY* means O(n) or more complex operations.
constexpr char const*	EXCEPTION_DEFAULT_MESSAGE			=	"Reason unspecified. Use debugger to track source of the exception.";
auto	halt_if(bool const condition, std::string const& message = EXCEPTION_DEFAULT_MESSAGE) -> void;
auto	error_if(bool const condition, std::string const& message = EXCEPTION_DEFAULT_MESSAGE) -> void;
#if		EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_MODE
auto	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(bool const condition, std::string const& message = "[Eonil::CommonRealtimeGameAlgorithms] Assertion failure") -> void;
#else
#define EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(...)						//	Erase the macro for release mode.
#endif
//#if		EONIL_COMMON_REALTIME_GAME_ALGORITHMS_HEAVY_TRACE_DEBUG_MODE
//auto	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_HEAVY_TRACE_DEBUG_ASSERT(bool const condition, std::string const& message = "[Eonil::CommonRealtimeGameAlgorithms] **HEAVY-TRACE** Assertion failure!!!") -> void;
//#else
//#define EONIL_COMMON_REALTIME_GAME_ALGORITHMS_HEAVY_TRACE_DEBUG_ASSERT(...)				//	Erase the macro for release mode.
//#endif
/*!
 Must be zero-sized.
 */
struct
ExceptionSupportTools
{
protected:
	auto	_halt_if_this_is_null() const -> void;
	
	template <typename T> auto
	_error_if_supplied_reference_is_dereference_of_null(T const&o, std::string const& extra_description = "") const -> void
	{
		std::string	ex_desc2	=	extra_description.length() == 0 ? "" : (" (" + extra_description + ")");
		error_if(&o == nullptr, "Supplied object reference is actually dereference of `nullptr` and cannot be used on this operation." + ex_desc2);
	}
};
EONIL_COMMON_REALTIME_GAME_ALGORITHMS_END







EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_BEGIN
template <typename T, bool const ALIGNMENT>	class	ListAtomSlot;
template <typename T>						class	ListAtomSlotIterator;
//template <typename T>						class	ListAtomSlotRange;
template <typename T, Size const LEN>		class	StaticStableListStack;
template <typename T, Size const LEN>		class	StaticStableListMap;
template <typename T, Size const LEN>		class	StaticStableOrderlessSet;
template <typename T, Size const LEN>		class	StaticUnstableOrderlessSet;
EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END



//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_GENERIC_UTILITIES_BEGIN
//template <typename IT>						class	Range;
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_GENERIC_UTILITIES_END



























