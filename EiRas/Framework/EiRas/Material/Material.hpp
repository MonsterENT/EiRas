//
//  Material.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include "Shader.hpp"

namespace MaterialSys {

class Material
{
public:
    Material(Shader* shader);
    
private:
    Shader* shader;
};

};//namespace Material

#endif /* Material_hpp */
