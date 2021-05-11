#include "RMCapture.hpp"
#include <Math/Math.hpp>

#include <Graphics/CommandBuffer.hpp>
#include <GPCompute/ComputeKernel.hpp>

#include <Material/Shader.hpp>
#include <Material/ShaderLayout.h>

#include <Component/FileSys/FileManager.hpp>

#include <Mesh/Mesh.hpp>

using namespace MaterialSys;
using namespace Graphics;
using namespace GPCompute;
using namespace MeshSys;
using namespace Math;


CommandBuffer* gpCmd;
ComputeKernel* SDFGenProcessor;

void RMCapture::OnInit()
{
    std::string modelPath = FileSys::FileManager::shareInstance()->GetModelResourcePath("SF90_TMP", "FBX");
    Mesh* cloudMesh = new Mesh("CloudModel");
    cloudMesh->LoadDataFromFile(modelPath);
    _uint vCount = cloudMesh->GetVertexCount();
    float3* vertex = cloudMesh->GetPositionData();
    float3* normal = cloudMesh->GetNormalData();

    ShaderLayout* gpLayout = new ShaderLayout(4);
    ShaderProp* propNormalBuffer = new ShaderProp("normal", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT, 0);
    GraphicsResource* normalBuffer = new GraphicsResource("NormalBuffer", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT, false);
    normalBuffer->InitAsShaderResource();
    normalBuffer->SetResource(normal, true);
    

    std::string gpShaderPath = FileSys::FileManager::shareInstance()->GetResourcePath("Shader\\DX\\GP", "hlsl");
    SDFGenProcessor = new ComputeKernel();
    //SDFGenProcessor->SetLayout()
    SDFGenProcessor->AddKernel(gpShaderPath, "SDFGen");

    gpCmd = new CommandBuffer("GP CommandBuffer");
    gpCmd->Reset();

    //SDFGenProcessor->SetLayout()

    //gpCmd->DispatchComputeKernel()
}

void RMCapture::OnUpdate()
{

}