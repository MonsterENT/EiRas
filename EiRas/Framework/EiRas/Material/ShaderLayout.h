#pragma once
#include <string>

#include <Material/MaterialLayout.hpp>
#include <Material/GraphicsResource.hpp>

namespace MaterialSys
{
    typedef 
    enum ShaderSlotType
    {
        ShaderSlotType_Prop = 0,
        ShaderSlotType_Table = 1
    } ShaderSlotType;
    
    class ShaderSlot
    {
    public:
        ShaderSlotType SlotType;

        //ResourceDX12* Resource;
        //ShaderResourceHeapDX12* ResourceHeap;

        //virtual void* buildResource(void* srcPtr)
        //{
        //    Resource = nullptr;
        //    return nullptr;
        //}
        //virtual void buildResourceHeap(void**)
        //{
        //    ResourceHeap = nullptr;
        //}
        //virtual void* Copy()
        //{
        //    ShaderSlot* ptr = new ShaderSlot();
        //    ptr->SlotType = this->SlotType;
        //    return ptr;
        //}
    };

    class ShaderProp : public ShaderSlot
    {
    public:
        std::string PropName;
        int PropID;
        GraphicsResourceType PropType;
        int BufferSize;
        //D3D12_DESCRIPTOR_RANGE_TYPE PropType;

        //void* ResMappingSrcPtr;
        //UINT8* ResMappingDestPtr;

        ////For CBV
        //int _CBV_SIZE;

        //virtual void* buildResource(void* srcPtr)
        //{
        //    if (PropType == D3D12_DESCRIPTOR_RANGE_TYPE_CBV)
        //    {
        //        this->Resource = new ConstantBufferDX12(this->_CBV_SIZE);
        //        CD3DX12_RANGE range(0, 0);
        //        this->Resource->Resource->Map(0, &range, (void**)&ResMappingDestPtr);
        //        this->ResMappingSrcPtr = srcPtr;
        //    }
        //    return this->Resource;
        //}
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

       /* virtual void buildResourceHeap(ResourceDX12** resArray)
        {
            this->ResourceHeap = new ShaderResourceHeapDX12(PropNum, resArray, PropNum);
        }*/
    };

    class ShaderLayout
    {
    public:
        int SlotNum;
        ShaderSlot** Slots;
    };
}