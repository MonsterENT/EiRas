//
//  LogManager.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/7/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#ifndef LogManager_hpp
#define LogManager_hpp

#include <string>
#include <Global/GlobalDefine.h>

namespace LogSys {
class LogManager
{
public:
    static void DebugPrint(std::string str);
    static void DebugPrint(int i);
    static void DebugPrint(float f);
    static void DebugPrint(double d);
    static void DebugPrint(_uint ui);
};
}

#endif /* LogManager_hpp */
