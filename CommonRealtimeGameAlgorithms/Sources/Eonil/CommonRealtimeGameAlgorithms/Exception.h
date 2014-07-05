//
//  Exception.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 14/4/30.
//
//

#pragma once
#include "CommonRealtimeGameAlgorithmsCommon.h"
EONIL_COMMON_REALTIME_GAME_ALGORITHMS_BEGIN







/*!
 Root class of categorization.
 */
class
Exception : public std::logic_error
{
public:
	virtual ~Exception();

protected:
	Exception() = delete;
	Exception(Exception const&) = default;
	Exception(std::string const& domain, std::string const& category, std::string const& message);
	
private:
	std::string const		domain		=	"";
	std::string const		category	=	"";
	std::string const		message		=	"";
};









/*!
 Represents **recoverable** exception.
 
 @discussion
 This is thrown when the code can guarantee *strong exception safety*.
 No changes are made, and no memory leaked. You can just safely treat
 all the trials are fully rollback, and continue program execution.
 
 This is mostly about input validation.
 If the function cannot provide strong exception safety, that means 
 the execution is unrecoverable, and it should throw `Halt` instead of.
 
 This mean;
 
 -	The library has no bug on the case.
 -	Your input is wrong.
 -	So you can recover.
 
 @classdesign
 You are expected to subclass this class to represent same kind of exceptions.
 
 @note
 Some code may explicitly return/output this object if they cannot afford
 exception catching cost.
 */
class
Error : public Exception
{
public:
	Error() = delete;
	Error(Error const&) = default;
	Error(std::string const& domain, std::string const& message);
	virtual ~Error();
};







/*!
 Represents **UNRECOVERABLE** exception.
 
 @discussion
 This is thrown when unrecoverable state corruption has been dicsovered.
 Though this library guarantees strong exception safety, state can be corrupted
 by bugs. So this is a result of bug detections, mostly about logical integrity.
 
 This means;
 
 -	The library may contain a BUG.
 -	You input doesn't matter.
 -	Program should crash to prevent further damage.
 
 @warning
 NEVER try to recover from this kind of exception. Program state already corrupted.
 
 @classdesign
 You are expected to subclass this class to represent same kind of exceptions.
 */
class
Crash : public Exception
{
public:
	Crash() = delete;
	Crash(Crash const&) = default;
	Crash(std::string const& domain, std::string const& message);
	virtual ~Crash();
};







EONIL_COMMON_REALTIME_GAME_ALGORITHMS_END

