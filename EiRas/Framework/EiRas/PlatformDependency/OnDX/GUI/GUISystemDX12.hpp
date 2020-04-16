#ifndef GUI_SYSTEM_DX12_HPP
#define GUI_SYSTEM_DX12_HPP
#include <Math/Math.hpp>

namespace GUISys
{
    class GUISystemDX12
    {
    public:
        void RunLoopInvoke(void* msg);

    private:
        Math::float2 _MouseUVPos;

    protected:
    };
}

#endif