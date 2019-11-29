//
//  EiRas.hpp
//  EiRas
//
//  Created by MonsterENT on 11/11/19.
//

#ifndef EiRas_hpp
#define EiRas_hpp

#include <Global/PlatformDefine.h>
#include "Protocols/EiRasProtocol.h"
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

#if GRAPHICS_DX
#include <Windows.h>
#endif

namespace GraphicsAPI {

class EiRas
{
public:
    static EiRas* SharedInstance();

#if GRAPHICS_DX
    static EiRas* Create(HWND hwnd, int frameWidth, int frameHeight);
#elif GRAPHICS_METAL
    static EiRas* Create();
#endif


    void OnUpdate();


    
private:
    EiRasPlatformBridgeProtocol* PlatformBridge;
};

};



#endif /* EiRas_hpp */
