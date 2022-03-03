# Com Hijacking

The Microsoft Component Object Model (COM) is a platform-independent, distributed, object-oriented system for creating binary software components that can interact. COM is the foundation technology for Microsoft's OLE (compound documents), ActiveX (Internet-enabled components), as well as other

The Class ID, or CLSID, is a serial number that represents a unique ID 
for any application component in Windows. In practice, this means all 
registry entries for an application component can usually be found under
 the registry key HKEY_CLASSES_ROOT\CLSID{CLSID value}

### Default Regiatry Path

```cmd
HKEY_LOCAL_MACHINE\SOFTWARE\Classes\mscfile\shell\open\command 
%SystemRoot%\system32\mmc.exe "%1" %*
```

### After change value

```cmd
HKEY_LOCAL_MACHINE\SOFTWARE\Classes\mscfile\shell\open\command 
%SystemRoot%\system32\windowspowershell\v1.0\powershell.exe
```
