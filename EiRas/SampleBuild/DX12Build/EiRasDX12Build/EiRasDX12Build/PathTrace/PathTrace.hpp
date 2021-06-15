#ifndef Path_Trace_Hpp
#define Path_Trace_Hpp
#include "SceneSearchManager.hpp"
#include <Component/ComponentManager/ComponentBase.hpp>

class PathTrace : public ComponentSys::ComponentBase
{
public:
	PathTrace();
	~PathTrace();

	void OnUpdate();

	SceneSearchManager* SceneManager;

private:

};
#endif