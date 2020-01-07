//
//  FileManager.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/5/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#ifndef FileManager_hpp
#define FileManager_hpp

#include <string>

namespace FileSys {

class FileManager
{
public:
    static FileManager* shareInstance();
    
    const char * GetResourcePath(std::string resName, std::string type);
};

}

#endif /* FileManager_hpp */
