//
//  Shader.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "Shader.hpp"

#if GRAPHICS_DX
#include "PlatformDependency/Shader/DX12/ShaderDX12Bridge.h"
#endif

#if GRAPHICS_METAL
#include "PlatformDependency/Shader/Metal/ShaderMetalBridge.hpp"
#endif

using MaterialSys::Shader;


Shader::Shader(std::string fileName, std::string vertexFuncName, std::string pixelFuncName)
{
    PlatformBridge = new ShaderMetalBridge(fileName, vertexFuncName, pixelFuncName);
}

void* Shader::GetRawObj()
{
    return PlatformBridge->raw_obj;
}
