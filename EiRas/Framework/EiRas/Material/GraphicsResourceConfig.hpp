#ifndef Graphics_Resource_Config_Hpp
#define Graphics_Resource_Config_Hpp

namespace MaterialSys
{
    typedef enum class GraphicsResourceType
    {
        SRV = 0,
        UAV = (SRV + 1),
        CBV = (UAV + 1),
        SAMPLER = (CBV + 1),
        Default = (SAMPLER + 1),
        SRV_RT = (Default + 1)
    } GraphicsResourceType;

    enum class GraphicsResourceDimension
    {
        GraphicsResourceDimension_Buffer = 0,
        GraphicsResourceDimension_Tex1D = 1,
        GraphicsResourceDimension_Tex2D = 2,
        GraphicsResourceDimension_Tex3D = 3,
    };

    typedef enum class GraphicsResourceVisibility
    {
        VISIBILITY_ALL = 0,
        VISIBILITY_VERTEX = (VISIBILITY_ALL + 1),
        VISIBILITY_PIXEL = (VISIBILITY_VERTEX + 1),
    } GraphicsResourceVisibility;

    //D3D12_SHADER_VISIBILITY_ALL = 0,
    //    D3D12_SHADER_VISIBILITY_VERTEX = 1,
    //    D3D12_SHADER_VISIBILITY_HULL = 2,
    //    D3D12_SHADER_VISIBILITY_DOMAIN = 3,
    //    D3D12_SHADER_VISIBILITY_GEOMETRY = 4,
    //    D3D12_SHADER_VISIBILITY_PIXEL = 5

    inline int GraphicsResourceVisibilityToDX12(GraphicsResourceVisibility visibility)
    {
        switch (visibility)
        {
        case GraphicsResourceVisibility::VISIBILITY_ALL:
            return 0;
            break;
        case GraphicsResourceVisibility::VISIBILITY_VERTEX:
            return 1;
            break;
        case GraphicsResourceVisibility::VISIBILITY_PIXEL:
            return 5;
            break;
        default:
            return 0;
            break;
        }
    }

    enum class GraphicsResourceFormat
    {
        UNKNOWN = 0,
        R32G32B32A32_TYPELESS = 1,
        R32G32B32A32_FLOAT = 2,
        R32G32B32A32_UINT = 3,
        R32G32B32A32_SINT = 4,
        R32G32B32_TYPELESS = 5,
        R32G32B32_FLOAT = 6,
        R32G32B32_UINT = 7,
        R32G32B32_SINT = 8,
        R16G16B16A16_TYPELESS = 9,
        R16G16B16A16_FLOAT = 10,
        R16G16B16A16_UNORM = 11,
        R16G16B16A16_UINT = 12,
        R16G16B16A16_SNORM = 13,
        R16G16B16A16_SINT = 14,
        R32G32_TYPELESS = 15,
        R32G32_FLOAT = 16,
        R32G32_UINT = 17,
        R32G32_SINT = 18,
        R32G8X24_TYPELESS = 19,
        D32_FLOAT_S8X24_UINT = 20,
        R32_FLOAT_X8X24_TYPELESS = 21,
        X32_TYPELESS_G8X24_UINT = 22,
        R10G10B10A2_TYPELESS = 23,
        R10G10B10A2_UNORM = 24,
        R10G10B10A2_UINT = 25,
        R11G11B10_FLOAT = 26,
        R8G8B8A8_TYPELESS = 27,
        R8G8B8A8_UNORM = 28,
        R8G8B8A8_UNORM_SRGB = 29,
        R8G8B8A8_UINT = 30,
        R8G8B8A8_SNORM = 31,
        R8G8B8A8_SINT = 32,
        R16G16_TYPELESS = 33,
        R16G16_FLOAT = 34,
        R16G16_UNORM = 35,
        R16G16_UINT = 36,
        R16G16_SNORM = 37,
        R16G16_SINT = 38,
        R32_TYPELESS = 39,
        D32_FLOAT = 40,
        R32_FLOAT = 41,
        R32_UINT = 42,
        R32_SINT = 43,
        R24G8_TYPELESS = 44,
        D24_UNORM_S8_UINT = 45,
        R24_UNORM_X8_TYPELESS = 46,
        X24_TYPELESS_G8_UINT = 47,
        R8G8_TYPELESS = 48,
        R8G8_UNORM = 49,
        R8G8_UINT = 50,
        R8G8_SNORM = 51,
        R8G8_SINT = 52,
        R16_TYPELESS = 53,
        R16_FLOAT = 54,
        D16_UNORM = 55,
        R16_UNORM = 56,
        R16_UINT = 57,
        R16_SNORM = 58,
        R16_SINT = 59,
        R8_TYPELESS = 60,
        R8_UNORM = 61,
        R8_UINT = 62,
        R8_SNORM = 63,
        R8_SINT = 64,
        A8_UNORM = 65,
        R1_UNORM = 66,
        R9G9B9E5_SHAREDEXP = 67,
        R8G8_B8G8_UNORM = 68,
        G8R8_G8B8_UNORM = 69,
        BC1_TYPELESS = 70,
        BC1_UNORM = 71,
        BC1_UNORM_SRGB = 72,
        BC2_TYPELESS = 73,
        BC2_UNORM = 74,
        BC2_UNORM_SRGB = 75,
        BC3_TYPELESS = 76,
        BC3_UNORM = 77,
        BC3_UNORM_SRGB = 78,
        BC4_TYPELESS = 79,
        BC4_UNORM = 80,
        BC4_SNORM = 81,
        BC5_TYPELESS = 82,
        BC5_UNORM = 83,
        BC5_SNORM = 84,
    };

    typedef enum class GraphicsResourceUpdateFreq
    {
        UPDATE_FREQ_ONINIT = 0,
        UPDATE_FREQ_LOW = (UPDATE_FREQ_ONINIT + 1),
        UPDATE_FREQ_HIGH = (UPDATE_FREQ_LOW + 1),
    } GraphicsResourceUpdateFreq;

    typedef struct GraphicsResourceBehaviors
    {
        GraphicsResourceType ResourceType;
        GraphicsResourceVisibility Visibility;
        GraphicsResourceUpdateFreq UpdateFreq;
    } GraphicsResourceBehaviors;
}
#endif
