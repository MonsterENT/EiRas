#include "MaterialDX12.h"
#include <PlatformDependency/OnDX/Shader/ShaderDX12.h>
#include <Material/Shader.hpp>
#include <Material/ShaderLayout.h>
#include <Material/MaterialLayout.hpp>


using MaterialSys::MaterialDX12;
using MaterialSys::Shader;
using MaterialSys::ShaderDX12;

using MaterialSys::ShaderLayout;
using MaterialSys::ShaderSlot;
using MaterialSys::ShaderProp;
using MaterialSys::ShaderTable;
using MaterialSys::ShaderSlotType;

using MaterialSys::MaterialLayout;
using MaterialSys::MaterialSlot;
using MaterialSys::MaterialProp;
using MaterialSys::MaterialTable;
using MaterialSys::MaterialSlotType;

MaterialDX12::MaterialDX12(std::string name, Shader* shaderObj)
{
    Name = name;
    RawShaderObj = (ShaderDX12*)shaderObj->GetRawObj();
    //RawShaderObj->RefShaderLayout
    //Create Resourcs Layout
    //Props = new MaterialProp*[]

    for (int i = 0; i < RawShaderObj->RefShaderLayout->SlotNum; i++)
    {
        ShaderSlot* shaderSlot = RawShaderObj->RefShaderLayout->Slots[i];
        MaterialProp* tmpMatProp = 0;
        if (shaderSlot->SlotType == ShaderSlotType::ShaderSlotType_Prop)
        {
            ShaderProp* tmpProp = (ShaderProp*)shaderSlot;
            tmpMatProp = new MaterialProp(tmpProp->PropType, tmpProp->BufferSize);
            tmpMatProp->SlotID = tmpProp->PropID;
            Props.push_back(tmpMatProp);
            LayoutProps.push_back(tmpMatProp);
        }
        else if (shaderSlot->SlotType == ShaderSlotType::ShaderSlotType_Table)
        {
            ShaderTable* shaderTable = (ShaderTable*)shaderSlot;

            GraphicsResource** tmpResArray = new GraphicsResource * [shaderTable->PropNum];
            for (int propIndex = 0; propIndex < shaderTable->PropNum; propIndex++)
            {
                ShaderProp* tmpProp = shaderTable->Props[propIndex];
                tmpMatProp = new MaterialProp(tmpProp->PropType, tmpProp->BufferSize);
                tmpMatProp->SlotID = tmpProp->PropID;
                Props.push_back(tmpMatProp);
                tmpResArray[propIndex] = tmpMatProp->Resource;
            }
            MaterialTable* matTable = new MaterialTable(shaderTable->PropNum, tmpResArray);
            LayoutTables.push_back(matTable);
        }
    }
}

void MaterialDX12::SetProperty(int propertyId, void* res)
{

}

void MaterialDX12::UpdateRenderState(Graphics::GraphicsRenderState* renderState, Shader* shaderObj)
{
}
