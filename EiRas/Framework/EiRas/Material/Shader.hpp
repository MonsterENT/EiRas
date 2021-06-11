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
#include <Global/GlobalDefine.h>

namespace Graphics {
class GraphicsVertexDescriptor;
}

namespace MaterialSys {

    class ShaderLayout;

    class Shader
    {
    public:
        Shader(std::string fileName, std::string vertexFuncName, std::string pixelFuncName);
        Shader(std::string fileName);
        ~Shader();
        void AddVertexFuncToPass(std::string vertexFuncName, _uint pass);
        void AddPixelFuncToPass(std::string pixelFuncName, _uint pass);

        void SetVertexFuncToPass(_uint index, _uint pass);
        void SetPixelFuncToPass(_uint index, _uint pass);
        
        Shader()
        {
            this->PlatformBridge = 0;
            this->Layout = 0;
        }
        void* GetRawObj();

        void SetLayout(ShaderLayout* layout);
        
        void InitVertexDescriptor(Graphics::GraphicsVertexDescriptor* vertexDescriptor, _uint pass = 0, bool enableInstance = false);

        EiRasPlatformBridgeProtocol* PlatformBridge;

        ShaderLayout* Layout;
    };
};//namespace Material


#endif /* Shader_hpp */
