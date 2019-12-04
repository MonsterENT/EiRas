//
//  GraphicsRenderState.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/11/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef GraphicsRenderState_hpp
#define GraphicsRenderState_hpp

namespace Graphics
{

typedef enum CullMode
{
    CullModeBack = 0,
    CullModeFront = 1,
    CullModeNone = 3
} CullMode;

typedef enum BlendOp
{
    BlendOpAdd = 0,
} BlendOp;

typedef enum BlendFactor
{
    BlendRGBFactorZero = 0,
    BlendRGBFactorOne = 1,
    BlendRGBFactorSourceColor = 2,
    BlendRGBFactorOneMinusSourceColor = 3,
    BlendRGBFactorSourceAlpha = 4,
    BlendRGBFactorOneMinusSourceAlpha = 5,
    BlendRGBFactorDestinationColor = 6,
    BlendRGBFactorOneMinusDestinationColor = 7,
    BlendRGBFactorDestinationAlpha = 8,
    BlendRGBFactorOneMinusDestinationAlpha = 9,
    BlendRGBFactorSourceAlphaSaturated = 10,
    BlendRGBFactorBlendColor = 11,
    BlendRGBFactorOneMinusBlendColor = 12,
    BlendRGBFactorBlendAlpha = 13,
    BlendRGBFactorOneMinusBlendAlpha = 14,
//    BlendRGBFactorSource1Color              API_AVAILABLE(macos(10.12), ios(10.11)) = 15,
//    BlendRGBFactorOneMinusSource1Color      API_AVAILABLE(macos(10.12), ios(10.11)) = 16,
//    BlendRGBFactorSource1Alpha              API_AVAILABLE(macos(10.12), ios(10.11)) = 17,
//    BlendRGBFactorOneMinusSource1Alpha      API_AVAILABLE(macos(10.12), ios(10.11)) = 18,
} BlendFactor;

class GraphicsRenderState
{
public:
    CullMode _CullMode;
    
    BlendOp _BlendOp;
    BlendFactor _BlendSrcRGBFactor;
    BlendFactor _BlendDstRGBFactor;
    BlendFactor _BlendSrcAlphaFactor;
    BlendFactor _BlendDstAlphaFactor;
    
    int _StencilRefValue;
    
    GraphicsRenderState();
};

}//namespace GraphicsRenderState




#endif /* GraphicsRenderState_hpp */
