//
//  error.h
//  CommonUtility
//
//  Created by Hoon H. on 2014/06/28.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#pragma once
#include "common.h"
EONIL_COMMONUTILITY_AGE2_NAMESPACE_BEGIN








/*!
 
 @header
 In my experience type of error isn't that much important.
 Only these stuffs are important;
 
 -	Is it RECOVERABLE?
 -	Is it because of current state or paramaters?
 
 Then, I categorized errors into three groups.
 
 1.	Recoverable, and because of the bad input parameter (new future state).
 2.	Recoverable, and because of improper current state.
 3.	Unrecoverable. Program state is already corrupted. Reason doesn't matter,
	and program must quit immediately to prevent further damage on data.
 
 There're several convenient error raising functions named in @c err~ manner.
 These functions will not be eliminated on release build, and you need to 
 manually exclude these stuffs by your own way. These functions are marked as
 @c static to support stripping off by C++ optimization. Then
 
 @internal
 This file contains internal-only features on most projects.
 
 @warning
 These functions doesn't handle any conditional compilation or release build
 elimination. You're responsible to do that.
 */










static constexpr char const* const	err_no_message	=	"(no message)";





[[noreturn]]
static inline auto
fail(str const& message = err_no_message) -> void
{
	/*
	 Throw properly typed error when you getting need it.
	 */
	throw	std::logic_error("Eonil::CommonUtility::age2/fail, message = " + message);
//	std::terminate();
}

static inline auto
fail_if(bool cond, str const& message = err_no_message) -> void
{
	if (cond)
	{
		fail(message);
	}
}











/*
 errors in lower number should be preferred and considered first.
 */

static inline auto
err1_recoverable_bad_input_parameter_if(bool cond, str const& message = err_no_message) -> void
{
	fail_if(cond, message);
}
[[noreturn]]
static inline auto
err1_recoverable_bad_input_parameter_always(str const& message = err_no_message) -> void
{
	fail(message);
}

static inline auto
err2_recoverable_program_state_is_not_proper_for_this_command_if(bool cond, str const& message = err_no_message) -> void
{
	fail_if(cond, message);
}
[[noreturn]]
static inline auto
err2_recoverable_program_state_is_not_proper_for_this_command_always(str const& message = err_no_message) -> void
{
	fail(message);
}





/*!
 @warning	this is very rare case! consider using of err2. most errors are recoverable in most cases.
 */
static inline auto
err3_UNRECOVERABLE_unexpected_inconsistent_program_state_DISCOVERED_and_seems_to_be_an_internal_logic_bug_if(bool cond, str const& message = err_no_message) -> void
{
	fail_if(cond, message);
}
[[noreturn]]
static inline auto
err3_UNRECOVERABLE_unexpected_inconsistent_program_state_DISCOVERED_and_seems_to_be_an_internal_logic_bug_always(str const& message = err_no_message) -> void
{
	fail(message);
}






































EONIL_COMMONUTILITY_AGE2_NAMESPACE_END
