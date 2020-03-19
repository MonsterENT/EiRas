//
//  GraphicsResourceMetalAdapter.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/8/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef GraphicsResourceMetalAdapter_hpp
#define GraphicsResourceMetalAdapter_hpp

#include <Global/GlobalDefine.h>
#include <string>

namespace MaterialSys {

void* createConstantBufferMetal(std::string name, int bufferSize, bool initResource);

void* createShaderResourceTexture(std::string name, _uint width, _uint height, void* texData, bool* buildStatusFlag);

void* createDefaultBufferMetal(std::string name, int bufferSize, bool initResource);

void setResourceMetal(void* ptr, void* res);
}

#endif /* GraphicsResourceMetalAdapter_hpp */
