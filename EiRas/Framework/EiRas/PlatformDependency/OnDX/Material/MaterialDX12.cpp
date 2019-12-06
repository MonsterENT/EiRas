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
}

void MaterialDX12::SetProperty(int propertyId, void* res)
{

}

void MaterialDX12::UpdateRenderState(Graphics::GraphicsRenderState* renderState, Shader* shaderObj)
{
}
