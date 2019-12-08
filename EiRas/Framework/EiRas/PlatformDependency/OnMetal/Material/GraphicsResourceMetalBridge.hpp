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

namespace MaterialSys {

    enum class GraphicsResourceType;
    class GraphicsResourceMetalBridge : public EiRasPlatformBridgeProtocol
    {
    public:
        GraphicsResourceMetalBridge(GraphicsResourceType type, int bufferSize = 0);
    };
}

#endif /* GraphicsResourceMetalBridge_hpp */
