#ifndef InspectorTransform_Hpp
#define InspectorTransform_Hpp
#include "Inspector.hpp"
#include <FontSys/FontSys.hpp>

namespace BasicComponent
{
    class TransformSys;
}

namespace GUISys
{
    class View;
    class Label;
    class InspectorTransform : public Inspector
    {
    public:
        InspectorTransform(BasicComponent::TransformSys* transform);
        virtual void Invoke();

    private:
        BasicComponent::TransformSys* _TransformObj;
        Label* _PosX, *_PosY, *_PosZ;
        FontSys::Text _PosXTextObj, _PosYTextObj, _PosZTextObj;

    };
}

#endif