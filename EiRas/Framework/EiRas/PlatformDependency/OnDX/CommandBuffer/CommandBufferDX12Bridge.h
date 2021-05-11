#pragma once
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Global/GlobalDefine.h>
#include <string>
#include <Math/Math.hpp>

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

namespace GPCompute
{
    class ComputeKernel;
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
        void DispatchComputeKernel(GPCompute::ComputeKernel* kernel, Math::int3 groupCount);
        void BeginFrame();

        void Reset();

        void Commit(bool present);

        void SetViewPort(float topLeftX, float topLeftY, float width, float height, float minDepth, float maxDepth);
        
        void SetRenderTexture(EiRasPlatformBridgeProtocol* renderTexturePB);
    };
}