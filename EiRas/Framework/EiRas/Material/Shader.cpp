//
//  Shader.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "Shader.hpp"

#include <Material/ShaderLayout.h>

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Shader/ShaderDX12Bridge.h>
#endif

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/Shader/ShaderMetalBridge.hpp>
#endif

using MaterialSys::Shader;

#if GRAPHICS_DX
using MaterialSys::ShaderLayout;
#endif

Shader::Shader(std::string fileName, std::string vertexFuncName, std::string pixelFuncName)
{
#if GRAPHICS_METAL
    PlatformBridge = new ShaderMetalBridge(fileName, vertexFuncName, pixelFuncName);
#endif

#if GRAPHICS_DX
    PlatformBridge = new ShaderDX12Bridge(fileName.c_str(), vertexFuncName.c_str(), pixelFuncName.c_str());
#endif
    Layout = 0;
}

void Shader::InitLayout(ShaderLayout* layout)
{
    Layout = layout;
#if GRAPHICS_DX
    ((ShaderDX12Bridge*)PlatformBridge)->InitRootSignature(layout);
#endif
}

void* Shader::GetRawObj()
{
    return PlatformBridge->raw_obj;
}