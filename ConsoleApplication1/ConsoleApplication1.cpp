#include <stdio.h>
#include <windows.h>
BOOL CALLBACK EnumWindowsProc(_In_ HWND hwnd, _In_ LPARAM Lparam)
{
	HWND hDefView = FindWindowEx(hwnd, 0, L"SHELLDLL_DefView", 0);
	if (hDefView != 0) {
		HWND hWorkerw = FindWindowEx(0, hwnd, L"WorkerW", 0);
		ShowWindow(hWorkerw, SW_HIDE);

		return FALSE;
	}
	return TRUE;
}
int main()
{
	LPCWSTR lpParameter = L" E:\\测试视频.mp4  -noborder -x 1920 -y 1080  -loop 0";
	STARTUPINFO si{ 0 };
	PROCESS_INFORMATION pi{ 0 };
	if (CreateProcess(L"C:\\Program Files\\WindowsApps\\Microsoft.ZuneVideo_10.21111.10511.0_x64__8wekyb3d8bbwe\\Video.UI.exe", (LPWSTR)lpParameter, 0, 0, 0, 0, 0, 0, &si, &pi))
	{
		Sleep(200);

		HWND hProgman = FindWindow(L"Progman", 0);
		SendMessageTimeout(hProgman, 0x52C, 0, 0, 0, 100, 0);
		HWND hFfplay = FindWindow(L"SDL_app", 0);
		SetParent(hFfplay, hProgman);
		EnumWindows(EnumWindowsProc, 0);
	}

	return 0;
}
