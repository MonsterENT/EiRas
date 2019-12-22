//
//  GraphicsPipelineInput.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/22/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef GraphicsPipelineInput_h
#define GraphicsPipelineInput_h

#include <Math/Math.hpp>
using Math::float2;
using Math::float3;
using Math::float4;

namespace Graphics {

struct VertexData2D {
    float2 Position;
    float2 UV;
};

struct VertexData2D_Color {
    float2 Position;
    float2 UV;
    float4 Color;
};

struct VertexData3D {
    float3 Position;
    float2 UV;
    float3 Normal;
};

struct VertexData3D_Color {
    float3 Position;
    float2 UV;
    float3 Normal;
    float4 Color;
};

}
#endif /* GraphicsPipelineInput_h */
