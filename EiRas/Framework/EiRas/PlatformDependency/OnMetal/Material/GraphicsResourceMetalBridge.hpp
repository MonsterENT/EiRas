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

namespace MaterialSys {

    enum class GraphicsResourceType;
    class GraphicsResourceMetalBridge : public EiRasPlatformBridgeProtocol
    {
    public:
        GraphicsResourceMetalBridge(bool initResource);
        
        void InitAsConstantBuffer(UINT bufferSize);
        
        void InitAsDefault(UINT bufferSize);
        
        void SetResource(void* res, bool shouldUnmap);
        
        GraphicsResourceType type;
    private:
        bool shouldInitResource;
    };
}

#endif /* GraphicsResourceMetalBridge_hpp */
