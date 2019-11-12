//
//  Shader.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "Shader.hpp"

#include "PlatformDependency/Metal/ShaderMetalBridge.hpp"

using MaterialSys::Shader;


Shader::Shader(std::string fileName, std::string vertexFuncName, std::string pixelFuncName)
{
    pd_ShaderObj = new ShaderMetalBridge(fileName, vertexFuncName, pixelFuncName);
}
