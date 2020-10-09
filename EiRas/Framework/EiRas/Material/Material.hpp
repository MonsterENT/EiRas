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
    class RenderTexture;
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
    class GraphicsResource;

    class Material
    {
    public:
        std::string Name;
        Material(std::string Name, Shader* shader, Graphics::CommandBuffer* commandBuffer);
        ~Material();
        Graphics::GraphicsRenderState* RenderState;

        void FinishStateChange(_uint pass = 0);
        EiRasPlatformBridgeProtocol* PlatformBridge;

        void GetPropertyData(void* res, _uint slotIndex, int propIndex = -1);
        void SetProperty(void* res, _uint slotIndex, int propIndex = -1, bool asResObj = false);
        void SetProperty(ImageSys::Image* image, _uint slotIndex, int propIndex = -1);
        void SetProperty(MaterialSys::GraphicsResource* srv, _uint slotIndex, int propIndex = -1);
        void SetProperty(Graphics::RenderTexture* rt, _uint slotIndex, int propIndex = -1);

        Shader* shader;
        MaterialLayout* materialLayout;
    private:
        Graphics::CommandBuffer* referenceCmdBuffer;
    };

};//namespace Material

#endif /* Material_hpp */
