#include "GraphicsResourceDX12.h"
#include <Material/GraphicsResource.hpp>

using MaterialSys::GraphicsResourceType;
using MaterialSys::GraphicsResourceDX12;

GraphicsResourceDX12::GraphicsResourceDX12()
{
    Resource = NULL;
    ResType = GraphicsResourceType::CBV;
}


GraphicsResourceDX12::~GraphicsResourceDX12()
{
}
