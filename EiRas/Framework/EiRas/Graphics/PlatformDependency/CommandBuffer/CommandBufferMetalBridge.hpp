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

namespace Graphics {

class CommandBufferMetalBridge : public EiRasPlatformBridgeProtocol
{
public:
    CommandBufferMetalBridge(std::string name);
};

}

#endif /* CommandBufferMetalBridge_hpp */
