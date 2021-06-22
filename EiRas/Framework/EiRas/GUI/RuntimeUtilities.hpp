#ifndef Runtime_Utilities_Hpp
#define Runtime_Utilities_Hpp

#include <string>
#include <Material/Material.hpp>
#include <Material/Shader.hpp>
#include <Graphics/CommandBuffer.hpp>
#include <Graphics/GraphicsVertexDescriptor.hpp>
#include <Material/ShaderLayout.h>
using namespace MaterialSys;
using namespace Graphics;

namespace GUISys
{
    class RuntimeUtilities
    {
    public:
        static Shader* GetGUIDefaultShader();
        static Material* GetGUIDefaultMaterial();
        static Material* CreateGUIDefaultMaterial(std::string name);

        static Shader* GetFontShader();
        static Material* CreateFontMaterial(std::string name);

        static ShaderLayout* GetDefaultShaderLayout();
        static GraphicsVertexDescriptor* GetDefaultVertexDesc();

    private:
        static Material* _GUIDefaultMaterial;
        static Shader* _GUIDefaultShader;

        static Shader* _FontShader;

        static GraphicsVertexDescriptor* _DefaultVertexDesc;
        static ShaderLayout* _DefaultShaderLayout;
    };
}

#endif