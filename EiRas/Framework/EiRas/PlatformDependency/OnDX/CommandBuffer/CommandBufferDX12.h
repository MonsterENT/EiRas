#pragma once
#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>
#include <string>
#include <vector>
#include <Global/GlobalDefine.h>
#include <PlatformDependency/OnDX/RenderTexture/RenderTextureDX12.hpp>

namespace MaterialSys
{
    class GraphicsResourceHeapDX12;
    class MaterialDX12;
    class MaterialLayout;
    class GraphicsResourceDX12;
}

namespace MeshSys
{
    class Mesh;
}

namespace Graphics {
    
    class CommandBufferDX12
    {
    public:
        CommandBufferDX12(std::string Name);
        ~CommandBufferDX12();

        void BeginFrame();

        void Reset(MaterialSys::GraphicsResourceHeapDX12* heapObj);
        void Commit(bool present);

        void SetViewPort(float topLeftX, float topLeftY, float width, float height, float minDepth, float maxDepth);

        void DrawMesh(MeshSys::Mesh* mesh);

        void SetMaterial(MaterialSys::MaterialDX12* mat, MaterialSys::MaterialLayout* layout, _uint pass = 0);

        void SetRenderTexture(void* rawRenderTexture);

        ID3D12CommandAllocator* cmdAllocator = 0;
        ID3D12GraphicsCommandList* cmdList = 0;
        MaterialSys::GraphicsResourceHeapDX12* CurrentUseingHeap;

        void GetCurrentRenderTextureInfo(_uint* numRT, DXGI_FORMAT* rtFormats, DXGI_FORMAT* depthFormat);
    private:
        RenderTextureDX12* _CurrentRenderTexture;
    };
}
