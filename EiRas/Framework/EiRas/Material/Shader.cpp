//
//  Shader.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "Shader.hpp"

#include <Material/ShaderLayout.h>
#include <Graphics/GraphicsVertexDescriptor.hpp>

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Shader/ShaderDX12Bridge.h>
#endif

#if GRAPHICS_METAL
#include <PlatformDependency/OnMetal/Shader/ShaderMetalBridge.hpp>
#endif

using MaterialSys::Shader;
using namespace Graphics;

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

Shader::Shader(std::string fileName)
{
#if GRAPHICS_DX
    PlatformBridge = new ShaderDX12Bridge(fileName.c_str());
#endif
    Layout = 0;
}

void Shader::AddVertexFuncToPass(std::string vertexFuncName, _uint pass)
{
    ((ShaderDX12Bridge*)PlatformBridge)->AddVertexFuncToPass(vertexFuncName.c_str(), pass);
}

void Shader::AddPixelFuncToPass(std::string pixelFuncName, _uint pass)
{
    ((ShaderDX12Bridge*)PlatformBridge)->AddPixelFuncToPass(pixelFuncName.c_str(), pass);
}

void Shader::SetVertexFuncToPass(_uint index, _uint pass)
{
    ((ShaderDX12Bridge*)PlatformBridge)->SetVertexFuncToPass(index, pass);
}

void Shader::SetPixelFuncToPass(_uint index, _uint pass)
{
    ((ShaderDX12Bridge*)PlatformBridge)->SetPixelFuncToPass(index, pass);
}

void Shader::SetLayout(ShaderLayout* layout)
{
    Layout = layout;
#if GRAPHICS_DX
    ((ShaderDX12Bridge*)PlatformBridge)->SetLayout(layout);
#endif
}

void Shader::InitVertexDescriptor(GraphicsVertexDescriptor* vertexDescriptor, _uint pass)
{
#if GRAPHICS_METAL
    ((ShaderMetalBridge*)PlatformBridge)->InitVertexDescriptor(vertexDescriptor);
#endif

#if GRAPHICS_DX
    ((ShaderDX12Bridge*)PlatformBridge)->InitVertexDescriptor(vertexDescriptor, pass);
#endif
}

void* Shader::GetRawObj()
{
    return PlatformBridge->raw_obj;
}
