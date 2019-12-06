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
#include <vector>

namespace Graphics {
    class GraphicsRenderState;
}

namespace MaterialSys {

    class Shader;
    class MaterialLayout;
    class MaterialProp;
    class MaterialTable;

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
        MaterialLayout* materialLayout;
        std::vector<MaterialProp*> Props;
        std::vector<MaterialProp*> LayoutProps;
        std::vector<MaterialTable*> LayoutTables;
    };

};//namespace Material

#endif /* Material_hpp */
