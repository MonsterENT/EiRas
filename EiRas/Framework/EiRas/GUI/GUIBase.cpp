#include "GUIBase.hpp"
#include <Mesh/Mesh.hpp>

using namespace MeshSys;
using namespace GUISys;

GUIBase::GUIBase()
{
    _Mesh = new MeshSys::Mesh("GUI Mesh");
}