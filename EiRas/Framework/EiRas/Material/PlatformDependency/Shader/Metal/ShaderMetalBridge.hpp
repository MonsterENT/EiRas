//
//  ShaderMetalBridge.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef ShaderMetalBridge_hpp
#define ShaderMetalBridge_hpp

#include <string>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace MaterialSys {

class ShaderMetalBridge : public EiRasPlatformBridgeProtocol
{
public:
    ShaderMetalBridge(std::string fileName, std::string vertexFuncName, std::string pixelFuncName);
};

};//namespace MaterialSys


#endif /* ShaderMetalBridge_hpp */
