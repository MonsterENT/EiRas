#ifndef Component_Manager_Hpp
#define Component_Manager_Hpp

#include <vector>

namespace ComponentSys
{
    class ComponentBase;
    class ComponentManager
    {
    public:
        static ComponentManager* SharedManager();

        void AddComponent(ComponentBase* comp);
        void RemoveComponent(ComponentBase* comp);

        void OnUpdate();
    private:
        std::vector<ComponentBase*> components;
    };
}

#endif