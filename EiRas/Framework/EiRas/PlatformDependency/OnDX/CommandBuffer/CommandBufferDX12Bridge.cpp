#include "CommandBufferDX12Bridge.h"
#include "CommandBufferDX12.h"
#include <Material/Material.hpp>
#include <Material/MaterialLayout.hpp>
#include <PlatformDependency/OnDX/Material/MaterialDX12Bridge.h>

using Graphics::CommandBufferDX12;
using Graphics::CommandBufferDX12Bridge;

using namespace MaterialSys;

CommandBufferDX12Bridge::CommandBufferDX12Bridge(std::string name)
{
    raw_obj = new CommandBufferDX12(name);
}

void CommandBufferDX12Bridge::SetMaterial(Material* mat)
{
    CommandBufferDX12* obj = (CommandBufferDX12*)raw_obj;
    obj->SetPipelineState((MaterialDX12*)mat->PlatformBridge->raw_obj, &mat->LayoutProps, &mat->LayoutTables);
}
