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
        GraphicsResourceVisibility Visibility;
        GraphicsResourceUpdateFreq UpdateFreq;
        int BufferSize;
    };

    class ShaderTable : public ShaderSlot
    {
    public:
        _uint PropNum;
        ShaderProp** Props;

        ShaderTable(_uint propNum)
        {
            PropNum = propNum;
            Props = new ShaderProp * [propNum];
            SlotType = ShaderSlotType::ShaderSlotType_Table;
        }
    };

    class ShaderLayout
    {
    public:
        _uint SlotNum;
        ShaderSlot** Slots;
    };
}
