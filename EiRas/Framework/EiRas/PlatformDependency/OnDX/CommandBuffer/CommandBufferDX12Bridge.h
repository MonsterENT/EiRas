#pragma once
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <string>

namespace MaterialSys
{
    class Material;
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
    };
}