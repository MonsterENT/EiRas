//
//  CommandBuffer.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef CommandBuffer_hpp
#define CommandBuffer_hpp

#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <string>
#include <vector>
#include <map>

namespace MaterialSys {
    class Material;
    class MaterialTable;
    class GraphicsResourceHeap;
}

namespace MeshSys {
    class Mesh;
}

namespace Graphics {

    class GraphicsRenderSate;

    class CommandBuffer
    {
        friend MaterialSys::Material;
        typedef std::map<std::string, MaterialSys::Material*> MaterialCache_MAP;
        typedef std::pair<std::string, MaterialSys::Material*> MaterialCache_PAIR;
    public:
        std::string Name;

        CommandBuffer(std::string Name);

        void SetMaterial(MaterialSys::Material* material);

        void DrawMesh(MeshSys::Mesh* mesh);

        void BeginFrame();

        void Present();

        void Commit();

        EiRasPlatformBridgeProtocol* PlatformBridge;

    private:
        MaterialSys::GraphicsResourceHeap* resourceHeap;
        void RegMaterial(MaterialSys::Material* material);
        void RemoveMaterial(MaterialSys::Material* material);
        std::vector<MaterialSys::MaterialTable*> tmpMaterialTableArray;
        std::map<std::string, MaterialSys::Material*> MaterialMap;
    };

}

#endif /* CommandBuffer_hpp */
