//
//  Shader.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "Shader.hpp"

#include "PlatformDependency/Shader/Metal/ShaderMetalBridge.hpp"

using MaterialSys::Shader;


Shader::Shader(std::string fileName, std::string vertexFuncName, std::string pixelFuncName)
{
    PlatformBridge = new ShaderMetalBridge(fileName, vertexFuncName, pixelFuncName);
}

void* Shader::GetRawObj()
{
    return PlatformBridge->raw_obj;
}
