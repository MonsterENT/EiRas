//
//  MetalMacro.h
//  EiRasMetalBuild
//
//  Created by MonsterENT on 11/12/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef MetalMacro_h
#define MetalMacro_h

#define PROCESS_OC_OBJ(oc_obj, bridge_ptr) \
oc_obj.self_retain = oc_obj;\
void* bridge_ptr = (__bridge void*)oc_obj;


#endif /* MetalMacro_h */
