#pragma once
#include <EiRas/PlatformDependency/OnDX/DX12Utils.h>
#include <EiRas/Global/GlobalDefine.h>

namespace FileSys
{
    class FileManagerWin
    {
    public:

        static char* GetProjectBasePath()
        {
            if (tmpProjectBasePath == 0)
            {
                tmpProjectBasePath = new char[MAX_STR_LEN];
                char* tmp = new char[MAX_STR_LEN];
                GetModuleFileNameA(NULL, tmp, MAX_STR_LEN);
                _uint len = strlen(tmp);
                memcpy(tmpProjectBasePath, tmp, len - BUILD_OFFSET);
                delete[] tmp;
                tmpProjectBasePath[len - BUILD_OFFSET] = '\0';
            }
            return tmpProjectBasePath;
        }

        ~FileManagerWin()
        {
            delete[] tmpProjectBasePath;
        }

    private:
        static char* tmpProjectBasePath;

        static const _uint MAX_STR_LEN = 150;

        static const _uint BUILD_OFFSET = 53;
    };
}