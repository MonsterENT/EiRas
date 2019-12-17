//
//  MeshMetalBridge.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/15/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef MeshMetalBridge_hpp
#define MeshMetalBridge_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Global/GlobalDefine.h>

namespace MeshSys {

class MeshMetalBridge : public EiRasPlatformBridgeProtocol
{
public:
    MeshMetalBridge();
    
    void BuildBuffer(EiRasPlatformBridgeProtocol* vertexResBridge, EiRasPlatformBridgeProtocol* indexResBridge, _uint vertexCount, _uint indexCount, _uint vertexBufferIndex, _uint indexBufferIndex);
};

}

#endif /* MeshMetalBridge_hpp */
