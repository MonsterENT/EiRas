#ifndef Material_Layout_hpp
#define Material_Layout_hpp

#include <Material/GraphicsResource.hpp>
#include <Material/GraphicsResourceHeap.hpp>
#include <string>
#include <Global/GlobalDefine.h>

namespace MaterialSys
{
    typedef enum MaterialSlotType
    {
        MaterialSlotType_Prop = 0,
        MaterialSlotType_Table = 1
    } MaterialSlotType;

    class MaterialSlot
    {
    public:
        _uint SlotID;
        MaterialSlotType SlotType;
    };

    class MaterialProp : public MaterialSlot
    {
    public:
        std::string Name;
        GraphicsResource* Resource;
        MaterialProp(std::string name, GraphicsResourceType propType, GraphicsResourceVisibility visible, GraphicsResourceUpdateFreq updateFreq, bool initResource, _uint bufferSize)
        {
            Name = name;
            Resource = new GraphicsResource(name, propType, visible, updateFreq, initResource);
            Resource->InitAsConstantBuffer(bufferSize);
        }
    };

    class MaterialTable : public MaterialSlot
    {
    public:
        _uint PropNum;
        MaterialProp** Props;
        MaterialTable(_uint propNum, MaterialProp** matProps)
        {
            PropNum = propNum;
            this->Props = matProps;
        }
    };

    class MaterialLayout
    {
    public:
        _uint SlotNum;
        MaterialSlot** Slots;

        MaterialLayout(_uint slotNum)
        {
            SlotNum = slotNum;
            Slots = new MaterialSlot*[SlotNum];
        }
    };

}

#endif
