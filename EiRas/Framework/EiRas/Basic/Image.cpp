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

Image::Image(std::string name)
{
    isFinishBuild = false;
    PipelineResource = 0;
    ImageSysBuildingList.push_back(this);
}

void Image::LoadFromFile(std::string filePath)
{
    unsigned char* data = LoadImageFromFile(filePath, (int*)&Width, (int*)&Height, (int*)&Channels);
    if (data == 0)
    {
        LogManager::DebugPrint("Load Fail " + filePath);
        return;
    }

    buildResourceWithData(data);
#pragma message("TOFIX InitAsShaderResource will copy data")
    //FreeData(data);
}

void Image::LoadFromBuffer(void* buffer, int width, int height, int channels)
{
    Width = width;
    Height = height;
    Channels = channels;
    buildResourceWithData(buffer);
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

void Image::buildResourceWithData(void* data)
{
    if (PipelineResource)
    {
        delete PipelineResource;
    }
    PipelineResource = new GraphicsResource(Name, GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_PIXEL, GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT, false);
    PipelineResource->InitAsShaderResource(Width, Height, Channels, data, &isFinishBuild);
}
