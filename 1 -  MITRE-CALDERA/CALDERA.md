# MITRE CALDERA™

***

CALDERA™ is a cyber security platform designed to easily automate adversary emulation, assist manual red-teams, and automate incident response ,It is built on the MITRE ATT&CK™ framework and is an active research project at MITRE.

https://caldera.mitre.org/
https://github.com/mitre/caldera 

## Installing  CALDERA

```bash
Git clone https://github.com/mitre/caldera
pip3 install -r requirements.txt
```

## Running CALDERA

```
python3 server.py --insecure
```

http://localhost:8888

* Username: red 

* Password : admin

## Basic Usage

* `Agent` 
    Agents are software programs that connect back to CALDERA at certain intervals to get instruction
  
  * Sandcat (54ndc47): A GoLang agent which communicates through HTTP, Git, or P2P over SMB contacts
  * Manx: A GoLang agent which communicates via the TCP contact and functions as a reverse-shell
  * Ragdoll: A Python agent which communicates via the HTML contact

* `Abilities`
  An ability is a specific ATT&CK tactic/technique implementation which can be executed on running agents. Abilities will include the command(s) to run

* `Adversaries`
  Adversary profiles are groups of abilities, representing the tactics, techniques, and procedures (TTPs) available to a threat actor. Adversary profiles are used when running an operation to determine which abilities will be executed

* `Operation` 
  Operations run abilities on agent groups. Adversary profiles are used to determine which abilities will be run and agent groups are used to determine which agents the abilities will be run on.

### Agent

1. go to agent menu and select Deploy an agent 
2. Select 54ndc47 and windows platform
3. Change app.contact.http to your ip address 
4. Payload Save as first.ps1 and send for victim 
5. victim should run payload

### Adversaries

#### Scenario -1

1. select New and create a profile
   
   * Profile name  : Local Enum NooraNet
     * Profile Description : Local Enum NooraNet

2. Add Ability
   
   * Find ip address
   * Current user
   * Find local user
   * Find user process
   * Network interface configuration 
   * Check python 
   * Discover antivirus

#### Scenarion -2

1. select New and create a profile
   
   * Profile name  : Local net  Enum NooraNet
     * Profile Description : Local net Enum NooraNet

2. Add Ability
   
   * Networkshare discovery command prompt
   * View admin share
   * Identifying firewall
   * Scan wifi network
   * Preferred wifi network
   * Network service scanning (host and port discovery)

#### Scenarion -3

1. select New and create a profile
   
   * Profile name  : Cred-dump NooraNet
   * Profile Description : Cred-dump NooraNet

2. Add Ability
   
   * Powerkatz-staged
   
   * Credential in registry - HKCU
   
   * Credential in registry - HKLM
   
   * Run chrome-password collector
   
   * Extracting password with findstr
     
     #### Scenarion -4

3. select New and create a profile
   
   * Profile name  : Linux Enum NooraNet
   * Profile Description : Linux Enum NooraNet

4. Add Ability
   
   * Find ip address 
   * Find local users
   * Detetc Virtualization Environment (Linux)
   * System network connections Discovery 
   * Linux load kernel Module via insmod

### Operation

* Create Operation 
  * Operation name : Local OS Enum NooraNet
  * Adversary : Local OS Enumeration NooraNet
  * Fact source : Alice filter
* Create Operation 
  * Operation name : Local Net Enum NooraNet
    * Adversary : Local Net Enum NooraNet
    * Fact source : Alice filter
* Create Operation 
  * Operation name : Local OS-Cred NooraNet
  * Adversary : Local OS Cred-dump NooraNet
  * Fact source : Alice filter

## plugins

`Compass`Generate a layer file for any adversary, which you can overlay on the matrix below OR Create an adversary in the matrix, then upload the layer file to generate an adversary to use in an operation
