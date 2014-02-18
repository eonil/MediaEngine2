//
//  Graphics.h
//  EonilGraphics
//
//  Created by Hoon H. on 2/5/14.
//
//

#ifndef __EonilGraphics__Graphics__
#define __EonilGraphics__Graphics__

#pragma	clang system_header


#include	<Eonil/Improvisations/MediaEngine/Foundation/Foundation.h>


#if		__cplusplus

#include "Common.h"

#include "Transform.h"
#include "Resource/Model.h"
#include "Resource/Mesh.h"
#include "Resource/Material.h"
#include "Form/Figure.h"
#include "Form/Cluster.h"
#include "Form/Cloud.h"
#include "Transcoding/VertexTranscoder.h"

#include "Rendering/D2014R1/Aliases.h"
#include "Rendering/D2014R1/_Renderer_v2.h"
#include "Rendering/D2014R1/_Display_v1.h"
#include "Rendering/D2014R1/_TriangleListMeshForm_v2.h"
#include "Rendering/D2014R1/_SkinnedForm_v2.h"

#endif




#if	EE_LANG_OBJC
#include "Platform/iOS/EEGraphicsDrawableView.h"
#include "Platform/OSX/EEGraphicsDrawableView.h"
#endif





#endif /* defined(__EonilGraphics__Graphics__) */
