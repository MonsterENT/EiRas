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
#include <FileSys/FileManager.hpp>
#include <Material/Shader.hpp>
#include <Material/ShaderLayout.h>
#include <Graphics/GraphicsVertexDescriptor.hpp>
#pragma comment (lib, "D3DCompiler.lib")

using namespace Graphics;
using namespace MaterialSys;

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
        ID3DBlob* errMsg = NULL;
        HRESULT hr = D3DCompileFromFile(tmp_ws, 0, D3D_COMPILE_STANDARD_FILE_INCLUDE, fnName, target, 0, 0, &shader, &errMsg);
        if (errMsg != NULL)
        {
#pragma warning("TODO")
            char* msgCharData = new char[errMsg->GetBufferSize()];
            memcpy(msgCharData, errMsg->GetBufferPointer(), errMsg->GetBufferSize());
            delete[] msgCharData;
        }
        assert(SUCCEEDED(hr));
        return SUCCEEDED(hr);
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
            subMesh->IndexBufferStartIdx = 0;
            subMesh->IndexCount = 3;

            _FullScreenTriangle->SetVertexData(new Math::float3[3]{ {-1, -1, 0}, {-1, 3, 0}, {3, -1, 0} },
                new Math::float2[3]{ {0, 0}, {0, 0}, {0, 0} },
                3);

            _FullScreenTriangle->SetIndexData(new _uint[3]{ 0, 1, 2 }, 3);
            _FullScreenTriangle->BuildBuffer(MeshSys::MeshType::VertexInput2D, true);
        }
        return _FullScreenTriangle;
    }

    static MaterialSys::Shader* _CopyStd = 0;
    static MaterialSys::Shader* CopyStd()
    {
        if (_CopyStd == 0)
        {
            ShaderLayout* layout = new ShaderLayout(1);
            ShaderTable* table = new ShaderTable();
            table->AddProp(-1, "_MainTex", GraphicsResourceType::SRV, GraphicsResourceVisibility::VISIBILITY_ALL, GraphicsResourceUpdateFreq::UPDATE_FREQ_ONINIT);
            layout->Slots[0] = table;
            layout->BuildOnDX12();

            //Graphics::GraphicsVertexDescriptor* m_vertexDesc = new Graphics::GraphicsVertexDescriptor();
            //m_vertexDesc->AddBufferAttribute("POSITION", GraphicsVertexAttributeFormat::VertexFormatFloat3, 0);
            //m_vertexDesc->InitBufferLayout();

            GraphicsVertexDescriptor* m_vertexDesc2 = new GraphicsVertexDescriptor();
            m_vertexDesc2->AddBufferAttribute("POSITION", GraphicsVertexAttributeFormat::VertexFormatFloat2, 0);
            m_vertexDesc2->AddBufferAttribute("TEXCOORD", GraphicsVertexAttributeFormat::VertexFormatFloat2, 0);
            m_vertexDesc2->InitBufferLayout();

            std::string filePath = FileSys::FileManager::shareInstance()->GetResourcePath("Shader\\DX\\CopyStd", "hlsl");
            _CopyStd = new MaterialSys::Shader(filePath, "vs_main_0", "ps_main");
            //_CopyStd->AddVertexFuncToPass("vs_main_1", 1);
            //_CopyStd->SetPixelFuncToPass(0, 1);
            _CopyStd->InitVertexDescriptor(m_vertexDesc2);
            //_CopyStd->InitVertexDescriptor(m_vertexDesc2, 1, false);

            _CopyStd->SetLayout(layout);
            //delete m_vertexDesc;
        }
        return _CopyStd;
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