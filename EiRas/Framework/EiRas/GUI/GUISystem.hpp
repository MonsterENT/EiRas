#ifndef GUI_SYSTEM_HPP
#define GUI_SYSTEM_HPP

#include <Global/GlobalDefine.h>
#include <Global/PlatformDependency/EiRasPlatformBridgeProtocol.h>
#include <Math/Math.hpp>
#include <vector>

namespace MaterialSys
{
    class Material;
    class Shader;
}

namespace Graphics
{
    class CommandBuffer;
}

namespace GUISys
{
    class GUIBase;
    class View;
    class GUISystem
    {
        friend GUIBase;
        friend View;
    public:
        static GUISystem* CreateSystem(_uint width, _uint height, Graphics::CommandBuffer* cmdBuffer);
        static GUISystem* SharedInstance();
        GUISystem(_uint width, _uint height, Graphics::CommandBuffer* cmdBuffer);
        void RunLoopInvoke(void* msg);

        EiRasPlatformBridgeProtocol* PlatformBridge;

    protected:
        _uint _Height, _Width;

        Graphics::CommandBuffer* _CmdBuffer;
        void FrameToNDC(Math::rect_float frame, Math::rect_float& NDC);
        void RegGUIComponent(GUIBase* comp);

        std::vector<GUIBase*> _RegedGUIComp;
        static MaterialSys::Material* SharedMaterial;
        static MaterialSys::Shader* DefaultShader;
    };
}

#endif