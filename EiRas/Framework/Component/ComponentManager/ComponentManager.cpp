#include "ComponentManager.hpp"
#include "ComponentBase.hpp"
using namespace ComponentSys;

static ComponentManager* g_manager = 0;

ComponentManager* ComponentManager::SharedManager()
{
    if (g_manager == 0)
    {
        g_manager = new ComponentManager();
    }
    return g_manager;
}

void ComponentManager::OnUpdate()
{
    std::vector<ComponentBase*>::iterator it = components.begin();
    while (it != components.end())
    {
        (*it)->OnUpdate();
        it++;
    }
}

void ComponentManager::AddComponent(ComponentBase* comp)
{
    components.push_back(comp);
}

void ComponentManager::RemoveComponent(ComponentBase* comp)
{
    std::vector<ComponentBase*>::iterator it = components.begin();
    while (it != components.end())
    {
        if (comp == *it)
        {
            components.erase(it);
            break;
        }
        it++;
    }
}
