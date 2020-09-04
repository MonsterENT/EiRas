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

void Label::NeedLayout()
{
    View::NeedLayout();
    _BuildTextMesh();
}

void Label::DrawView(Graphics::CommandBuffer* cmdBuffer)
{
    View::DrawView(cmdBuffer);
    cmdBuffer->DrawRenderData(_Render);
}

void Label::_BuildTextMesh()
{
    if (_Text == 0)
    {
        return;
    }

    _Render->ClearMesh(true);
    _Render->ClearMaterials(true);

    _uint charCount = _Text->CharDataList.size();
    float posTop = _NDC.top;
    float posLeft = _NDC.left;
    float posButtom = _NDC.top - _NDC.height;
    float posMid = (posTop - posButtom) / 2.0f + posButtom;

    //Batch
    map<_uint, BatchedFontMeshData> BatchedData;
    float charMeshHeightMax = 0, hCharMeshHeightMax = 0;

    for (int i = 0; i < charCount; i++)
    {
        rect_float uvRect = _Text->CharDataList[i].MappingRect;
        _uint height, width;
        GUISystem::SharedInstance()->GetFrameSize(width, height);
        //pixel Size
        float tHeight = uvRect.height * FONT_MAP_HEIGHT / (float)height;
        charMeshHeightMax = tHeight > charMeshHeightMax ? tHeight : charMeshHeightMax;
    }
    hCharMeshHeightMax = charMeshHeightMax / 2.0f;
    posButtom = posMid - hCharMeshHeightMax;

    for (int i = 0; i < charCount; i++)
    {
        rect_float uvRect = _Text->CharDataList[i].MappingRect;
        _uint refMapIndex = _Text->CharDataList[i].FontMapIndex;
        bool alignmentMid = _Text->CharDataList[i].AlignmentMid;

        _uint height, width;
        GUISystem::SharedInstance()->GetFrameSize(width, height);
        //pixel Size
        float charMeshHeight = uvRect.height * FONT_MAP_HEIGHT / (float)height;
        float charMeshWidth = uvRect.width * FONT_MAP_WIDTH / (float)width;

        float3 pos0, pos1;
        float3 pos2, pos3;

        if (alignmentMid)
        {
            float hCharMeshHeight = charMeshHeight / 2.0f;
            pos0 = float3(posLeft, posMid + hCharMeshHeight, 1), pos1 = float3(posLeft + charMeshWidth, posMid + hCharMeshHeight, 1);
            pos2 = float3(posLeft, posMid - hCharMeshHeight, 1), pos3 = float3(posLeft + charMeshWidth, posMid - hCharMeshHeight, 1);
        }
        else
        {
            pos0 = float3(posLeft, posButtom + charMeshHeight, 1); pos1 = float3(posLeft + charMeshWidth, posButtom + charMeshHeight, 1);
            pos2 = float3(posLeft, posButtom, 1); pos3 = float3(posLeft + charMeshWidth, posButtom, 1);
        }

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
        posLeft += charMeshWidth;
    }

    map<_uint, BatchedFontMeshData>::iterator batchedDataIt = BatchedData.begin();
    while (batchedDataIt != BatchedData.end())
    {
        Mesh* textMesh = new Mesh("TextMesh");

        _Render->AddMesh(textMesh);
        textMesh->SubMeshCount = 1;
        textMesh->SubMeshes = new SubMesh[1];

        BatchedFontMeshData* data = &(batchedDataIt->second);

        Material* mat = RuntimeUtilities::CreateFontMaterial("Font Mat", GUISystem::SharedInstance()->_CmdBuffer);
        mat->SetProperty(FontManager::SharedInstance()->fontDataList[data->RefFontImageIndex]->_FontImage, 1, 0);
        mat->SetProperty(&_TextColor, 0, 0);
        _Render->AddMaterial(mat, 0);

        _uint indexCount = data->Pos.size() / 4 * 6;
        SubMesh* subMesh = &(textMesh->SubMeshes[0]);
        subMesh->IndexCount = indexCount;
        subMesh->IndexBufferStartIdx = 0;

        _uint* indexData = new _uint[sizeof(float2) * indexCount];
        for (int j = 0, vertexIndex = 0; j < indexCount; j += 6, vertexIndex += 4)
        {
            indexData[j + 0] = vertexIndex;
            indexData[j + 1] = vertexIndex + 1;
            indexData[j + 2] = vertexIndex + 2;
            indexData[j + 3] = vertexIndex + 1;
            indexData[j + 4] = vertexIndex + 2;
            indexData[j + 5] = vertexIndex + 3;
        }

        textMesh->SetVertexData(data->Pos, data->UV);
        textMesh->SetIndexData(indexData, indexCount);
        batchedDataIt++;
        textMesh->BuildBuffer(MeshType::VertexInput2D);
    }
}