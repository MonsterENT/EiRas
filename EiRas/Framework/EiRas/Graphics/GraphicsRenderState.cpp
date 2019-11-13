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
    _CullMode = CullMode::CullModeBack;
    
    _BlendOp = BlendOp::BlendOpAdd;
    _BlendSrcRGBFactor = BlendFactor::BlendRGBFactorOne;
    _BlendDstRGBFactor = BlendFactor::BlendRGBFactorZero;
    _BlendSrcAlphaFactor = BlendFactor::BlendRGBFactorOne;
    _BlendDstAlphaFactor = BlendFactor::BlendRGBFactorZero;
    
    _StencilRefValue = 0;
}
