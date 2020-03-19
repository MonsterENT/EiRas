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
#include <Global/GlobalDefine.h>

namespace MaterialSys {
    class MaterialTable;

    class GraphicsResourceHeapMetalBridge : public EiRasPlatformBridgeProtocol
    {
    public:
        GraphicsResourceHeapMetalBridge(_uint propCount);
    };
}

#endif /* GraphicsResourceHeapMetalBridge_hpp */
