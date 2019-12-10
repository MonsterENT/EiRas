#include "GraphicsResourceHeapDX12Bridge.h"
#include "GraphicsResourceHeapDX12.h"
#include <Material/MaterialLayout.hpp>
using namespace MaterialSys;

GraphicsResourceHeapDX12Bridge::GraphicsResourceHeapDX12Bridge(int propCount, int tableCount, MaterialTable** tableArray)
{
    raw_obj = new GraphicsResourceHeapDX12(propCount, tableCount, tableArray);
}