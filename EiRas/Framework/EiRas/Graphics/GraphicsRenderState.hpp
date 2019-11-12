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

enum CullMode
{
    CullModeBack = 0,
    CullModeFront = 1,
    CullModeNone = 3
};

enum BlendOp
{
    BlendOpAdd = 0,
};

enum BlendRGBFactor
{
    BlendRGBFactorOne = 0,
    BlendRGBFactorZero = 1,
};

enum BlendAlphaFactor
{
    BlendAlphaFactorOne = 0,
    BlendAlphaFactorZero = 1,
};

class GraphicsRenderState
{
public:
    CullMode _CullMode;
    
    BlendOp _BlendOp;
    BlendRGBFactor _BlendSrcRGBFactor;
    BlendRGBFactor _BlendDstRGBFactor;
    BlendAlphaFactor _BlendSrcAlphaFactor;
    BlendAlphaFactor _BlendDstAlphaFactor;
    
    int _StencilRefValue;
    
    GraphicsRenderState();
};

}//namespace GraphicsRenderState




#endif /* GraphicsRenderState_hpp */
