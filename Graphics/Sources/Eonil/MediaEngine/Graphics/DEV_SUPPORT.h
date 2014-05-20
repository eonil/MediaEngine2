//
//  DEV_SUPPORT.h
//  Graphics
//
//  Created by Hoon H. on 14/5/19.
//
//

#pragma once






/*
 A header file for feature development.
 Will not be available in final release.
 */







#if	__cplusplus

////

#include "Stub/GL.h"

#include "Server/Symbols.h"
#include "Server/Framebuffer.h"
#include "Server/Buffer.h"
#include "Server/Texture.h"
#include "Server/Shader.h"
#include "Server/Program.h"

#include "Server/Machine.h"
#include "Server/Machinery/MachineVirtualSubdeviceChannelList.h"
#include "Server/Machinery/VertexAttributeChannel.h"
#include "Server/Machinery/IndexUnitChannel.h"
#include "Server/Machinery/TextureSampler.h"

//#include "Platform/D2014R1/_TextTextureGenerator.h"
#include "Aliens/TextTextureGeneratorV2.h"



#include "Transcoding/LEGACY_PackA.h"
#include "Transcoding/LEGACY_PackNodeA.h"
#include "Transcoding/LEGACY_PackSerializerA.h"
#include "Transcoding/LEGACY_ModelProxyEditorBoxA.h"
#include "Transcoding/LEGACY_ModelExporterA.h"

#endif

