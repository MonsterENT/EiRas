#ifndef EventBase_Hpp
#define EventBase_Hpp

namespace GUISys
{
    class EventBase
    {
    public:
        EventBase();
        virtual void Invoke()
        {
        }
    };
}

#endif
