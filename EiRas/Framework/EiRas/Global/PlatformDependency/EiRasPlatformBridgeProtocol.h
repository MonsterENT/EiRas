//
//  EiRasPlatformBridgeProtocol.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/11/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef EiRasPlatformBridgeProtocol_h
#define EiRasPlatformBridgeProtocol_h

class EiRasPlatformBridgeProtocol {
public:
    void* raw_obj;
    virtual ~EiRasPlatformBridgeProtocol()
    {
        delete raw_obj;
        raw_obj = 0;
    }
private:
    
};

#endif /* EiRasPlatformBridgeProtocol_h */
