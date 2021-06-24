#ifndef Scene_Search_Manager_Hpp
#define Scene_Search_Manager_Hpp

#include <Math/Math.hpp>
#include <vector>
#include "GraphicsData.hpp"
#include <Material/GraphicsResource.hpp>
#include <Material/Material.hpp>
#include <GPCompute/ComputeKernel.hpp>

using namespace MaterialSys;
using namespace GPCompute;
class SceneNode
{
public:
	bool isContainer;

	std::vector<void*> objects;

	Math::float3 centerPos, size;
	std::vector<SceneNode*> children;
	SceneNode* parent;

	int BlockReference;

	static SceneNode* BuildSceneNode(Math::float3 centerPos, Math::float3 size, int level);

	~SceneNode();
};

class SceneSearchManager
{
public:
	SceneSearchManager(Math::float3 centerPos, Math::float3 size, int level);
	~SceneSearchManager();

	void AddSceneObject(void* obj, Math::float3 center, Math::float3 size);

	SceneNode* node;

	void BuildGraphics(ComputeKernel* kernel, int nodeInfoSlot, int packInfoSlot, int triangleDataSlot);
private:
	int level;

	MaterialSys::GraphicsResource* SceneNodeInfoResObj;
	MaterialSys::GraphicsResource* SceneDataPackInfoResObj;
	MaterialSys::GraphicsResource* SceneTriangleDataResObj;
};

#endif