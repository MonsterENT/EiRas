//
//  CommandBufferMetalBridge.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef CommandBufferMetalBridge_hpp
#define CommandBufferMetalBridge_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

#include <string>

namespace MaterialSys {
class Material;
}

namespace Graphics {

class CommandBufferMetalBridge : public EiRasPlatformBridgeProtocol
{
public:
    CommandBufferMetalBridge(std::string name);
    
    void SetMaterial(MaterialSys::Material* material);
    
    void DrawMesh(void* meshData, int dataSize, int index);
    
    void BeginFrame();
    
    void Present();

    void Commit();

};

}

#endif /* CommandBufferMetalBridge_hpp */
