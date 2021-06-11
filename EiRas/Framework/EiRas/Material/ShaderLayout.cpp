#include <Material/ShaderLayout.h>

#if GRAPHICS_DX
#include <PlatformDependency/OnDX/Shader/ShaderLayoutDX12Bridge.hpp>
#endif

using MaterialSys::ShaderLayout;

ShaderLayout::ShaderLayout(_uint slotNum)
{
    SlotNum = slotNum;
    Slots = new ShaderSlot * [slotNum];
    PlatformBridge = 0;
}

void ShaderLayout::BuildOnDX12()
{
#if GRAPHICS_DX
    PlatformBridge = new ShaderLayoutDX12Bridge();
    ((ShaderLayoutDX12Bridge*)PlatformBridge)->Build(this);
#endif
}

ShaderLayout::~ShaderLayout()
{
    delete PlatformBridge;
    PlatformBridge = 0;
}