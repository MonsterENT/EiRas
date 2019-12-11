#ifndef Material_Layout_hpp
#define Material_Layout_hpp

#include <Material/GraphicsResource.hpp>
#include <Material/GraphicsResourceHeap.hpp>
#include <string>

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
        int SlotID;
        MaterialSlotType SlotType;
    };

    class MaterialProp : public MaterialSlot
    {
    public:
        std::string Name;
        GraphicsResourceType PropType;
        GraphicsResource* Resource;
        int BufferSize;
        MaterialProp(std::string Name, GraphicsResourceType propType, bool initResource, int bufferSize)
        {
            this->Name = Name;
            BufferSize = bufferSize;
            PropType = propType;
            Resource = new GraphicsResource(Name, PropType, initResource, bufferSize);
        }
    };

    class MaterialTable : public MaterialSlot
    {
    public:
        int PropNum;
        MaterialProp** Props;
        MaterialTable(int propNum, MaterialProp** matProps)
        {
            PropNum = propNum;
            this->Props = matProps;
        }
    };

    class MaterialLayout
    {
    public:
        int SlotNum;
        MaterialSlot** Slots;

        MaterialLayout(int slotNum)
        {
            SlotNum = slotNum;
            Slots = new MaterialSlot*[SlotNum];
        }
    };

}

#endif
