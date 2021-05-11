#ifndef RM_Capture_Hpp
#define RM_Capture_Hpp

#include <Component/ComponentManager/ComponentBase.hpp>
using ComponentSys::ComponentBase;

class RMCapture : public ComponentBase
{
public:
    void OnInit();
    void OnUpdate();
};

#endif