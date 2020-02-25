#ifndef EIRAS_CONSTANT_BUFFER
#define EIRAS_CONSTANT_BUFFER

#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>

namespace MaterialSys
{
    class ConstantBufferDX12 : public GraphicsResourceDX12
    {
    public:
        ConstantBufferDX12(UINT bufferSize, GraphicsResourceBehaviors* behaviors);
        ~ConstantBufferDX12();

    private:

    };
}
#endif // !EIRAS_CONSTANT_BUFFER
