 //
//  EiRasGlobalManager.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef EiRasGlobalManager_hpp
#define EiRasGlobalManager_hpp

#include <vector>
#include <Math/Math.hpp>

namespace MaterialSys {
    class Material;
    class GraphicsResource;
    class GraphicsResourceDescriptorHeap;
}

namespace EiRasGlobal {

    struct CommonCB0
    {
        Math::Matrix4X4 WorldToViewMatrix;
        Math::Matrix4X4 ProjectionMatrix;
    };

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
        MaterialSys::GraphicsResource* CBViewProjRawRes;

        void SetViewProj(const Math::Matrix4X4 WorldToViewMatrix, const Math::Matrix4X4 ProjectionMatrix);

        /*
         Render Target Texture Width & Height 2 float
         */
        MaterialSys::GraphicsResource* _CB1;

    private:
        MaterialSys::GraphicsResource* GetViewProjRawRes();
        CommonCB0 _CBViewProj;
    };

}

#endif /* EiRasGlobalManager_hpp */
