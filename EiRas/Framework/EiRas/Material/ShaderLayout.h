#pragma once
#include <string>

#include <Material/MaterialLayout.hpp>
#include <Material/GraphicsResource.hpp>

namespace MaterialSys
{
    typedef 
    enum class ShaderSlotType
    {
        ShaderSlotType_Prop = 0,
        ShaderSlotType_Table = 1
    } ShaderSlotType;
    
    class ShaderSlot
    {
    public:
        ShaderSlotType SlotType;
    };

    class ShaderProp : public ShaderSlot
    {
    public:
        std::string PropName;
        GraphicsResourceType PropType;
        int BufferSize;
    };

    class ShaderTable : public ShaderSlot
    {
    public:
        int PropNum;
        ShaderProp** Props;

        ShaderTable(int propNum)
        {
            PropNum = propNum;
            Props = new ShaderProp * [propNum];
            SlotType = ShaderSlotType::ShaderSlotType_Table;
        }
    };

    class ShaderLayout
    {
    public:
        int SlotNum;
        ShaderSlot** Slots;
    };
}