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
    class RenderData;

    class CommandBuffer
    {
        friend MaterialSys::Material;
    public:
        std::string Name;

        CommandBuffer(std::string Name);

        void SetMaterial(MaterialSys::Material* material, _uint pass = 0);

        void DrawMesh(MeshSys::Mesh* mesh);
        void DrawRenderData(RenderData* render);

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
        std::vector<MaterialSys::Material*> MaterialArray;
#endif
    };

}

#endif /* CommandBuffer_hpp */
