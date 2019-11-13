//
//  Shader.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace MaterialSys {

class Shader
{
public:
    Shader(std::string fileName, std::string vertexFuncName, std::string pixelFuncName);
    
    void* GetRawObj();
    
private:
    EiRasPlatformBridgeProtocol* PlatformBridge;
};

};//namespace Material


#endif /* Shader_hpp */
