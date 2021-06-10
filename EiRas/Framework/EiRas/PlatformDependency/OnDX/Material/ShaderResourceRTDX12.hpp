#ifndef Shader_Resource_RT_Hpp
#define Shader_Resource_RT_Hpp
#include <d3d12.h>
#include <PlatformDependency/OnDX/ResourceHeapManager/ResourceDescriptorHeapManager.hpp>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDescriptorHeapDX12.h>
#include <PlatformDependency/OnDX/RenderTexture/RenderTextureDX12.hpp>

namespace MaterialSys
{
    enum class GraphicsResourceFormat;
}

using namespace Graphics;

namespace MaterialSys
{
    class ShaderResourceRTDX12
    {
    public:
        ShaderResourceRTDX12(void* rtRawObj)
        {
            RTRawObj = (RenderTextureDX12*)rtRawObj;
            ColorBufferGlobalHeapOffset = ResourceDescriptorHeapManager::ShareInstance()->HeapPool[0]->DynamicFillHeapGlobal(RTRawObj->ColorBuffer, &RTRawObj->ColorFormat);
            DepthStencilBufferGlobalHeapOffset = ResourceDescriptorHeapManager::ShareInstance()->HeapPool[0]->DynamicFillHeapGlobal(RTRawObj->DepthStencilBuffer, &RTRawObj->DepthStencilFormat, true);
        }

        RenderTextureDX12* RTRawObj;
        _uint ColorBufferGlobalHeapOffset;
        _uint DepthStencilBufferGlobalHeapOffset;
    };
}

#endif