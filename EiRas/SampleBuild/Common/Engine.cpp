#include "Engine.hpp"
#include <Material/ShaderLayout.h>
#include <GraphicsAPI/EiRas.hpp>
#include <Graphics/CommandBuffer.hpp>
#include <Material/Material.hpp>
#include <Material/Shader.hpp>
#include <Mesh/Mesh.hpp>

using namespace MaterialSys;
using namespace Graphics;
using namespace GraphicsAPI;
using namespace MeshSys;

void Engine::m_initEngine()
{
    cmdBuffer = new CommandBuffer("main buffer");

    ShaderLayout* layout = new ShaderLayout();
    layout->SlotNum = 1;

    ShaderProp* commonCb0 = new ShaderProp();
    commonCb0->BufferSize = sizeof(float) * 4;
    commonCb0->PropName = "CommonCB0";
    commonCb0->PropType = GraphicsResourceType::CBV;
    commonCb0->SlotType = ShaderSlotType::ShaderSlotType_Prop;

    layout->Slots = new ShaderSlot*[1];
    layout->Slots[0] = commonCb0;

    shader = new Shader("shaders.hlsl", "VSMain", "PSMain");
    shader->InitLayout(layout);
    mat = new Material("material", shader, cmdBuffer);
    static XMFLOAT4 tmpCol;
    tmpCol.x = 1;
    tmpCol.y = 1;
    tmpCol.z = 0;
    tmpCol.w = 1;
    mat->SetProperty(0, &tmpCol);
    mesh = new Mesh("mesh");
}

Engine::Engine()
{
}

Engine::~Engine()
{
}

#if GRAPHICS_DX
void Engine::InitEngine(HWND hWnd, _uint width, _uint height)
{
    device = EiRas::Create(hWnd, 1024, 1080);
    m_initEngine();
}
#endif

#if GRAPHICS_METAL
void Engine::InitEngine()
{
    device = EiRas::Create();
    m_initEngine();
}
#endif

void Engine::Update()
{
    cmdBuffer->BeginFrame();
    cmdBuffer->Reset();
    cmdBuffer->SetMaterial(mat);
    cmdBuffer->DrawMesh(mesh);
    cmdBuffer->Commit(true);
}
