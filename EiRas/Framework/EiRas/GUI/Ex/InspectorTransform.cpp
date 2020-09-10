#include "InspectorTransform.hpp"
#include <Basic/TransformSys.hpp>
#include "../Label.hpp"
#include <FontSys/FontSys.hpp>
using namespace GUISys;
using namespace FontSys;
using namespace BasicComponent;

InspectorTransform::InspectorTransform(BasicComponent::TransformSys* transform)
{
    _TransformObj = transform;

    _PosX = new Label();
    _PosX->SetFrame(Math::rect_float(0, 0, 500, 100));
}

void InspectorTransform::Invoke()
{
    
    //std::string t_str = std::to_string(_TransformObj->Position.x);
    char r_str[20];
    sprintf(r_str, "PositionX%.0fY%.0fZ%.0f", _TransformObj->Position.x, _TransformObj->Position.y, _TransformObj->Position.z);
    if (Font::GetDefaultFont()->GetText(r_str, &_PosXTextObj, 100))
    {
        _PosX->SetText(&_PosXTextObj);
    }
}