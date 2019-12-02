#include "MaterialDX12.h"
#include <PlatformDependency/OnDX/Shader/ShaderDX12.h>
#include <Material/Shader.hpp>
#include <PlatformDependency/OnDX/Shader/ShaderLayout.h>

using MaterialSys::MaterialDX12;
using MaterialSys::Shader;
using MaterialSys::ShaderDX12;
using MaterialSys::ShaderLayout;

MaterialDX12::MaterialDX12(std::string name, Shader* shaderObj)
{
    Name = name;
    RawShaderObj = (ShaderDX12*)shaderObj->GetRawObj();
    //RawShaderObj->RefShaderLayout
    //Create Resourcs Layout
}

void MaterialDX12::SetProperty(int propertyId, void* res)
{

}

void MaterialDX12::UpdateRenderState(Graphics::GraphicsRenderState* renderState, Shader* shaderObj)
{
}
