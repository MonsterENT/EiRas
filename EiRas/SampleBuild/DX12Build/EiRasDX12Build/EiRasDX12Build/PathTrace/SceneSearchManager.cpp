#include "SceneSearchManager.hpp"

using namespace Math;

void BuildSceneNodeInternel(SceneNode* cur, int curLvl, int targetLvl)
{
    if (curLvl >= targetLvl)
    {
        cur->isContainer = true;
    }
    else
    {
#pragma region Build
        float3 halfSize = cur->size / 2.0f;
        float3 quadSize = cur->size / 4.0f;
        SceneNode* n0 = new SceneNode;
        n0->centerPos = cur->centerPos + float3(quadSize.x, quadSize.y, quadSize.z);
        n0->size = halfSize;
        n0->parent = cur;
        BuildSceneNodeInternel(n0, curLvl + 1, targetLvl);

        SceneNode* n1 = new SceneNode;
        n1->centerPos = cur->centerPos + float3(-quadSize.x, quadSize.y, quadSize.z);
        n1->size = halfSize;
        n1->parent = cur;
        BuildSceneNodeInternel(n1, curLvl + 1, targetLvl);

        SceneNode* n2 = new SceneNode;
        n2->centerPos = cur->centerPos + float3(quadSize.x, quadSize.y, -quadSize.z);
        n2->size = halfSize;
        n2->parent = cur;
        BuildSceneNodeInternel(n1, curLvl + 1, targetLvl);

        SceneNode* n3 = new SceneNode;
        n3->centerPos = cur->centerPos + float3(-quadSize.x, quadSize.y, -quadSize.z);
        n3->size = halfSize;
        n3->parent = cur;
        BuildSceneNodeInternel(n3, curLvl + 1, targetLvl);

        SceneNode* n4 = new SceneNode;
        n4->centerPos = cur->centerPos + float3(quadSize.x, -quadSize.y, quadSize.z);
        n4->size = halfSize;
        n4->parent = cur;
        BuildSceneNodeInternel(n4, curLvl + 1, targetLvl);

        SceneNode* n5 = new SceneNode;
        n5->centerPos = cur->centerPos + float3(-quadSize.x, -quadSize.y, quadSize.z);
        n5->size = halfSize;
        n5->parent = cur;
        BuildSceneNodeInternel(n5, curLvl + 1, targetLvl);

        SceneNode* n6 = new SceneNode;
        n6->centerPos = cur->centerPos + float3(quadSize.x, -quadSize.y, -quadSize.z);
        n6->size = halfSize;
        n6->parent = cur;
        BuildSceneNodeInternel(n6, curLvl + 1, targetLvl);

        SceneNode* n7 = new SceneNode;
        n7->centerPos = cur->centerPos + float3(-quadSize.x, -quadSize.y, -quadSize.z);
        n7->size = halfSize;
        n7->parent = cur;
        BuildSceneNodeInternel(n7, curLvl + 1, targetLvl);

        cur->children.push_back(n0);cur->children.push_back(n1);cur->children.push_back(n2);cur->children.push_back(n3);
        cur->children.push_back(n4);cur->children.push_back(n5);cur->children.push_back(n6);cur->children.push_back(n7);
#pragma endregion
    }
}

void ReleaseSceneNodeInternel(SceneNode* cur)
{
    for (int i = 0; i < cur->children.size(); i++)
    {
        ReleaseSceneNodeInternel(cur->children[i]);
    }
    delete cur;
}

SceneNode::~SceneNode()
{
    children.clear();
    objects.clear();
}

int BuildSceneNodeGraphicResInternel(SceneNode* cur, int parentIdx, vector<SceneBlock> &blockArray, vector<SceneNodeDataPackInfo> &dataPackInfoArray)
{
    SceneBlock* curBlock = new SceneBlock();
    curBlock->pos = cur->centerPos;
    curBlock->size = cur->size;
    curBlock->parent = parentIdx;
    blockArray.push_back(*curBlock);
    int curIdx = blockArray.size() - 1;

    cur->BlockReference = curIdx;
    if (cur->isContainer)
    {
        dataPackInfoArray.push_back(SceneNodeDataPackInfo());
        curBlock->dataPackage = dataPackInfoArray.size() - 1;
    }
    else
    {
        curBlock->dataPackage = -1;
    }
    
    for (int i = 0; i < 8; i++)
    {
        if (i < cur->children.size())
        {
            curBlock->children[i] = BuildSceneNodeGraphicResInternel(cur->children[i], curIdx, blockArray, dataPackInfoArray);
        }
        else
        {
            curBlock->children[i] = -1;
        }
    }
    return curIdx;
}

SceneNode* SceneNode::BuildSceneNode(Math::float3 centerPos, Math::float3 size, int level)
{
    SceneNode* n = new SceneNode();
    n->centerPos = centerPos;
    n->size = size;
    n->parent = 0;

    BuildSceneNodeInternel(n, 1, level);
    return n;
}

void BuildNodeData(SceneNode* node, vector<TriangleData> &dataArray, vector<SceneNodeDataPackInfo> &dataPackInfoArray)
{
    if (node->isContainer)
    {
        dataPackInfoArray[node->BlockReference].start = dataArray.size();
        dataPackInfoArray[node->BlockReference].end = dataArray.size() + node->objects.size();

        for (int i = 0; i < node->objects.size(); i++)
        {
            dataArray.push_back(*(TriangleData*)(node->objects[i]));
        }
    }
    else
    {
        for(int i = 0; i < node->children.size(); i++)
        {
            BuildNodeData(node->children[i], dataArray, dataPackInfoArray);
        }
    }
}

void SceneSearchManager::BuildGraphics(ComputeKernel* kernel, int nodeInfoSlot, int packInfoSlot, int triangleDataSlot)
{
    vector<SceneBlock> blockArray;
    vector<SceneNodeDataPackInfo> dataPackInfoArray;
    BuildSceneNodeGraphicResInternel(node, -1, blockArray, dataPackInfoArray);

    if (SceneNodeInfoResObj == 0)
    {
        SceneNodeInfoResObj = new GraphicsResource("SceneNodeInfoResObj", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW, false);
        SceneNodeInfoResObj->InitAsShaderResource(sizeof(SceneBlock) * blockArray.size());
    }

    if (SceneDataPackInfoResObj == 0)
    {
        SceneDataPackInfoResObj = new GraphicsResource("SceneDataPackInfoResObj", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW, false);
        SceneDataPackInfoResObj->InitAsShaderResource(sizeof(SceneNodeDataPackInfo) * blockArray.size());
    }

    SceneNodeInfoResObj->SetResource(&blockArray[0], false);
    SceneDataPackInfoResObj->SetResource(&dataPackInfoArray[0], false);

    //mat->SetPropertyObject(SceneNodeInfoResObj, nodeInfoSlot);
    //mat->SetPropertyObject(SceneDataPackInfoResObj, packInfoSlot);

    vector<TriangleData> triangleDataArray;
    BuildNodeData(node, triangleDataArray, dataPackInfoArray);
    
    if (SceneTriangleDataResObj == 0)
    {
        SceneTriangleDataResObj = new GraphicsResource("SceneTriangleDataResObj", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_LOW, false);
        SceneTriangleDataResObj->InitAsShaderResource(sizeof(TriangleData) * triangleDataArray.size());
    }

    SceneTriangleDataResObj->SetResource(&triangleDataArray[0]);
    kernel->SetPropertyObject(SceneTriangleDataResObj, triangleDataSlot);
}

SceneSearchManager::SceneSearchManager(Math::float3 centerPos, Math::float3 size, int level)
{
    this->level = level;
    node = SceneNode::BuildSceneNode(centerPos, size, level);
    SceneNodeInfoResObj = NULL;
    SceneDataPackInfoResObj = NULL;
}

SceneSearchManager::~SceneSearchManager()
{
    if (node)
    {
        ReleaseSceneNodeInternel(node);
        node = 0;
    }

    delete SceneNodeInfoResObj;
    SceneNodeInfoResObj = NULL;
    delete SceneDataPackInfoResObj;
    SceneDataPackInfoResObj = NULL;
}

void SceneSearchManager::AddSceneObject(void* obj, float3 center, float3 size)
{
    node->objects.push_back(obj);
}
