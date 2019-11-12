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
    _BlendSrcRGBFactor = BlendRGBFactor::BlendRGBFactorOne;
    _BlendDstRGBFactor = BlendRGBFactor::BlendRGBFactorOne;
    _BlendSrcAlphaFactor = BlendAlphaFactor::BlendAlphaFactorOne;
    _BlendDstAlphaFactor = BlendAlphaFactor::BlendAlphaFactorZero;
    
    _StencilRefValue = 0;
}
