//
//  GraphicsRenderState.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/11/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef GraphicsRenderState_hpp
#define GraphicsRenderState_hpp

#include <Global/GlobalDefine.h>

namespace Graphics
{
typedef enum class FillMode
{
    FillMode_WireFrame = 2,
    FillMode_SOLID = 3,
} FillMode;

typedef enum class CullMode
{
    CullModeBack = 1,
    CullModeFront = 2,
    CullModeNone = 3
} CullMode;

typedef enum class BlendOp
{
    BlendOpAdd = 1,
    BlendOpSubtract = 2,
    BlendOpRevSubtract = 3,
    BlendOpMin = 4,
    BlendOpMax = 5
} BlendOp;

typedef enum class BlendFactor
{
    BlendRGBFactorZero = 1,
    BlendRGBFactorOne = 2,
    BlendRGBFactorSourceColor = 3,
    BlendRGBFactorOneMinusSourceColor = 4,
    BlendRGBFactorSourceAlpha = 5,
    BlendRGBFactorOneMinusSourceAlpha = 6,
    BlendRGBFactorDestinationColor = 7,
    BlendRGBFactorOneMinusDestinationColor = 8,
    BlendRGBFactorDestinationAlpha = 9,
    BlendRGBFactorOneMinusDestinationAlpha = 10,
    BlendRGBFactorSourceAlphaSaturated = 11,
    BlendRGBFactorBlendColor = 12,
    BlendRGBFactorOneMinusBlendColor = 13,
    BlendRGBFactorBlendAlpha = 14,
    BlendRGBFactorOneMinusBlendAlpha = 15,
//    BlendRGBFactorSource1Color              API_AVAILABLE(macos(10.12), ios(10.11)) = 15,
//    BlendRGBFactorOneMinusSource1Color      API_AVAILABLE(macos(10.12), ios(10.11)) = 16,
//    BlendRGBFactorSource1Alpha              API_AVAILABLE(macos(10.12), ios(10.11)) = 17,
//    BlendRGBFactorOneMinusSource1Alpha      API_AVAILABLE(macos(10.12), ios(10.11)) = 18,
} BlendFactor;

#ifdef GRAPHICS_DX
inline _uint BlendFactorConvertDX12(BlendFactor factor)
{
    switch (factor)
    {
    case Graphics::BlendFactor::BlendRGBFactorZero:
        return 1;
        break;
    case Graphics::BlendFactor::BlendRGBFactorOne:
        return 2;
        break;
    case Graphics::BlendFactor::BlendRGBFactorSourceColor:
        return 3;
        break;
    case Graphics::BlendFactor::BlendRGBFactorOneMinusSourceColor:
        return 4;
        break;
    case Graphics::BlendFactor::BlendRGBFactorSourceAlpha:
        return 5;
        break;
    case Graphics::BlendFactor::BlendRGBFactorOneMinusSourceAlpha:
        return 6;
        break;
    case Graphics::BlendFactor::BlendRGBFactorDestinationColor:
        return 9;
        break;
    case Graphics::BlendFactor::BlendRGBFactorOneMinusDestinationColor:
        return 10;
        break;
    case Graphics::BlendFactor::BlendRGBFactorDestinationAlpha:
        return 7;
        break;
    case Graphics::BlendFactor::BlendRGBFactorOneMinusDestinationAlpha:
        return 8;
        break;
    case Graphics::BlendFactor::BlendRGBFactorSourceAlphaSaturated:
        return 11;
        break;
    case Graphics::BlendFactor::BlendRGBFactorBlendColor:
        return 16;
        break;
    case Graphics::BlendFactor::BlendRGBFactorOneMinusBlendColor:
        return 17;
        break;
    case Graphics::BlendFactor::BlendRGBFactorBlendAlpha:
        return 18;
        break;
    case Graphics::BlendFactor::BlendRGBFactorOneMinusBlendAlpha:
        return 19;
        break;
    default:
        return 1;
        break;
    }
}
#endif

class GraphicsRenderState
{
public:
    FillMode _FillMode;
    CullMode _CullMode;
    
    BlendOp _BlendOp_RGB;
    BlendOp _BlendOp_ALPHA;
    BlendFactor _BlendSrcRGBFactor;
    BlendFactor _BlendDstRGBFactor;
    BlendFactor _BlendSrcAlphaFactor;
    BlendFactor _BlendDstAlphaFactor;
    
    int _StencilRefValue;
    
    GraphicsRenderState();

    _uint GetHashCode()
    {
        _uint hashCode = 5;
        hashCode = 23 * hashCode + (_uint)_FillMode;
        hashCode = 23 * hashCode + (_uint)_CullMode;
        hashCode = 23 * hashCode + (_uint)_BlendOp_RGB;
        hashCode = 23 * hashCode + (_uint)_BlendOp_ALPHA;
        hashCode = 23 * hashCode + (_uint)_BlendSrcRGBFactor;
        hashCode = 23 * hashCode + (_uint)_BlendDstRGBFactor;
        hashCode = 23 * hashCode + (_uint)_BlendSrcAlphaFactor;
        hashCode = 23 * hashCode + (_uint)_BlendDstAlphaFactor;
        hashCode = 256 * hashCode + (_uint)_StencilRefValue;
        return hashCode;
    }
};

}//namespace GraphicsRenderState




#endif /* GraphicsRenderState_hpp */
