//
//  CommandBufferMetalBridge.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "CommandBufferMetalBridge.hpp"

#include "CommandBufferMetalAdapter.hpp"

using Graphics::CommandBufferMetalBridge;

CommandBufferMetalBridge::CommandBufferMetalBridge(std::string name)
{
    raw_obj = createCommandBufferMetal(name);
}
