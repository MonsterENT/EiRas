#include "ShaderResourceDX12.h"
#include <PlatformDependency/OnDX/DXMacro.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>

using MaterialSys::ShaderResourceDX12;
using GraphicsAPI::EiRasDX12;

ShaderResourceDX12::ShaderResourceDX12(DXGI_FORMAT format, UINT width, UINT height, UINT8* texData)
{
    GET_EIRAS_DX12(deviceObj)

    this->texData = texData;
        //new UINT8[width * height];
    //memcpy(this->texData, texData, width * height);
    ResType = ResourceTypeDX12::TypeSRV;
    textureFormat = format;
    this->width = width;
    this->height = height;

    D3D12_RESOURCE_DESC textureDesc = {};
    textureDesc.MipLevels = 1;
    textureDesc.Format = format;
    textureDesc.Width = width;
    textureDesc.Height = height;
    textureDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
    textureDesc.DepthOrArraySize = 1;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    
    deviceObj->device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
        D3D12_HEAP_FLAG_NONE,
        &textureDesc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&Resource));

    const UINT64 uploadBufferSize = GetRequiredIntermediateSize(Resource, 0, 1);

    deviceObj->device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize),
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&tmpResource));
}


ShaderResourceDX12::~ShaderResourceDX12()
{
}


void ShaderResourceDX12::invoke(void* data)
{
    ID3D12GraphicsCommandList* cmdList = (ID3D12GraphicsCommandList*)data;
    
    D3D12_SUBRESOURCE_DATA textureData = {};
    textureData.pData = &texData[0];
    textureData.RowPitch = width * 4;
    textureData.SlicePitch = textureData.RowPitch * height;
    
    UpdateSubresources(cmdList, Resource, tmpResource, 0, 0, 1, &textureData);
    cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(Resource, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
}