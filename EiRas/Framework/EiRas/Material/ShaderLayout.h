#pragma once
#include <string>
#include <vector>
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

        ShaderProp(std::string propName, GraphicsResourceType propType, GraphicsResourceVisibility visibility, GraphicsResourceUpdateFreq updateFreq, int bufferSize)
        {
            SlotType = ShaderSlotType::ShaderSlotType_Prop;

            PropName = propName;
            PropType = propType;
            Visibility = visibility;
            UpdateFreq = updateFreq;
            BufferSize = bufferSize;
        }
    };

    class ShaderPropRange
    {
    public:
        std::string BasePropName;
        GraphicsResourceType PropType;
        GraphicsResourceVisibility Visibility;
        GraphicsResourceUpdateFreq UpdateFreq;
        std::vector<int> BufferSizeList;
        _uint PropNum;

        ShaderPropRange(std::string basePropName, GraphicsResourceType propType, GraphicsResourceVisibility visibility, GraphicsResourceUpdateFreq updateFreq)
        {
            BasePropName = basePropName;
            PropType = propType;
            Visibility = visibility;
            UpdateFreq = updateFreq;
        }

        void AddProp(int bufferSize)
        {
            PropNum++;
            BufferSizeList.push_back(bufferSize);
        }
    };

    class ShaderTable : public ShaderSlot
    {
    public:
        std::vector<ShaderPropRange> Ranges;

        ShaderTable()
        {
            SlotType = ShaderSlotType::ShaderSlotType_Table;
        }

        void AddRange(ShaderPropRange range)
        {
            Ranges.push_back(range);
        }
    };

    class ShaderLayout
    {
    public:
        std::vector<ShaderSlot*> Slots;

        void AddSlot(ShaderSlot* slot)
        {

            Slots.push_back(slot);
        }
    };
}
