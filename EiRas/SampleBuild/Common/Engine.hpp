#ifndef ENGINE_HPP
#define ENGINE_HPP


#include <Global/GlobalDefine.h>
#if GRAPHICS_DX
#include <Windows.h>
#endif
#include <string>
#include <Math/Math.hpp>

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

    void Update(void* data);
    ~Engine();

    void KeyPressed(_uint param);
    Graphics::CommandBuffer* cmdBuffer;
private:
    void m_initEngine();
    GraphicsAPI::EiRas* device;
    MaterialSys::Material* _Mat0;
    MaterialSys::Shader* _BasicBRDFShader;

    MaterialSys::Material* _Mat2;
    MaterialSys::Shader* _BasicBRDFShader2;

    MeshSys::Mesh* _SF90Mesh;

    Math::int2 _ClientHW;
};
#endif
