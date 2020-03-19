/*
See LICENSE folder for this sample’s licensing information.

Abstract:
Metal shaders used for this sample
*/

#include <metal_stdlib>
#include <simd/simd.h>

using namespace metal;

// Include header shared between this Metal shader code and C code executing Metal API commands.
typedef enum AAPLVertexInputIndex
{
    AAPLVertexInputIndexVertices     = 0,
    AAPLVertexInputIndexViewportSize = 1,
} AAPLVertexInputIndex;

//  This structure defines the layout of vertices sent to the vertex
//  shader. This header is shared between the .metal shader and C code, to guarantee that
//  the layout of the vertex array in the C code matches the layout that the .metal
//  vertex shader expects.
typedef struct
{
    float3 position [[ attribute(0) ]];
    float2 uv [[ attribute(1) ]];
    float3 normal [[ attribute(2) ]];
} AAPLVertex;

typedef struct
{
    float4 _TmpColor;
} CommonCB1;

// Vertex shader outputs and fragment shader inputs
typedef struct
{
    // The [[position]] attribute of this member indicates that this value
    // is the clip space position of the vertex when this structure is
    // returned from the vertex function.
    float4 position [[position]];
    float2 uv;
    
} RasterizerData;

vertex RasterizerData
vertexShader(uint vertexID [[vertex_id]],
             AAPLVertex vertices [[ stage_in ]],
             constant vector_uint2 *viewportSizePointer [[buffer(AAPLVertexInputIndexViewportSize)]])
{
    RasterizerData out;
    float3 pixelSpacePosition = vertices.position.xyz;
    out.position.xyz = pixelSpacePosition;
    out.position.w = 1;
    out.uv = vertices.uv;
    return out;
}

fragment float4 fragmentShader(RasterizerData in [[stage_in]],
                               constant CommonCB1& cb1[[buffer(0)]],
                               texture2d<half> colorTexture [[ texture(0) ]])
{
    constexpr sampler textureSampler (mag_filter::linear,
                                      min_filter::linear);

    // Sample the texture to obtain a color
    const half4 colorSample = colorTexture.sample(textureSampler, in.uv);

    // return the color of the texture
    return float4(colorSample) * cb1._TmpColor;
}

