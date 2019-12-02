//
//  ShaderMetalBridge.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "ShaderMetalBridge.hpp"
#include "ShaderMetalAdapter.hpp"

using MaterialSys::ShaderMetalBridge;

ShaderMetalBridge::ShaderMetalBridge(std::string fileName, std::string vertexFuncName, std::string pixelFuncName)
{
    raw_obj = createShaderMetal(fileName, vertexFuncName, pixelFuncName);
}
