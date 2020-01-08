#pragma once
#include <EiRas/PlatformDependency/OnDX/DX12Utils.h>
#include <EiRas/Global/GlobalDefine.h>

namespace FileSys
{
    class FileManagerWin
    {
    public:
        static char* GetResourcePath()
        {
#pragma message("TOFIX")
            if (tmpResourcePath == 0)
            {
                std::string tmp = "E://EiRasWorkspace//EiRas/EiRas//SampleBuild/Common//Resource//";
                tmpResourcePath = new char[150];
                memcpy(tmpResourcePath, tmp.c_str(), 150 * sizeof(char));
                //DX12Utils::g_getAssetsPath(tmpResourcePath, 150);
                tmpResourcePathLen = strlen(tmpResourcePath) * sizeof(char);
            }

            return tmpResourcePath;
        }

        static _uint GetResourcePathLen()
        {
            return tmpResourcePathLen;
        }
    private:
        static char* tmpResourcePath;
        static _uint tmpResourcePathLen;
    };
}