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


namespace Graphics {
class GraphicsVertexDescriptor;
}

namespace MaterialSys {

    class ShaderLayout;

    class Shader
    {
    public:
        Shader(std::string fileName, std::string vertexFuncName, std::string pixelFuncName);
        Shader()
        {
            this->PlatformBridge = 0;
            this->Layout = 0;
        }
        void* GetRawObj();

        void InitLayout(ShaderLayout* layout);
        
        void InitVertexDescriptor(Graphics::GraphicsVertexDescriptor* vertexDescriptor);

        EiRasPlatformBridgeProtocol* PlatformBridge;

        ShaderLayout* Layout;
    };
};//namespace Material


#endif /* Shader_hpp */
