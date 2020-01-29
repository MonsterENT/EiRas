//
//  GraphicsResourceMetalBridge.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/8/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef GraphicsResourceMetalBridge_hpp
#define GraphicsResourceMetalBridge_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Global/PlatformDefine.h>
#include <Global/GlobalDefine.h>

#include <string>

namespace MaterialSys {

    enum class GraphicsResourceType;
    class GraphicsResourceMetalBridge : public EiRasPlatformBridgeProtocol
    {
    public:
        GraphicsResourceMetalBridge(std::string name, bool initResource);
        
        void InitAsConstantBuffer(_uint bufferSize);
        
        void InitAsDefault(_uint bufferSize);
        
        void SetResource(void* res);
        
        GraphicsResourceType type;
        
        std::string name;
    private:
        bool shouldInitResource;
    };
}

#endif /* GraphicsResourceMetalBridge_hpp */
