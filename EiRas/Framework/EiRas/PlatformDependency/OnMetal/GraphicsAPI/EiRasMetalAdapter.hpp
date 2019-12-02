//
//  EiRasMetalAdapter.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/11/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef EiRasMetalAdapter_hpp
#define EiRasMetalAdapter_hpp

namespace GraphicsAPI {

void* createMetal();

void initMetalDevice(void* ptr);

void OnUpdateMetal(void* ptr);

}
#endif /* EiRasMetalAdapter_hpp */
