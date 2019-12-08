//
//  GraphicsResourceHeapMetalBridge.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/8/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef GraphicsResourceHeapMetalBridge_hpp
#define GraphicsResourceHeapMetalBridge_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace MaterialSys {
    class GraphicsResource;

    class GraphicsResourceHeapMetalBridge : public EiRasPlatformBridgeProtocol
    {
    public:
        GraphicsResourceHeapMetalBridge(int resCount, GraphicsResource** resArray);
    };
}

#endif /* GraphicsResourceHeapMetalBridge_hpp */
