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

namespace MaterialSys {

class Shader
{
public:
    Shader(std::string fileName, std::string vertexFuncName, std::string pixelFuncName);
    
private:
    void* pd_ShaderObj;
};

};//namespace Material


#endif /* Shader_hpp */
