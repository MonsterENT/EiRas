#pragma once
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <string>

namespace MaterialSys
{
    class Material;
    class MaterialProp;
}

namespace MeshSys
{
    class Mesh;
}

namespace Graphics {
    class CommandBufferDX12Bridge : public EiRasPlatformBridgeProtocol
    {
    public:
        CommandBufferDX12Bridge(std::string Name);

        void SetMaterial(MaterialSys::Material* mat);

        void DrawMesh(MeshSys::Mesh* mesh);

        void BeginFrame();

        void Reset(EiRasPlatformBridgeProtocol* heapBridge);

        void Commit(bool present);

        void SetViewPort(float topLeftX, float topLeftY, float width, float height, float minDepth, float maxDepth);
    };
}