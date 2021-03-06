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
#include <Global/GlobalDefine.h>

#include <string>
#include <vector>
#include <map>

namespace MaterialSys {
    class Material;
    class MaterialSlot;
    class MaterialProp;
    class MaterialTable;
    class GraphicsResourceHeap;
}

namespace MeshSys
{
    class Mesh;
}

namespace Graphics {

    class RenderTexture;
    class GraphicsRenderState;

    class CommandBuffer
    {
        friend MaterialSys::Material;
        typedef std::map<std::string, MaterialSys::Material*> MaterialCache_MAP;
        typedef std::pair<std::string, MaterialSys::Material*> MaterialCache_PAIR;
    public:
        std::string Name;

        CommandBuffer(std::string Name);

        void SetMaterial(MaterialSys::Material* material, _uint pass = 0);

        void DrawMesh(MeshSys::Mesh* mesh);

        void BeginFrame();

        void Reset();

        void Commit(bool present);

        void SetViewPort(float topLeftX, float topLeftY, float width, float height, float minDepth = 0, float maxDepth = 1);

        void SetRenderTexture(Graphics::RenderTexture* renderTexture);

        EiRasPlatformBridgeProtocol* PlatformBridge;

    private:

#if GRAPHICS_DX
        void _ReFillHeap();

        MaterialSys::GraphicsResourceHeap* resourceHeap;
        void RegMaterial(MaterialSys::Material* material);
        void RemoveMaterial(MaterialSys::Material* material);
        std::vector<MaterialSys::MaterialTable*> tmpMaterialTableArray;
        std::map<std::string, MaterialSys::Material*> MaterialMap;
#endif
    };

}

#endif /* CommandBuffer_hpp */
