#include "ShaderLayoutDX12Bridge.hpp"
#include <Material/ShaderLayout.h>
#include "ShaderLayoutDX12.hpp"
using namespace MaterialSys;

void ShaderLayoutDX12Bridge::Build(ShaderLayout* layout)
{
    if (raw_obj == NULL)
    {
        raw_obj = new ShaderLayoutDX12();
    }
    ((ShaderLayoutDX12*)raw_obj)->Build(layout);
}