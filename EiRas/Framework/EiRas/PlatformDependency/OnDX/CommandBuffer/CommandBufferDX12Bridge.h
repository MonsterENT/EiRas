#pragma once
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Global/GlobalDefine.h>
#include <string>

namespace MaterialSys
{
    class Material;
    class MaterialProp;
    class GraphicsResource;
}

namespace MeshSys
{
    class Mesh;
}

namespace Graphics {
    class RenderData;

    class CommandBufferDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        CommandBufferDX12Bridge(std::string Name);

        void SetMaterial(MaterialSys::Material* mat, _uint pass = 0);

        void SetTransformGraphics(MaterialSys::GraphicsResource* res);
        void DrawMesh(MeshSys::Mesh* mesh);
        void DrawRenderData(RenderData* render);

        void BeginFrame();

        void Reset(EiRasPlatformBridgeProtocol* heapBridge);

        void Commit(bool present);

        void SetViewPort(float topLeftX, float topLeftY, float width, float height, float minDepth, float maxDepth);
        
        void SetRenderTexture(EiRasPlatformBridgeProtocol* renderTexturePB);
    };
}