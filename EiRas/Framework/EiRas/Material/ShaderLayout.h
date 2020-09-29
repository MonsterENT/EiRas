#pragma once
#include <string>
#include <vector>
#include <Material/MaterialLayout.hpp>
#include <Material/GraphicsResource.hpp>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Global/GlobalDefine.h>

namespace MaterialSys
{
    typedef 
    enum class ShaderSlotType
    {
        ShaderSlotType_Prop = 0,
        ShaderSlotType_Table = 1,
        ShaderSlotType_Builtin_ViewProj = 2,
        ShaderSlotType_Ref_WorldMatrix = 3,
    } ShaderSlotType;
    
    class ShaderSlot
    {
    public:
        ShaderSlotType SlotType;
    };

    class ShaderProp : public ShaderSlot
    {
    public:
        _uint RegisterIndex;
        _uint RegisterSpace;
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
        
        void InitRegisterSettings(_uint registerIndex, _uint registerSpace = 0)
        {
            RegisterIndex = registerIndex;
            RegisterSpace = registerSpace;
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

        _uint BaseRegisterIndex;
        _uint BaseRegisterSpace;
        bool RegisterSpaceLayoutMode;
        
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
        
        void InitBaseRegisterSettings(_uint baseRegisterIndex, _uint baseRegisterSpace = 0, bool regSpaceLayoutMode = false)
        {
            RegisterSpaceLayoutMode = regSpaceLayoutMode;
            BaseRegisterIndex = baseRegisterIndex;
            BaseRegisterIndex = baseRegisterSpace;
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
        _uint SlotNum;
        ShaderSlot** Slots;

        ShaderLayout(_uint slotNum);

        void BuildOnDX12();
        EiRasPlatformBridgeProtocol* PlatformBridge;
    private:
        
    };
}
