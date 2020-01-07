#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <Global/PlatformDefine.h>
#include <Global/GlobalDefine.h>
#if GRAPHICS_DX
#include <Windows.h>
#endif
#include <string>

namespace Graphics
{
    class CommandBuffer;
}

namespace GraphicsAPI
{
    class EiRas;
}

namespace MaterialSys
{
    class Material;
    class Shader;
}

namespace MeshSys
{
    class Mesh;
}

class Engine
{
public:
    Engine();

#if GRAPHICS_DX
    void InitEngine(HWND hWnd, _uint width, _uint height);
#endif

#if GRAPHICS_METAL
    void InitEngine();
#endif

    void Update();

    ~Engine();

private:
    void m_initEngine();
    GraphicsAPI::EiRas* device;
    MaterialSys::Material* mat;
    MaterialSys::Shader* shader;
    Graphics::CommandBuffer* cmdBuffer;
    MeshSys::Mesh* mesh;
};
#endif
