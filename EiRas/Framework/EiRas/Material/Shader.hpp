//
//  Shader.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <string>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Global/PlatformDefine.h>

#if GRAPHICS_DX
#include <Windows.h>
#endif

namespace MaterialSys {

    class ShaderLayout;

    class Shader
    {
    public:
        Shader(std::string fileName, std::string vertexFuncName, std::string pixelFuncName);
        Shader()
        {
            this->PlatformBridge = 0;
        }
        void* GetRawObj();

        void InitLayout(ShaderLayout* layout);

    private:
        EiRasPlatformBridgeProtocol* PlatformBridge;
    };
};//namespace Material


#endif /* Shader_hpp */
