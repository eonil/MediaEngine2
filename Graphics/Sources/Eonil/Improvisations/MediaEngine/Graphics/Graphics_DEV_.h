//
//  Graphics_DEV_.h
//  EonilGraphics
//
//  Created by Hoon H. on 2/5/14.
//
//

#ifndef __EonilGraphics__Graphics_DEV___
#define __EonilGraphics__Graphics_DEV___






/*
 A header file for feature development.
 Will not be available in final release.
 */







#if	__cplusplus


#include "Graphics.h"

////

#include "Stub/GL.h"

#include "Server/Symbols.h"
#include "Server/Framebuffer.h"
#include "Server/Buffer.h"
#include "Server/Texture.h"
#include "Server/Shader.h"
#include "Server/Program.h"

#include "Server/Machine.h"
#include "Server/Machinery/VertexAttributeChannel.h"
#include "Server/Machinery/IndexUnitChannel.h"
#include "Server/Machinery/TextureSampler.h"

//#include "Platform/D2014R1/_TextTextureGenerator.h"
#include "Aliens/TextTextureGeneratorV2.h"



#include "Transcoding/_PackA.h"
#include "Transcoding/_PackNodeA.h"
#include "Transcoding/_PackSerializerA.h"
#include "Transcoding/_ModelProxyEditorBoxA.h"
#include "Transcoding/_ModelExporterA.h"

#endif


#endif /* defined(__EonilGraphics__Graphics_DEV___) */
