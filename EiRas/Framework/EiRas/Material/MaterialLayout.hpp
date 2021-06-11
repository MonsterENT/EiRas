#ifndef Material_Layout_hpp
#define Material_Layout_hpp

#include <Material/GraphicsResource.hpp>
#include <string>
#include <vector>
#include <Global/GlobalDefine.h>

namespace MaterialSys
{
    typedef enum class MaterialSlotType
    {
        MaterialSlotType_Prop = 0,
        MaterialSlotType_Table = 1,
        MaterialSlotType_Builtin_ViewProj = 2,
        MaterialSlotType_Ref_WorldMatrix = 3,
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
        GraphicsResource* _oriResource;

        MaterialProp(std::string name, GraphicsResourceType propType, GraphicsResourceVisibility visible, GraphicsResourceUpdateFreq updateFreq, bool initResource, int bufferSize)
        {
            Name = name;
            if (propType == GraphicsResourceType::SRV)
            {
                if (bufferSize > 0)
                {
                    Resource = new GraphicsResource(name, propType, visible, updateFreq, initResource);
                    Resource->InitAsShaderResource(bufferSize);
                    _oriResource = Resource;
                }
                else
                {
                    Resource = NULL;
                    _oriResource = NULL;
                }
            }
            else
            {
                Resource = new GraphicsResource(name, propType, visible, updateFreq, initResource);
                Resource->InitAsConstantBuffer(bufferSize);
                _oriResource = Resource;
            }
            this->SlotType = MaterialSlotType::MaterialSlotType_Prop;
        }

        ~MaterialProp()
        {
#pragma warning("Resource should use Reference Count")
            if (_oriResource)
            {
                delete _oriResource;
                _oriResource = 0;
            }

            Resource = 0;
        }

        void SetRawResObject(GraphicsResource* rawResObj)
        {
            if (rawResObj == NULL)
            {
                Resource = _oriResource;
            }
            else
            {
                Resource = rawResObj;
            }
        }

        void InitHeapOffset(_uint offset)
        {
            _oriHeapOffset = offset;
            _heapOffset = offset;
        }

        void RevertHeapOffset()
        {
            _heapOffset = _oriHeapOffset;
        }

        _uint _heapOffset;
    private:
        _uint _oriHeapOffset;
    };

    class MaterialTable : public MaterialSlot
    {
    public:
        _uint PropNum;
        MaterialProp** Props;
        MaterialTable(_uint propNum, std::vector<MaterialProp*> matProps)
        {
            PropNum = propNum;
            this->Props = new MaterialProp*[PropNum];
            for (_uint i = 0; i < PropNum; i++)
            {
                this->Props[i] = matProps[i];
            }
            this->SlotType = MaterialSlotType::MaterialSlotType_Table;
        }

        ~MaterialTable()
        {
            if (Props)
            {
                for (int i = 0; i < PropNum; i++)
                {
                    delete Props[i];
                }
                Props = 0;
            }
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
            if (SlotNum > 0)
            {
                Slots = new MaterialSlot * [SlotNum];
            }
            else
            {
                Slots = NULL;
            }
        }
        ~MaterialLayout()
        {
            if (Slots)
            {
                for (int i = 0; i < SlotNum; i++)
                {
                    delete Slots[i];
                }

                delete[] Slots;
                Slots = 0;
            }
        }
    };

}

#endif