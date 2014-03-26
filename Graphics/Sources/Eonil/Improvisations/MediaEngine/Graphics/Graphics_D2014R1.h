//
//  Graphics_D2014R1.h
//  Graphics
//
//  Created by Hoon H. on 2/27/14.
//
//

#ifndef __Graphics__Graphics_D2014R1__
#define __Graphics__Graphics_D2014R1__


















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
#include "Rendering/D2014R1/_Display_v1.h"
#include "Rendering/D2014R1/LEGACY_Renderer_v2.h"
#include "Rendering/D2014R1/LEGACY_TriangleListMeshForm_v2.h"
#include "Rendering/D2014R1/LEGACY_SkinnedForm_v2.h"

#include "Rendering/D2014R2/DisplayScreenFrame.h"
#include "Rendering/D2014R2/DebuggingInformationOverlayDrawer.h"
#include "Rendering/D2014R2/SpriteDrawer.h"

#endif




#if	EE_LANG_OBJC
#import "Platform/iOS/EEGraphicsDrawableView.h"
#import "Platform/OSX/EEGraphicsDrawableView.h"
#endif












#endif /* defined(__Graphics__Graphics_D2014R1__) */
