//
//  EiRasGlobalManager.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef EiRasGlobalManager_hpp
#define EiRasGlobalManager_hpp

namespace MaterialSys {
    class GraphicsResource;
}

namespace EiRasGlobal {

    class EiRasGlobalManager
    {
    public:
        static EiRasGlobalManager* SharedInstance();
        void* GraphicsAPIDevice;

        EiRasGlobalManager();

        /*
         ProjectionMatrix 16 float
         View Matrix 16 float
         */
        MaterialSys::GraphicsResource* CBViewProj;

        /*
         Render Target Texture Width & Height 2 float
         */
        MaterialSys::GraphicsResource* _CB1;
    private:
    };

}

#endif /* EiRasGlobalManager_hpp */
