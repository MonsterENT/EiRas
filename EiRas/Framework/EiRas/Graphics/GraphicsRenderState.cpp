//
//  GraphicsRenderState.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/11/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "GraphicsRenderState.hpp"
using namespace Graphics;

GraphicsRenderState::GraphicsRenderState()
{
    _FillMode = FillMode::FillMode_SOLID;
    _CullMode = CullMode::CullModeBack;
    _ZTest = CompareFunction::CompareFunctionLess;
    _ZWrite = true;

    _BlendOp_RGB = BlendOp::BlendOpAdd;
    _BlendOp_ALPHA = BlendOp::BlendOpAdd;
    _BlendSrcRGBFactor = BlendFactor::BlendRGBFactorOne;
    _BlendDstRGBFactor = BlendFactor::BlendRGBFactorZero;
    _BlendSrcAlphaFactor = BlendFactor::BlendRGBFactorOne;
    _BlendDstAlphaFactor = BlendFactor::BlendRGBFactorZero;
    
    _StencilRefValue = 0;
}
