#ifndef Shader_Resource_RT_Hpp
#define Shader_Resource_RT_Hpp
#include <d3d12.h>
#include <PlatformDependency/OnDX/ResourceHeapManager/ResourceDescriptorHeapManager.hpp>
#include <PlatformDependency/OnDX/Material/GraphicsResourceDescriptorHeapDX12.h>
namespace MaterialSys
{
    enum class GraphicsResourceFormat;
}

namespace MaterialSys
{
    class ShaderResourceRTDX12
    {
    public:
        ShaderResourceRTDX12(void* format, void* resource)
        {
            Format = *((MaterialSys::GraphicsResourceFormat*)format);
            Resource = (ID3D12Resource*)resource;

            GlobalHeapOffset = ResourceDescriptorHeapManager::ShareInstance()->HeapPool[0]->DynamicFillHeapGlobal(Resource, format);
        }
        MaterialSys::GraphicsResourceFormat Format;
        ID3D12Resource* Resource;
        _uint GlobalHeapOffset;
    };
}

#endif