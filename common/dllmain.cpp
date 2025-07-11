#include <Windows.h>

extern "C" { 
    #include "proxydll.h" 
}
#include "chainload.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
#ifdef _DEBUG
        while (!IsDebuggerPresent())
            Sleep(100);
#endif
        DisableThreadLibraryCalls(hModule);
        real_dll_init();
        chainload(hModule);
        break;
    case DLL_PROCESS_DETACH:
        if (!lpReserved)
            real_dll_free();
        break;
    default:
        break;
    }
    return TRUE;
}
