#include "InspectorTransform.hpp"
#include <Basic/TransformSys.hpp>
#include "../Label.hpp"
#include <FontSys/FontSys.hpp>
using namespace GUISys;
using namespace FontSys;
using namespace BasicComponent;

InspectorTransform::InspectorTransform(BasicComponent::TransformSys* transform)
{
    Inspector::Inspector();
    _TransformObj = transform;

    _PosX = new Label();
    _PosX->SetFrame(Math::rect_float(0, 0, 100, 100));

}

void InspectorTransform::Invoke()
{
    if (Font::GetDefaultFont()->GetText(std::to_string(_TransformObj->Position.x), &_PosXTextObj))
    {
        _PosX->SetText(&_PosXTextObj);
    }
}