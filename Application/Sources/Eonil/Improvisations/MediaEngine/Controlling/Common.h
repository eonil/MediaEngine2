//
//  Common.h
//  Application
//
//  Created by Hoon H. on 2014/05/18.
//
//

#pragma once
#include <cstdint>
#include <memory>
#include <Eonil/Improvisations/MediaEngine/Foundation/Foundation.h>
#include <Eonil/Improvisations/MediaEngine/Mathematics/Mathematics.h>
#define	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_MODE	EONIL_DEBUG_MODE
#include <Eonil/CommonRealtimeGameAlgorithms.h>
#include "../Application/Application.h"
#define EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_BEGIN		namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Controlling {
#define EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_END		} } } }
#define EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT			EONIL_DEBUG_ASSERT





EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_BEGIN
using namespace	Mathematics;
using namespace	Mathematics::Value;
//using namespace	Eonil::CommonRealtimeGameAlgorithms;
using namespace	Eonil::CommonRealtimeGameAlgorithms::FlatContainers;
class	DraggingGesture;
EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_END