//
//  Foundation.h
//  Foundation
//
//  Created by Hoon H. on 2/5/14.
//
//

#pragma once

//#pragma		clang system_header
#include	"Platform/Targets.h"

#if			EE_LANG_CPP
#include	<memory>
#include 	<array>
#include	<string>
#include 	<vector>
#include	<list>
#include	<set>
#include	<map>
#include	<functional>

#include	"Prelude.h"
#include	"Debugging/Doctor.h"
#include	"Debugging/TestHelperMacros.h"

#include	"LocalCopyingAutomaticStorePointer.h"

#include	"D2014R1/GenericMemoryRange.h"
#include	"D2014R1/GenericMemoryBlock.h"
#include	"D2014R1/ObjectOwnershipTracking.h"

#endif


