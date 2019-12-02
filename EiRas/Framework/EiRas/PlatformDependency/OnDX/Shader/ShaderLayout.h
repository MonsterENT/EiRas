#pragma once

#include <d3d12.h>
#include <PlatformDependency/OnDX/d3dx12.h>
#include <PlatformDependency/OnDX/Shader/ShaderResource/ConstantBufferDX12.h>
#include <PlatformDependency/OnDX/Shader/ShaderResource/ShaderResourceDX12.h>
#include <PlatformDependency/OnDX/Shader/ShaderResource/ShaderResourceHeapDX12.h>

#include <string>

namespace MaterialSys
{
    enum class ShaderSlotType
    {
        Prop = 0,
        Table = 1
    };
    
    class ShaderSlot
    {
    public:
        std::string SlotName;
        int SlotID;
        ShaderSlotType SlotType;

        ResourceDX12* Resource;
        ShaderResourceHeapDX12* ResourceHeap;

        virtual void* buildResource(void* srcPtr)
        {
            Resource = nullptr;
            return nullptr;
        }
        virtual void buildResourceHeap(void**)
        {
            ResourceHeap = nullptr;
        }
        virtual void* Copy()
        {
            ShaderSlot* ptr = new ShaderSlot();
            ptr->SlotType = this->SlotType;
            return ptr;
        }
    };

    class ShaderProp : public ShaderSlot
    {
    public:
        D3D12_DESCRIPTOR_RANGE_TYPE PropType;

        void* ResMappingSrcPtr;
        UINT8* ResMappingDestPtr;

        //For CBV
        UINT _CBV_SIZE;

        virtual void* buildResource(void* srcPtr)
        {
            if (PropType == D3D12_DESCRIPTOR_RANGE_TYPE_CBV)
            {
                this->Resource = new ConstantBufferDX12(this->_CBV_SIZE);
                CD3DX12_RANGE range(0, 0);
                this->Resource->Resource->Map(0, &range, (void**)&ResMappingDestPtr);
                this->ResMappingSrcPtr = srcPtr;
            }
            return this->Resource;
        }

        virtual void* Copy()
        {
            ShaderProp* ptr = new ShaderProp();
            ptr->PropType = this->PropType;
            ptr->_CBV_SIZE = this->_CBV_SIZE;
            return ptr;
        }

    };

    class ShaderTable : public ShaderSlot
    {
    public:
        UINT PropNum;
        ShaderProp** Props;

        ShaderTable(UINT propNum)
        {
            PropNum = propNum;
            Props = new ShaderProp * [propNum];
            SlotType = ShaderSlotType::Table;
        }

        virtual void buildResourceHeap(ResourceDX12** resArray)
        {
            this->ResourceHeap = new ShaderResourceHeapDX12(PropNum, resArray, PropNum);
        }

        virtual void* Copy()
        {
            ShaderTable* ptr = new ShaderTable(this->PropNum);
            ptr->PropNum = this->PropNum;
            ptr->Props = new ShaderProp * [this->PropNum];
            for (int i = 0; i < this->PropNum; i++)
            {
                ptr->Props[i] = (ShaderProp*)this->Props[i]->Copy();
            }
            return ptr;
        }
    };

    class ShaderLayout
    {
    public:
        UINT SlotNum;
        ShaderSlot** Slots;
        ID3D12RootSignature* rootSignature;

        ShaderLayout* Copy()
        {
            ShaderLayout* ptr = new ShaderLayout();
            ptr->SlotNum = this->SlotNum;
            ptr->Slots = new ShaderSlot * [this->SlotNum];
            for (int i = 0; i < ptr->SlotNum; i++)
            {
                ptr->Slots[i] = (ShaderSlot*)this->Slots[i]->Copy();
            }
            return ptr;
        }
    };
}