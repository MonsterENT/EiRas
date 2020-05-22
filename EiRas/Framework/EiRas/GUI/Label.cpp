#include "Label.hpp"
#include <Mesh/Mesh.hpp>
#include <GUI/GUISystem.hpp>
#include <Graphics/CommandBuffer.hpp>
#include <Material/Material.hpp>
#include <FontSys/FontManager.hpp>
#include "RuntimeUtilities.hpp"
#include <map>
#include <vector>

using std::map;
using std::pair;
using std::vector;
using namespace MaterialSys;
using namespace Graphics;
using namespace MeshSys;
using namespace GUISys;
using namespace FontSys;
using namespace Math;

typedef struct BatchedFontMeshData
{
    vector<float2> UV;
    vector<float3> Pos;
    _uint RefFontImageIndex;
}BatchedFontMesh;

Label::Label()
{
    _Text = 0;
    _Render = new RenderData;
    SetTextColor(float4(0, 0, 0, 1));
}

void Label::SetText(FontSys::Text* text)
{
    _Text = text;
    _BuildTextMesh();
}

void Label::DrawView(Graphics::CommandBuffer* cmdBuffer)
{
    View::DrawView(cmdBuffer);
    cmdBuffer->DrawRenderData(_Render);
}

void Label::_BuildTextMesh()
{
    _Render->ClearMesh(true);
    _Render->ClearMaterials(true);

    _uint charCount = _Text->CharDataList.size();
    float subMeshWidth = _NDC.width / (float)charCount;
    float subMeshHeight = _NDC.height;
    float posTop = _NDC.top;
    float posLeft = _NDC.left;

    //Batch
    map<_uint, BatchedFontMeshData> BatchedData;


    for (int i = 0; i < charCount; i++)
    {
        rect_float uvRect = _Text->CharDataList[i].MappingRect;
        _uint refMapIndex = _Text->CharDataList[i].FontMapIndex;

        float3 pos0 = float3(posLeft, posTop, 1), pos1 = float3(posLeft + subMeshWidth, posTop, 1);
        float3 pos2 = float3(posLeft, posTop - subMeshHeight, 1), pos3 = float3(posLeft + subMeshWidth, posTop - subMeshHeight, 1);

        float2 uv0 = float2(uvRect.left, uvRect.top), uv1 = float2(uvRect.left + uvRect.width, uvRect.top);
        float2 uv2 = float2(uvRect.left, uvRect.top + uvRect.height), uv3 = float2(uvRect.left + uvRect.width, uvRect.top + uvRect.height);

        map<_uint, BatchedFontMeshData>::iterator BatchedPosDataIt = BatchedData.find(refMapIndex);

        if (BatchedPosDataIt == BatchedData.end())
        {
            BatchedFontMeshData tFontMeshData;
            tFontMeshData.Pos.push_back(pos0);
            tFontMeshData.Pos.push_back(pos1);
            tFontMeshData.Pos.push_back(pos2);
            tFontMeshData.Pos.push_back(pos3);

            tFontMeshData.UV.push_back(uv0);
            tFontMeshData.UV.push_back(uv1);
            tFontMeshData.UV.push_back(uv2);
            tFontMeshData.UV.push_back(uv3);
            tFontMeshData.RefFontImageIndex = refMapIndex;
            BatchedData.insert(pair<_uint, BatchedFontMeshData>(refMapIndex, tFontMeshData));
        }
        else
        {
            map<_uint, BatchedFontMeshData>::iterator batchedDataIt = BatchedData.find(refMapIndex);
            batchedDataIt->second.Pos.push_back(pos0);
            batchedDataIt->second.Pos.push_back(pos1);
            batchedDataIt->second.Pos.push_back(pos2);
            batchedDataIt->second.Pos.push_back(pos3);
            batchedDataIt->second.UV.push_back(uv0);
            batchedDataIt->second.UV.push_back(uv1);
            batchedDataIt->second.UV.push_back(uv2);
            batchedDataIt->second.UV.push_back(uv3);
        }
        posLeft += subMeshWidth;
    }

    Mesh* textMesh = new Mesh("TextMesh");

    _Render->SetMesh(textMesh);
    textMesh->SubMeshCount = BatchedData.size();
    textMesh->SubMeshes = new SubMesh[textMesh->SubMeshCount];

    _uint subMeshIndex = 0;
    map<_uint, BatchedFontMeshData>::iterator batchedDataIt = BatchedData.begin();
    while (batchedDataIt != BatchedData.end())
    {
        BatchedFontMeshData* data = &(batchedDataIt->second);

        Material* mat = RuntimeUtilities::CreateFontMaterial("Font Mat", GUISystem::SharedInstance()->_CmdBuffer);
        mat->SetProperty(FontManager::SharedInstance()->fontDataList[data->RefFontImageIndex]->_FontImage, 1, 0);
        mat->SetProperty(&_TextColor, 0, 0);
        _Render->AddMaterial(mat, 0);

        vector<float3>* tPos = &(data->Pos);
        vector<float2>* tUV = &(data->UV);

        SubMesh* subMesh = &(textMesh->SubMeshes[subMeshIndex++]);
        subMesh->IndicesCount = tPos->size() / 4 * 6;
        subMesh->VerticesCount = tPos->size();
        subMesh->IndicesData = new _uint[subMesh->IndicesCount];

        for (int j = 0, vertexIndex = 0; j < subMesh->IndicesCount; j += 6, vertexIndex += 4)
        {
            subMesh->IndicesData[j + 0] = vertexIndex;
            subMesh->IndicesData[j + 1] = vertexIndex + 1;
            subMesh->IndicesData[j + 2] = vertexIndex + 2;
            subMesh->IndicesData[j + 3] = vertexIndex + 1;
            subMesh->IndicesData[j + 4] = vertexIndex + 2;
            subMesh->IndicesData[j + 5] = vertexIndex + 3;
        }

        subMesh->PositionData = new float3[subMesh->VerticesCount];
        memcpy(subMesh->PositionData, &(*tPos)[0], sizeof(float3) * subMesh->VerticesCount);
        subMesh->UVData = new float2[subMesh->VerticesCount];
        memcpy(subMesh->UVData, &(*tUV)[0], sizeof(float2) * subMesh->VerticesCount);
        batchedDataIt++;
    }
    textMesh->BuildBuffer(MeshType::VertexInput2D);
}