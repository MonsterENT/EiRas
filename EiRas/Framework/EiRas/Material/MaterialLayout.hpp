#ifndef Material_Layout_hpp
#define Material_Layout_hpp

#include <Material/GraphicsResource.hpp>
#include <Material/GraphicsResourceHeap.hpp>

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
        GraphicsResourceType PropType;
        GraphicsResource* Resource;
        int BufferSize;
        MaterialProp(GraphicsResourceType propType, int bufferSize)
        {
            BufferSize = bufferSize;
            PropType = propType;
            Resource = new GraphicsResource("111", PropType, bufferSize);
        }
    };

    class MaterialTable : public MaterialSlot
    {
    public:
        int PropNum;
        MaterialProp** Props;
        GraphicsResourceHeap* ResourceHeap;

        MaterialTable(int propNum, MaterialProp** matProps, GraphicsResource** resArray)
        {
            PropNum = propNum;
            this->Props = matProps;
            ResourceHeap = new GraphicsResourceHeap(PropNum, resArray);
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
