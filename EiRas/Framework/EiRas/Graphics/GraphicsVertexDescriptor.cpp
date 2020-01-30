//
//  GraphicsVertexBufferDescriptor.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/16/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#include "GraphicsVertexDescriptor.hpp"

#if GRAPHICS_DX
#include <dxgiformat.h>
#endif

using namespace Graphics;

//VertexFormatFloat = 28,
//VertexFormatFloat2 = 29,
//VertexFormatFloat3 = 30,
//VertexFormatFloat4 = 31,
//
//VertexFormatInt = 32,
//VertexFormatInt2 = 33,
//VertexFormatInt3 = 34,
//VertexFormatInt4 = 35,
//
//VertexFormatUInt = 36,
//VertexFormatUInt2 = 37,
//VertexFormatUInt3 = 38,
//VertexFormatUInt4 = 39,

_uint Graphics::GraphicsVertexAttributeFormatSize(GraphicsVertexAttributeFormat format)
{
    switch (format) {
        case GraphicsVertexAttributeFormat::VertexFormatFloat:
            return sizeof(float);
            break;
        case GraphicsVertexAttributeFormat::VertexFormatFloat2:
            return sizeof(float) * 2;
            break;
        case GraphicsVertexAttributeFormat::VertexFormatFloat3:
            return sizeof(float) * 3;
            break;
        case GraphicsVertexAttributeFormat::VertexFormatFloat4:
            return sizeof(float) * 4;
            break;
            
        case GraphicsVertexAttributeFormat::VertexFormatInt:
            return sizeof(int);
            break;
        case GraphicsVertexAttributeFormat::VertexFormatInt2:
            return sizeof(int) * 2;
            break;
        case GraphicsVertexAttributeFormat::VertexFormatInt3:
            return sizeof(int) * 3;
            break;
        case GraphicsVertexAttributeFormat::VertexFormatInt4:
            return sizeof(int) * 4;
            break;
            
        case GraphicsVertexAttributeFormat::VertexFormatUInt:
            return sizeof(_uint);
            break;
        case GraphicsVertexAttributeFormat::VertexFormatUInt2:
            return sizeof(_uint) * 2;
            break;
        case GraphicsVertexAttributeFormat::VertexFormatUInt3:
            return sizeof(_uint) * 3;
            break;
        case GraphicsVertexAttributeFormat::VertexFormatUInt4:
            return sizeof(_uint) * 4;
            break;
        default:
            break;
    }

    return 0;
}

_uint Graphics::GraphicsVertexAttributeToDX12Format(GraphicsVertexAttributeFormat format)
{
#if GRAPHICS_DX
    switch (format)
    {
    case Graphics::GraphicsVertexAttributeFormat::VertexFormatFloat:
        return DXGI_FORMAT_R32_FLOAT;
        break;
    case Graphics::GraphicsVertexAttributeFormat::VertexFormatFloat2:
        return DXGI_FORMAT_R32G32_FLOAT;
        break;
    case Graphics::GraphicsVertexAttributeFormat::VertexFormatFloat3:
        return DXGI_FORMAT_R32G32B32_FLOAT;
        break;
    case Graphics::GraphicsVertexAttributeFormat::VertexFormatFloat4:
        return DXGI_FORMAT_R32G32B32A32_FLOAT;
        break;
    case Graphics::GraphicsVertexAttributeFormat::VertexFormatInt:
        return DXGI_FORMAT_R32_SINT;
        break;
    case Graphics::GraphicsVertexAttributeFormat::VertexFormatInt2:
        return DXGI_FORMAT_R32G32_SINT;
        break;
    case Graphics::GraphicsVertexAttributeFormat::VertexFormatInt3:
        return DXGI_FORMAT_R32G32B32_SINT;
        break;
    case Graphics::GraphicsVertexAttributeFormat::VertexFormatInt4:
        return DXGI_FORMAT_R32G32B32A32_SINT;
        break;
    case Graphics::GraphicsVertexAttributeFormat::VertexFormatUInt:
        return DXGI_FORMAT_R32_UINT;
        break;
    case Graphics::GraphicsVertexAttributeFormat::VertexFormatUInt2:
        return DXGI_FORMAT_R32G32_UINT;
        break;
    case Graphics::GraphicsVertexAttributeFormat::VertexFormatUInt3:
        return DXGI_FORMAT_R32G32B32_UINT;
        break;
    case Graphics::GraphicsVertexAttributeFormat::VertexFormatUInt4:
        return DXGI_FORMAT_R32G32B32A32_UINT;
        break;
    default:
        break;
    }
    
    return DXGI_FORMAT_UNKNOWN;
#endif
    return 0;
}
