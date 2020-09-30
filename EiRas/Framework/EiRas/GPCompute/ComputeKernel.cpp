#include "ComputeKernel.hpp"
#include <Material/MaterialLayout.hpp>
#include <Material/ShaderLayout.h>

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/GPCompute/ComputeKernelDX12Bridge.hpp>
#endif

using namespace GPCompute;
using namespace MaterialSys;

ComputeKernel::ComputeKernel()
{
    ResLayout = 0;
#if GRAPHICS_DX
    PlatformBridge = new ComputeKernelDX12Bridge();
#endif
}

void ComputeKernel::SetLayout(MaterialSys::ShaderLayout* layout)
{
    ResLayout = new MaterialLayout(layout->SlotNum);
    for (int i = 0; i < layout->SlotNum; i++)
    {
        ShaderSlot* shaderSlot = layout->Slots[i];
        MaterialProp* tmpMatProp = 0;
        if (shaderSlot->SlotType == ShaderSlotType::ShaderSlotType_Prop)
        {
            ShaderProp* tmpProp = (ShaderProp*)shaderSlot;
            tmpMatProp = new MaterialProp(tmpProp->PropName, tmpProp->PropType, tmpProp->Visibility, tmpProp->UpdateFreq, true, tmpProp->BufferSize);
#if GRAPHICS_DX
            tmpMatProp->SlotID = i;
#endif
            ResLayout->Slots[i] = tmpMatProp;
        }
        else if (shaderSlot->SlotType == ShaderSlotType::ShaderSlotType_Builtin_ViewProj ||
            shaderSlot->SlotType == ShaderSlotType::ShaderSlotType_Ref_WorldMatrix)
        {
            MaterialSlot* tmpSlot = new MaterialSlot();
#if GRAPHICS_DX
            tmpSlot->SlotID = i;
#endif
            tmpSlot->SlotType = (MaterialSlotType)shaderSlot->SlotType;
            ResLayout->Slots[i] = tmpSlot;
        }
    }

    ((ComputeKernelDX12Bridge*)PlatformBridge)->SetLayout(layout, ResLayout);
}

void ComputeKernel::AddKernel(std::string fileName, std::string kernelName)
{
    ((ComputeKernelDX12Bridge*)PlatformBridge)->AddKernel(fileName, kernelName);
}

void ComputeKernel::Build()
{
    ((ComputeKernelDX12Bridge*)PlatformBridge)->Build();
}

void ComputeKernel::SetProperty(void* res, _uint slotIndex)
{
    MaterialSlot* tSlot = ResLayout->Slots[slotIndex];
    if (tSlot->SlotType == MaterialSlotType::MaterialSlotType_Prop)
    {
        MaterialProp* prop = (MaterialProp*)tSlot;
        prop->Resource->SetResource(res, false);
    }
}

void ComputeKernel::GetPropertyData(void* res, _uint slotIndex)
{
    MaterialSlot* tSlot = ResLayout->Slots[slotIndex];
    if (tSlot->SlotType == MaterialSlotType::MaterialSlotType_Prop)
    {
        MaterialProp* prop = (MaterialProp*)tSlot;
        prop->Resource->GetResource(res);
    }
}