#pragma once

#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>
#include <PlatformDependency/OnDX/Shader/ShaderResource/ShaderResourceDX12.h>

namespace MaterialSys
{
    class ResourceDX12;
}
class ShaderResourceHeapDX12
{
public:
    ID3D12DescriptorHeap* heap = 0;
    ShaderResourceHeapDX12(UINT resCount, MaterialSys::ResourceDX12** resArray, UINT initCount = -1);
    ~ShaderResourceHeapDX12();
};

