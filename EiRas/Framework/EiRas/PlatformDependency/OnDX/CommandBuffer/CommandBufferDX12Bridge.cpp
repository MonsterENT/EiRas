#include "CommandBufferDX12Bridge.h"
#include "CommandBufferDX12.h"
#include <Material/Material.hpp>
#include <Material/MaterialLayout.hpp>
#include <PlatformDependency/OnDX/Material/MaterialDX12Bridge.h>
#include <PlatformDependency/OnDX/Material/GraphicsResourceHeapDX12.h>
#include <Mesh/Mesh.hpp>
#include <PlatformDependency/OnDX/Mesh/MeshDX12Bridge.h>
#include <PlatformDependency/OnDX/Mesh/MeshDX12.h>

using namespace Graphics;
using namespace MaterialSys;

CommandBufferDX12Bridge::CommandBufferDX12Bridge(std::string Name)
{
    raw_obj = new CommandBufferDX12(Name);
}

void CommandBufferDX12Bridge::BeginFrame()
{
    ((CommandBufferDX12*)raw_obj)->BeginFrame();
}

void CommandBufferDX12Bridge::Reset(EiRasPlatformBridgeProtocol* heapBridge)
{
    ((CommandBufferDX12*)raw_obj)->Reset((GraphicsResourceHeapDX12*)heapBridge->raw_obj);
}

void CommandBufferDX12Bridge::Commit(bool present)
{
    ((CommandBufferDX12*)raw_obj)->Commit(present);
}

void CommandBufferDX12Bridge::SetMaterial(Material* mat)
{
    CommandBufferDX12* obj = (CommandBufferDX12*)raw_obj;
    obj->SetPipelineState((MaterialDX12*)mat->PlatformBridge->raw_obj, &mat->LayoutProps, &mat->LayoutTables);
}

void CommandBufferDX12Bridge::DrawMesh(MaterialSys::Mesh* mesh)
{
    CommandBufferDX12* obj = (CommandBufferDX12*)raw_obj;
    obj->DrawMesh((MeshDX12*)mesh->PlatformBridge->raw_obj);
}