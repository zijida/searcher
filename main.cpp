#include "main.h"
#include "include/uri.h"
// a sample exported function
void DLL_EXPORT SomeFunction(const LPCSTR sometext)
{
    MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
}

void DLL_EXPORT test()
{
    http::uri u;
    u.convert(
              "http://222.36.28.38:82/down/NAV2010.zip",
              "/xgmm/link?url=yxDx1aNSC7CrHuhBexcWOCIDlzudu4vzLDNtpq3IASzf_yVKG3LuSgFsC3MxynJ9MCdA_YRoJ5HFaLkD5Yvngq");
    cout<<u.whole()<<endl;
    cout<<"domain: "<<u.host<<endl;
    cout<<"path: "<<u.path<<endl;
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
