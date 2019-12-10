#include "CommandBufferDX12Bridge.h"
#include "CommandBufferDX12.h"
#include <Material/Material.hpp>
#include <Material/MaterialLayout.hpp>
#include <PlatformDependency/OnDX/Material/MaterialDX12Bridge.h>
#include <PlatformDependency/OnDX/Material/GraphicsResourceHeapDX12.h>

using namespace Graphics;
using namespace MaterialSys;

CommandBufferDX12Bridge::CommandBufferDX12Bridge(std::string Name)
{
    raw_obj = new CommandBufferDX12(Name);
}

void CommandBufferDX12Bridge::BeginFrame(EiRasPlatformBridgeProtocol* heapBridge)
{
    ((CommandBufferDX12*)raw_obj)->BeginFrame((GraphicsResourceHeapDX12*)heapBridge->raw_obj);
}

void CommandBufferDX12Bridge::Commit()
{
    ((CommandBufferDX12*)raw_obj)->Commit();
}


void CommandBufferDX12Bridge::Present()
{
    ((CommandBufferDX12*)raw_obj)->Present();
}

void CommandBufferDX12Bridge::SetMaterial(Material* mat)
{
    CommandBufferDX12* obj = (CommandBufferDX12*)raw_obj;
    obj->SetPipelineState((MaterialDX12*)mat->PlatformBridge->raw_obj, &mat->LayoutProps, &mat->LayoutTables);
}
