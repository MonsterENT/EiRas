//
//  GraphicsResourceHeapMetalAdapter.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 12/8/19.
//  Copyright © 2019 MonsterENT. All rights reserved.
//

#ifndef GraphicsResourceHeapMetalAdapter_hpp
#define GraphicsResourceHeapMetalAdapter_hpp

namespace MaterialSys {

class GraphicsResource;
void* createResourceHeapMetal(int resCount, GraphicsResource** resArray);

}

#endif /* GraphicsResourceHeapMetalAdapter_hpp */
