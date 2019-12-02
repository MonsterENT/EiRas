//
//  Material.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <string>

namespace Graphics {
    class GraphicsRenderState;
}

namespace MaterialSys {

    class Shader;
    enum class MaterialSlotType
    {
        Prop = 0,
        Table = 1
    };

    enum class MaterialPropType
    {
        CBV = 0,
        SRV = 1
    };

    class MaterialSlot
    {
    public:
        int SlotID;
        MaterialSlotType SlotType;
    };

    class MaterialProp : public MaterialSlot
    {
    public:
        MaterialPropType PropType;
    };

    class MaterialTable : public MaterialSlot
    {
    public:
        int PropNum;
        MaterialProp** Props;
    };

    class Material
    {
    public:
        Material(std::string name, Shader* shader);
        Graphics::GraphicsRenderState* RenderState;

        void FinishStateChange();
        EiRasPlatformBridgeProtocol* PlatformBridge;

        void SetProperty(int propertyId, void* res);

    private:
        Shader* shader;

    };

};//namespace Material

#endif /* Material_hpp */
