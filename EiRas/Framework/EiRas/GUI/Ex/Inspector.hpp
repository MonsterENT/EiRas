#ifndef Inspector_Hpp
#define Inspector_Hpp
#include "../EventBase.hpp"

namespace GUISys
{
    class Inspector : public EventBase
    {
    public:
        Inspector();
        virtual void Invoke()
        {
        }
    };
}

#endif