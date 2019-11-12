//
//  Material.cpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#include "Material.hpp"
using MaterialSys::Material;

Material::Material(Shader* shader)
{
    this->shader = shader;
}
