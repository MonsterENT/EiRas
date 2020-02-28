#include "Image.hpp"
#include <ImageSys/ImageSys.hpp>
#include <LogSys/LogManager.hpp>
#include <Material/GraphicsResource.hpp>

#include <Math/Math.hpp>
using namespace ImageSys;
using namespace LogSys;
using namespace MaterialSys;
using std::vector;
using namespace Math;

vector<Image*> ImageSys::ImageSysBuildingList;

Image::Image(std::string filePath)
{
    isFinishBuild = false;
    unsigned char* data = LoadImageFromFile(filePath, (int*)&Width, (int*)&Height, (int*)&Channels);
    if (data == 0)
    {
        LogManager::DebugPrint("Load Fail " + filePath);
        return;
    }

    PipelineResource = new GraphicsResource(filePath, GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT, false);
    PipelineResource->InitAsShaderResource(Width, Height, data, &isFinishBuild);
    
#pragma message("TOFIX InitAsShaderResource will copy data")
    //FreeData(data);

    ImageSysBuildingList.push_back(this);
}

void Image::Build(void* cmdList)
{
    PipelineResource->ShaderResourceBuild(cmdList);
}

void Image::FinishBuild()
{
    PipelineResource->ShaderResourceFinishBuild();
#pragma message("TOFIX remove from building list")
}