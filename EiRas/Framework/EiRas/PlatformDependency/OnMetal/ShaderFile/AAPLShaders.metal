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
//}


typedef struct
{
    float4 _TmpColor;
} PixelCBV;

typedef struct
{
    float4 _DataArray[1000];
} CommonCB1;

// Vertex shader outputs and fragment shader inputs
typedef struct
{
    // The [[position]] attribute of this member indicates that this value
    // is the clip space position of the vertex when this structure is
    // returned from the vertex function.
    float4 position [[position]];

    // Since this member does not have a special attribute, the rasterizer
    // interpolates its value with the values of the other triangle vertices
    // and then passes the interpolated value to the fragment shader for each
    // fragment in the triangle.
    float4 color;

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
//    out.color = 0;

    return out;
}

fragment float4 fragmentShader(RasterizerData in [[stage_in]],
                            constant PixelCBV& cbv[[buffer(0)]],
                               constant CommonCB1& cb1[[buffer(1)]])
{
    // Return the interpolated color.
    float4 col = cbv._TmpColor;
    col.x += cb1._DataArray[0].r;
    return col;
}

