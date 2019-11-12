//
//  EiRasGlobalManager.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef EiRasGlobalManager_hpp
#define EiRasGlobalManager_hpp

namespace EiRasGlobal{
    
class EiRasGlobalManager
{
public:
    static EiRasGlobalManager* SharedInstance();
    void* GraphicsAPIDevice;
};

}

#endif /* EiRasGlobalManager_hpp */
