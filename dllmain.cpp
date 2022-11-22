// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
typedef BOOL(WINAPI* rpm)(HANDLE, LPCVOID, LPVOID, SIZE_T, SIZE_T*);
typedef SIZE_T(WINAPI* vqe)(HANDLE,LPCVOID,PMEMORY_BASIC_INFORMATION,SIZE_T);
rpm rpm_orig = nullptr;
vqe vqe_orig = nullptr;
//
bool isDumping = false;
bool isAccess = false;
bool isLegitDump = false;
//
int WINAPI Main();
BOOL ReadProcessMemoryHook(HANDLE  hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T  nSize, SIZE_T* lpNumberOfBytesRead) {
    if (strcmp(GetName(hProcess), skCrypt("aow_exe.exe")) == 0) {
        isAccess = true;
    }
    if (nSize > 2500000) {
        isDumping = true;
    }
    if (isAccess && isDumping && !isLegitDump) {
        Terminate(skCrypt("aow_exe.exe"), (DWORD)lpBaseAddress, nSize);
    }
    return rpm_orig(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
}
SIZE_T VirtualQueryExHk(HANDLE hProcess, LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
    SIZE_T a = vqe_orig(hProcess, lpAddress, lpBuffer, dwLength);
    isLegitDump = true;
    return a;
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, 0, 0, 0));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

int WINAPI Main() {
    if (MH_Initialize() != MH_OK)
        return -1;
    MH_CreateHook(GetProcAddress(LoadLibrary(skCrypt("Kernel32.dll")), skCrypt("ReadProcessMemory")), &ReadProcessMemoryHook, reinterpret_cast<void**>(&rpm_orig));
    MH_CreateHook(GetProcAddress(LoadLibrary(skCrypt("Kernel32.dll")), skCrypt("VirtualQueryEx")), &VirtualQueryExHk, reinterpret_cast<void**>(&vqe_orig));
    MH_EnableHook(MH_ALL_HOOKS);
    return 1;
}
