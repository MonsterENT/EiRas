#pragma once
#include <string>
#include <PlatformDependency/OnDX/Shader/ShaderDX12.h>
#include <PlatformDependency/OnDX/GraphicsAPI/EiRasDX12.h>
#include <Math/Math.hpp>
#include <Mesh/Mesh.hpp>
#include <Material/GraphicsResource.hpp>
#include <Graphics/RenderTexture.hpp>
#include <Graphics/CommandBuffer.hpp>
#include <Material/Material.hpp>
#pragma comment (lib, "D3DCompiler.lib")

namespace DX12Utils
{
    static inline void g_getAssetsPath(_Out_writes_(pathSize) CHAR* path, UINT pathSize)
    {
        if (path == nullptr)
        {
            return;
        }

        DWORD size = GetModuleFileNameA(nullptr, path, pathSize);
        if (size == 0 || size == pathSize)
        {
            return;
        }

        char* lastSlash = strrchr(path, L'\\');
        if (lastSlash)
        {
            *(lastSlash + 1) = L'\0';
        }
    }

    static bool g_compileShader(LPCSTR filePath, LPCSTR fnName, LPCSTR target, ID3DBlob*& shader)
    {
        wchar_t tmp_ws[128];
        swprintf(tmp_ws, 128, L"%hs", filePath);
        return SUCCEEDED(D3DCompileFromFile(tmp_ws, 0, 0, fnName, target, 0, 0, &shader, 0));
    }

    static MeshSys::Mesh* _FullScreenTriangle = 0;
    static MeshSys::Mesh* FullScreenTriangle()
    {
        if (_FullScreenTriangle == 0)
        {
            _FullScreenTriangle = new MeshSys::Mesh("Full Screen Triangle");
            _FullScreenTriangle->SubMeshCount = 1;
            MeshSys::SubMesh* subMesh = new MeshSys::SubMesh();
            _FullScreenTriangle->SubMeshes = subMesh;
            subMesh->UVData = new Math::float2[3]{ {0, 0}, {0, 0}, {0, 0}};
            subMesh->NormalData = new Math::float3[3]{ {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
            subMesh->IndicesCount = 3;
            subMesh->VerticesCount = 3;
            subMesh->IndicesData = new _uint[3]{ 0, 1, 2 };
            subMesh->PositionData = new Math::float3[3]{ {-1, -1, 0}, {-1, 3, 0}, {3, -1, 0} };
            _FullScreenTriangle->BuildBuffer();
        }
        return _FullScreenTriangle;
    }

    static void BlitFullScreen(MaterialSys::GraphicsResource* src, Graphics::RenderTexture* dest, Graphics::CommandBuffer* cmdBuffer, MaterialSys::Material* mat, _uint pass = 0)
    {
        cmdBuffer->SetRenderTexture(dest);
        mat->SetProperty(src, 0, 0);
        mat->FinishStateChange();
        cmdBuffer->SetMaterial(mat, pass);
        cmdBuffer->DrawMesh(FullScreenTriangle());
    }

    static void BlitFullScreen(Graphics::RenderTexture* src, Graphics::RenderTexture* dest, Graphics::CommandBuffer* cmdBuffer, MaterialSys::Material* mat, _uint pass = 0)
    {
        cmdBuffer->SetRenderTexture(dest);
        mat->SetProperty(src, 0, 0);
        mat->FinishStateChange(pass);
        cmdBuffer->SetMaterial(mat, pass);
        cmdBuffer->DrawMesh(FullScreenTriangle());
    }
}