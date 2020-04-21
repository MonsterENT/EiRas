#ifndef GUI_SYSTEM_DX12_HPP
#define GUI_SYSTEM_DX12_HPP
#include <Math/Math.hpp>
#include <GUI/Response.hpp>

namespace GUISys
{
    class GUISystemDX12
    {
    public:
        void RunLoopInvoke(void* msg);
        void SetEventResponse(Response* response)
        {
            _EventResponse = response;
        }

    protected:

    private:
        ResponseDataEvent _EventCommonData;
        Response* _EventResponse;
    };
}

#endif