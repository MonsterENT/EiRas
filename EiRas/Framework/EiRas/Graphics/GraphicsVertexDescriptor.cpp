//
//  GraphicsVertexBufferDescriptor.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/16/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#include "GraphicsVertexDescriptor.hpp"
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
