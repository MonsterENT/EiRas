//
//  ShaderMetalAdapter.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef ShaderMetalAdapter_hpp
#define ShaderMetalAdapter_hpp

#include <string>
using std::string;

namespace MaterialSys
{
    void* createShaderMetal(std::string fileName, std::string vertexFuncName, std::string pixelFuncName);
}

#endif /* ShaderMetalAdapter_hpp */
