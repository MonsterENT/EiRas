#ifndef Response_Hpp
#define Response_Hpp
#include <Math/Math.hpp>

namespace GUISys
{
    typedef void (*GUI_CALLBACK_FUNC)(void* data);

    class ResponseDataBase
    {
    public:
        void* UserData;
    };

    class ResponseDataEvent : public ResponseDataBase
    {
    public:
        Math::float2 MouseClickNDCPos;
    };

    class Response
    {
    public:

        Response()
        {
            _CallBack = nullptr;
            UserData = nullptr;
        }

        Response(GUI_CALLBACK_FUNC callBack, void* userData)
        {
            _CallBack = callBack;
            UserData = userData;
        }

        void SetCallBack(GUI_CALLBACK_FUNC callBack)
        {
            _CallBack = callBack;
        }

        void InvokeWithData(ResponseDataBase* data)
        {
            data->UserData = UserData;
            if (_CallBack != nullptr)
            {
                _CallBack(data);
            }
        }

    private:
        GUI_CALLBACK_FUNC _CallBack;
        void* UserData;
    };
}

#endif