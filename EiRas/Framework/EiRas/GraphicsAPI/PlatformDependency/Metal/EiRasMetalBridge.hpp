//
//  EiRasMetalBridge.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/11/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef EiRasMetalBridge_hpp
#define EiRasMetalBridge_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace GraphicsAPI {

class EiRasMetalBridge : public EiRasPlatformBridgeProtocol
{
public:
    EiRasMetalBridge();
    void InitDevice();
    void OnUpdate();
private:
};

}
#endif /* EiRasMetalBridge_hpp */
