# Discovery

****

## Account Discovery

### Local Account

`windows`

```CMD
 net user
```

```
net localgroup
```

`Linux`

```
cat /etc/passwd
```

`macOS`

```
dscl . list /users
```

### Domain Account

`windows`

```
net user /domain
```

```
net group /domain
```

```powershell
wmic /NAMESPACE:\\root\directory\ldap PATH ds_user GET ds_samaccountname
```

```powershell
wmic /NAMESPACE:\\root\directory\ldap PATH ds_group GET ds_samaccountname
```

```powershell
wmic path win32_groupuser
```

### Email Account

```powershell
Get-GlobalAddressList
```

### Cloud Account

```powershell
Get-MsolRoleMember
```

```powershell
az ad user list
```

```powershell
aws iam list-users
aws iam list-roles
```

## Application Discovery

`windows`

```powershell
Get-CimInstance -Query "select * from Win32_Product"
```

```powershell
Get-CimInstance -Query "select * from Win32_Product"  | ?{$_.Vendor -notmatch 'Microsoft'}
```

## Network Resource Discovery

```powershell
Get-Smbshare
```

## Cloud Infrastructure Discovery

`aws`

```bash
aws iam create-user --user-name #{username}
```

```bash
cat ~/.aws/credentials | grep "default"
```

```bash
aws iam list-users 
```
