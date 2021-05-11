#ifndef Component_Base_Hpp
#define Component_Base_Hpp

namespace ComponentSys
{
    class ComponentBase
    {
    public:
        virtual void OnInit()
        {
        }

        virtual void OnUpdate()
        {
        }

        virtual void OnDestory()
        {
        }
    };
}

#endif