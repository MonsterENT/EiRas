#include "ShaderResourceDX12.h"
#include <PlatformDependency/OnDX/d3dx12.h>
#include <Material/GraphicsResource.hpp>
#include <PlatformDependency/OnDX/DXMacro.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>

using namespace MaterialSys;
using GraphicsAPI::EiRasDX12;

ShaderResourceDX12::ShaderResourceDX12(GraphicsResourceBehaviors* behaviors, DXGI_FORMAT format, UINT width, UINT height, UINT channels, void* texData, bool* buildStatusFlag) : GraphicsResourceDX12(-1, behaviors)
{
    GET_EIRAS_DX12(deviceObj);

    this->texData = texData;
    TexFormat = format;

    this->width = width;
    this->height = height;
    this->channels = channels;

    tmpResource = NULL;

    outBuildStatusFlagPtr = buildStatusFlag;
    *buildStatusFlag = false;
}


ShaderResourceDX12::~ShaderResourceDX12()
{
    if (tmpResource != NULL)
    {
        tmpResource->Release();
    }
}

void ShaderResourceDX12::BuildTextureResource(void* cmdList)
{
    GET_EIRAS_DX12(deviceObj);
    const UINT64 uploadBufferSize = GetRequiredIntermediateSize(Resource, 0, 1);
    deviceObj->device->CreateCommittedResource(
        &CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
        D3D12_HEAP_FLAG_NONE,
        &CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize),
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&tmpResource));

    ID3D12GraphicsCommandList* _cmdList = (ID3D12GraphicsCommandList*)cmdList;
    
    D3D12_SUBRESOURCE_DATA textureData = {};
    textureData.pData = texData;
    textureData.RowPitch = width * channels;
    textureData.SlicePitch = textureData.RowPitch * height;
    
    _cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(Resource, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE, D3D12_RESOURCE_STATE_COPY_DEST));
    UpdateSubresources(_cmdList, Resource, tmpResource, 0, 0, 1, &textureData);
    _cmdList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(Resource, D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE));
    
    *outBuildStatusFlagPtr = true;
    buildStatusFlag = true;
}

void ShaderResourceDX12::FinishBuild()
{
#pragma message("TOFIX FinishBuild")
}

void ShaderResourceDX12::SetResource(void* res, bool noMoreUpdate)
{
    *outBuildStatusFlagPtr = false;
    this->texData = res;
    buildStatusFlag = false;
}