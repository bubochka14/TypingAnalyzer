#include <windows.h>
#include <stdio.h>
HINSTANCE hinst;
HHOOK hhk;
typedef void (*argFunc)(/*int , WPARAM , LPARAM */);
static LPVOID lpvMem = NULL;      // pointer to shared memory
static argFunc arg;
static HANDLE hMapObject = NULL;  // handle to file mapping
#define MAPOBJ_SIZE  2048

BOOL WINAPI DllMain(__in  HINSTANCE hinstDLL,
    __in  DWORD fdwReason,
    __in  LPVOID lpvReserved
) {

    hinst = hinstDLL;
    LPVOID lpvData;
    BOOL fInit, fIgnore;
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        hMapObject = CreateFileMapping(
            INVALID_HANDLE_VALUE,   // use paging file
            NULL,                   // default security attributes
            PAGE_READWRITE,         // read/write access
            0,                      // size: high 32-bits
            MAPOBJ_SIZE,              // size: low 32-bits
            TEXT("dllmemfilemap")); // name of map object
        if (hMapObject == NULL)
            return FALSE;

        // The first process to attach initializes memory

        fInit = (GetLastError() != ERROR_ALREADY_EXISTS);

        // Get a pointer to the file-mapped shared memory

        lpvMem = MapViewOfFile(
            hMapObject,     // object to map view of
            FILE_MAP_WRITE, // read/write access
            0,              // high offset:  map from
            0,              // low offset:   beginning
            0);             // default: map entire file
        if (lpvMem == NULL)
            return FALSE;

        // Initialize memory if this is the first process

        if (fInit)
            memset(lpvMem, '\0', MAPOBJ_SIZE);
        break;

    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:

        break;
    case DLL_PROCESS_DETACH:

        // Unmap shared memory from the process's address space

        fIgnore = UnmapViewOfFile(lpvMem);

        // Close the process's handle to the file-mapping object

        fIgnore = CloseHandle(hMapObject);
        break;
    default:
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
LRESULT CALLBACK wireKeyboardProc(int code, WPARAM wParam, LPARAM lParam) {
    WCHAR szBuf[128];
    HDC hdc;
    if(code <0)
        return CallNextHookEx(0, code,
            wParam, lParam);
        FILE* fileLog = fopen("logger.txt", "a+");
        fprintf(fileLog, "OK");
        fclose(fileLog);
        printf("in");

    //argFunc* lpszTmp = (argFunc*)lpvMem;
    //argFunc f = *(++lpszTmp);
    //f();
    //  (f)(code,wParam,lParam);
    return CallNextHookEx(0, code, wParam, lParam);
}
#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif
    __declspec(dllexport) void install() {
        hhk = SetWindowsHookEx(WH_KEYBOARD_LL, wireKeyboardProc, hinst, NULL);
        printf("install");
    }
    __declspec(dllexport)  void uninstall() {
        UnhookWindowsHookEx(hhk);
    }
    __declspec(dllexport) HRESULT subscribe(argFunc f)
    {

        argFunc* lpszTmp;
        DWORD dwCount = 1;
        lpszTmp = (argFunc*)lpvMem;
        // Get the address of the shared memory block
        *(++lpszTmp) = f;
        lpszTmp = (argFunc*)lpvMem;
        argFunc fa = *(++lpszTmp);
        fa();
        //lpszTmp = (LPWSTR)lpvMem;
        //LPWSTR lpszBuf = (LPWSTR)f;
        // Copy the null-terminated string into shared memory

        //while (*lpszBuf && dwCount < SHMEMSIZE)
        //{
        //    *lpszTmp++ = *lpszBuf++;
        //    dwCount++;
        //}
        //*lpszTmp = '\0';
        return S_OK;

    }
#ifdef __cplusplus
}
#endif
