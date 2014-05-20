//
//  Common.h
//  Application
//
//  Created by Hoon H. on 2014/05/18.
//
//

#pragma once
#include <memory>
#include <Eonil/MediaEngine/Foundation.h>
#include <Eonil/MediaEngine/Mathematics.h>
#include <Eonil/CommonRealtimeGameAlgorithms.h>
#include "../Application/Application.h"
#define EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_BEGIN		namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Controlling {
#define EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_END		} } } }
#define EONIL_MEDIA_ENGINE_CONTROLLING_DEBUG_ASSERT			EONIL_DEBUG_ASSERT





EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_BEGIN
using namespace	Mathematics;
using namespace	Mathematics::Geometry;
//using namespace	Eonil::CommonRealtimeGameAlgorithms;
using namespace	Eonil::CommonRealtimeGameAlgorithms::FlatContainers;
class	DraggingGesture;
EONIL_MEDIA_ENGINE_CONTROLLING_NAMESPACE_END