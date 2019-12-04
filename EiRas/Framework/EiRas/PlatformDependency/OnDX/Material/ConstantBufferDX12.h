#ifndef EIRAS_CONSTANT_BUFFER
#define EIRAS_CONSTANT_BUFFER

#include <PlatformDependency/OnDX/Material/GraphicsResourceDX12.h>

namespace MaterialSys
{
    class ConstantBufferDX12 : public GraphicsResourceDX12
    {
    public:
        ConstantBufferDX12(UINT bufferSize);
        ~ConstantBufferDX12();

        UINT GetBufferSize();

    private:
        UINT bufferSize;
    };
}
#endif // !EIRAS_CONSTANT_BUFFER
