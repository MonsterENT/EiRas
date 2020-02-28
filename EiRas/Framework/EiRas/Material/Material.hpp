//
//  Material.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <Global/GlobalDefine.h>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <string>
#include <vector>

namespace Graphics {
    class GraphicsRenderState;
    class CommandBuffer;
}

namespace ImageSys
{
    class Image;
}

namespace MaterialSys {

    class Shader;
    class MaterialLayout;
    class MaterialProp;
    class MaterialTable;

    class Material
    {
    public:
        std::string Name;
        Material(std::string Name, Shader* shader, Graphics::CommandBuffer* commandBuffer);
        ~Material();
        Graphics::GraphicsRenderState* RenderState;

        void FinishStateChange();
        EiRasPlatformBridgeProtocol* PlatformBridge;

        void SetProperty(void* res, _uint slotIndex, _uint propIndex = -1);
        void SetProperty(ImageSys::Image* image, _uint slotIndex, _uint propIndex = -1);

        Shader* shader;
        MaterialLayout* materialLayout;
    private:
        Graphics::CommandBuffer* referenceCmdBuffer;
    };

};//namespace Material

#endif /* Material_hpp */
