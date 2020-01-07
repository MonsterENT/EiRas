//
//  FileManagerMacOSAdapter.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/5/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#ifndef FileManagerMacOSAdapter_hpp
#define FileManagerMacOSAdapter_hpp

#include <string>

namespace FileSys {

const char* getResourcePathMacOs(std::string resName, std::string type);

}

#endif /* FileManagerMacOSAdapter_hpp */
