//
//  EiRas.hpp
//  EiRas
//
//  Created by MonsterENT on 11/11/19.
//

#ifndef EiRas_hpp
#define EiRas_hpp

#include "Protocols/EiRasProtocol.h"
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>

namespace GraphicsAPI {

class EiRas
{
public:
    static EiRas* SharedInstance();
    static EiRas* Create();
    
    void OnUpdate();
    
private:
    EiRasPlatformBridgeProtocol* PlatformBridge;
};

};



#endif /* EiRas_hpp */
