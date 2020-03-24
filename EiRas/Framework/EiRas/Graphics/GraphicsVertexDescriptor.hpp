//
//  GraphicsVertexDescriptor.hpp
//  EiRasMetalBuild
//
//  Created by MonsterENT on 1/16/20.
//  Copyright © 2020 MonsterENT. All rights reserved.
//

#ifndef GraphicsVertexDescriptor_hpp
#define GraphicsVertexDescriptor_hpp


#include <Global/GlobalDefine.h>
#include <string>

namespace Graphics {

    enum class GraphicsVertexAttributeFormat
    {
        VertexFormatFloat = 28,
        VertexFormatFloat2 = 29,
        VertexFormatFloat3 = 30,
        VertexFormatFloat4 = 31,

        VertexFormatInt = 32,
        VertexFormatInt2 = 33,
        VertexFormatInt3 = 34,
        VertexFormatInt4 = 35,

        VertexFormatUInt = 36,
        VertexFormatUInt2 = 37,
        VertexFormatUInt3 = 38,
        VertexFormatUInt4 = 39,
    };

    _uint GraphicsVertexAttributeFormatSize(GraphicsVertexAttributeFormat format);

    _uint GraphicsVertexAttributeToDX12Format(GraphicsVertexAttributeFormat format);

    class GraphiceVertexLayout
    {
    public:
        _uint Stride;
    };

    class GraphiceVertexAttribute
    {
    public:
        std::string SemanticName;
        _uint Offset;
        _uint BufferIndex;
        GraphicsVertexAttributeFormat AttributeFormat;
    };

    class GraphicsVertexDescriptor
    {
    public:
        static const _uint MAX_ATTRIBUTE_COUNT = 10;
        static const _uint MAX_LAYOUT_COUNT = 3;

        _uint _LayoutIndex;
        _uint _AttributeIndex;

        GraphiceVertexAttribute* Attributes;
        GraphiceVertexLayout* Layouts;

        GraphicsVertexDescriptor()
        {
            _LayoutIndex = 0;
            _AttributeIndex = 0;

            Attributes = new GraphiceVertexAttribute[MAX_ATTRIBUTE_COUNT];
            Layouts = new GraphiceVertexLayout[MAX_LAYOUT_COUNT];
        }

        void InitBufferLayout()
        {
            if (_LayoutIndex < MAX_LAYOUT_COUNT && _AttributeIndex > 0)
            {
                Layouts[_LayoutIndex++].Stride = Attributes[_AttributeIndex - 1].Offset + GraphicsVertexAttributeFormatSize(Attributes[_AttributeIndex - 1].AttributeFormat);
            }
        }

        void AddBufferAttribute(std::string semanticName, GraphicsVertexAttributeFormat attributeFormat, _uint atBufferIndex)
        {
            if (_AttributeIndex < MAX_ATTRIBUTE_COUNT)
            {
                Attributes[_AttributeIndex].AttributeFormat = attributeFormat;
                Attributes[_AttributeIndex].BufferIndex = atBufferIndex;
                Attributes[_AttributeIndex].SemanticName = semanticName;
                if (_AttributeIndex == 0)
                {
                    Attributes[_AttributeIndex].Offset = 0;
                }
                else
                {
                    Attributes[_AttributeIndex].Offset = Attributes[_AttributeIndex - 1].Offset + GraphicsVertexAttributeFormatSize(Attributes[_AttributeIndex - 1].AttributeFormat);
                }

                _AttributeIndex++;
            }
        }

    private:
    };

}

#endif /* GraphicsVertexBufferDescriptor_hpp */
